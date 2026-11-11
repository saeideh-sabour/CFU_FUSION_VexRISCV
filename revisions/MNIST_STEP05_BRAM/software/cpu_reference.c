/* Audited Q31 CPU baseline. No custom instructions; no hardware speed claim.
 * Host: gcc -O2 -std=c11 software/cpu_reference.c -o /tmp/mnist_cpu_reference
 * Verification is separate from inference and must stay outside timing windows.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../model/model_data.h"
static uint8_t c1[8*28*28],p1[8*14*14],c2[16*14*14],p2[16*7*7],f1[64],r1[64],f2[10];
/* Symmetric round-to-nearest ties-to-even of signed INT64 / 2^31.
 * Products in this model cannot reach INT64_MIN.
 */
static uint8_t requant(int32_t acc,int32_t mult,int zp,int relu){
 int64_t v=(int64_t)acc*mult;
 uint64_t mag=v<0?(uint64_t)(-v):(uint64_t)v;
 uint64_t q=mag>>31, rem=mag&0x7fffffffULL;
 if(rem>0x40000000ULL || (rem==0x40000000ULL && (q&1)))++q;
 int64_t y=(v<0?-(int64_t)q:(int64_t)q)+zp;
 if(y<(relu?zp:0))y=relu?zp:0;
 if(y>255)y=255;
 return (uint8_t)y;
}
static void conv(const uint8_t *x,const int8_t *w,uint8_t *y,int ci,int co,int h,int wd,int iz,int oz,const int32_t *m){
 for(int o=0;o<co;o++)for(int row=0;row<h;row++)for(int col=0;col<wd;col++){
  int32_t acc=0;
  for(int i=0;i<ci;i++)for(int ky=0;ky<3;ky++)for(int kx=0;kx<3;kx++){
   int yy=row+ky-1,xx=col+kx-1;
   int xv=(yy<0||yy>=h||xx<0||xx>=wd)?iz:x[(i*h+yy)*wd+xx];
   acc+=(xv-iz)*(int32_t)w[((o*ci+i)*3+ky)*3+kx];
  }
  y[(o*h+row)*wd+col]=requant(acc,m[o],oz,1);
 }
}
static void pool(const uint8_t *x,uint8_t *y,int c,int h,int w){
 for(int k=0;k<c;k++)for(int r=0;r<h/2;r++)for(int s=0;s<w/2;s++){
  uint8_t v=0;
  for(int a=0;a<2;a++)for(int b=0;b<2;b++){
   uint8_t z=x[(k*h+2*r+a)*w+2*s+b];if(z>v)v=z;
  }
  y[(k*(h/2)+r)*(w/2)+s]=v;
 }
}
static void fc(const uint8_t *x,const int8_t *w,uint8_t *y,int ni,int no,int iz,int oz,const int32_t *m){
 for(int o=0;o<no;o++){
  int32_t acc=0;for(int i=0;i<ni;i++)acc+=((int32_t)x[i]-iz)*(int32_t)w[o*ni+i];
  y[o]=requant(acc,m[o],oz,0);
 }
}
static int verify(const char *name,const uint8_t *a,const uint8_t *b,int n){
 int errors=0;for(int i=0;i<n;i++)if(a[i]!=b[i]){
  if(errors==0){printf("FAIL %s index=%d got=%u expected=%u\n",name,i,a[i],b[i]);}
  ++errors;
 }
 return errors;
}
static void infer(const uint8_t *input){
 conv(input,data_conv1_weights,c1,1,8,28,28,0,0,data_conv1_q31);
 pool(c1,p1,8,28,28);
 conv(p1,data_conv2_weights,c2,8,16,14,14,0,0,data_conv2_q31);
 pool(c2,p2,16,14,14);
 fc(p2,data_fc1_weights,f1,784,64,0,70,data_fc1_q31);
 for(int i=0;i<64;i++)r1[i]=f1[i]<70?70:f1[i];
 fc(r1,data_fc2_weights,f2,64,10,70,73,data_fc2_q31);
}
int main(void){
 int errors=0;
 for(int n=0;n<10;n++){
  infer(data_input+n*784);
  errors+=verify("conv1",c1,data_conv1+n*6272,6272);
  errors+=verify("pool1",p1,data_conv1_pool+n*1568,1568);
  errors+=verify("conv2",c2,data_conv2+n*3136,3136);
  errors+=verify("pool2",p2,data_conv2_pool+n*784,784);
  errors+=verify("fc1",f1,data_fc1+n*64,64);
  errors+=verify("fc1_relu",r1,data_fc1_relu+n*64,64);
  errors+=verify("fc2",f2,data_fc2+n*10,10);
  int pred=0;for(int j=1;j<10;j++)if(f2[j]>f2[pred])pred=j;
  if(pred!=data_labels[n])++errors;
  printf("sample=%d label=%u prediction=%d\n",n,data_labels[n],pred);
 }
 printf("CPU_Q31_REFERENCE %s mismatches=%d (host only, no CFU measurement)\n",errors?"FAIL":"PASS",errors);
 return errors?1:0;
}
