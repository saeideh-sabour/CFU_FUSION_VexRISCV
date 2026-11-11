#include "VCfu.h"
#include "verilated.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define main scalar_reference_main
#include "../software/cpu_reference.c"
#undef main
#include "../software/step03/cfu_driver.h"
static VCfu *dut;
static unsigned call_count;
static unsigned long long clocks;
static void fail(const char *s){fprintf(stderr,"RTL_FAIL %s at clock %llu\n",s,clocks);exit(1);}
static void tick(){dut->clk=0;dut->eval();dut->clk=1;dut->eval();dut->clk=0;dut->eval();++clocks;}
static void reset_dut(){dut->reset=1;dut->cmd_valid=0;dut->rsp_ready=0;tick();tick();dut->reset=0;tick();}
uint32_t mnist_cfu_call(unsigned family,unsigned fn,uint32_t a,uint32_t b){
 unsigned timeout=0;
 dut->cmd_valid=0;dut->rsp_ready=0;dut->eval();
 while(!dut->cmd_ready){if(++timeout>2000000)fail("command timeout");tick();}
 dut->cmd_payload_function_id=(fn<<3)|family;dut->cmd_payload_inputs_0=a;dut->cmd_payload_inputs_1=b;dut->cmd_valid=1;
 tick();dut->cmd_valid=0;
 // Inputs are allowed to change immediately after command handshake.
 dut->cmd_payload_function_id=1023;dut->cmd_payload_inputs_0=0xdeadbeef;dut->cmd_payload_inputs_1=0xabcdef01;
 dut->eval();timeout=0;
 while(!dut->rsp_valid){if(++timeout>2000000)fail("response timeout / deadlock");tick();}
 uint32_t response=dut->rsp_payload_outputs_0;
 for(unsigned s=0;s<(call_count++%4);s++){
  tick();if(!dut->rsp_valid||dut->rsp_payload_outputs_0!=response)fail("response changed under backpressure");
 }
 dut->rsp_ready=1;tick();dut->rsp_ready=0;dut->eval();
 return response;
}
static void must(bool condition,const char *s){if(!condition)fail(s);}
static void corner_tests(){
 reset_dut();must(mnist_cfu_call(0,7,0,0)==0x43465531,"identity");
 must(mnist_cfu_call(0,4,0,0)&0x80000000u,"unconfigured start accepted");
 must(mnist_cfu_call(7,127,0,0)&0x80000000u,"unknown opcode accepted");
 must(mnist_cfu_call(0,0,0,33)&0x80000000u,"oversized width accepted");
 must(mnist_cfu_call(0,1,2048,0)&0x80000000u,"out-of-bounds input write");
 uint8_t x[4]={1,3,5,255},y[4]={0},p[1]={0};int8_t w[9]={0,0,0,0,1,0,0,0,0};int32_t m[1]={1073741824};
 must(cfu_conv_layer(x,w,m,2,2,1,1,0,0,3,y,p)==0,"small conv");
 must(y[0]==0&&y[1]==2&&y[2]==2&&y[3]==128&&p[0]==128,"ties-to-even rounding");
 uint8_t expected[4];for(int i=0;i<4;i++)expected[i]=requant((int)x[i]-4,m[0],70,1);
 must(cfu_conv_layer(x,w,m,2,2,1,1,4,70,3,y,p)==0,"nonzero zero point");
 must(memcmp(y,expected,4)==0,"quantized ReLU / signed centered activation");
 w[4]=-128;m[0]=2147483647;x[0]=0;x[1]=0;x[2]=255;x[3]=255;
 must(cfu_conv_layer(x,w,m,2,2,1,1,128,0,3,y,p)==0,"negative weights");
 must(y[0]==255&&y[1]==255&&y[2]==0&&y[3]==0,"saturation");
 must(cfu_config(2,2,1,1,2,0,0)==0,"stream config");
 must(mnist_cfu_call(0,4,0,0)&0x80000000u,"unarmed stream must reject");
 must(cfu_config(3,2,1,1,1,0,0)==0,"odd width config");
 must(mnist_cfu_call(1,0,0,0)&0x80000000u,"odd pool width accepted");
 must(cfu_config(2,2,1,1,1,0,0)==0,"pool config");
 must(mnist_cfu_call(1,0,0,0)==0,"arm pool");
 must(mnist_cfu_call(1,1,256,0)&0x80000000u,"invalid byte push accepted");
 for(int i=0;i<4;i++)must(mnist_cfu_call(1,1,i+1,0)==0,"valid pool push");
 must(mnist_cfu_call(1,3,0,0)==0x10001,"pool count after invalid push");
 must(mnist_cfu_call(1,2,0,0)==4,"standalone pool");
 must(mnist_cfu_call(1,1,7,0)&0x80000000u,"push after full");
 reset_dut();must(mnist_cfu_call(0,6,0,0)==0,"reset capture count");
 printf("RTL_CORNER_TESTS PASS\n");
}
static void address_tests(){
 static uint8_t x[2048],got[8192],expected[8192],pgot[4096],pexp[4096];
 static int8_t w[4096];static int32_t m[32];
 // width,height,ci,co: odd shapes, maximum row width and channels,
 // exact input/capture capacity, unaligned channel/kernel word boundaries.
 const int dims[][4]={{1,1,1,1},{3,5,3,7},{32,32,2,8},{8,8,32,8},
                     {2,2,13,32},{30,2,3,5},{31,3,7,9},{4,6,5,11}};
 uint32_t seed=20261013;
 auto rnd=[&](){seed=seed*1664525u+1013904223u;return seed;};
 for(auto &d:dims){
  int wd=d[0],h=d[1],ci=d[2],co=d[3];
  for(int i=0;i<wd*h*ci;i++)x[i]=(uint8_t)(rnd()>>24);
  for(int i=0;i<ci*co*9;i++)w[i]=(int8_t)((int)(rnd()%17)-8);
  for(int i=0;i<co;i++)m[i]=10737418+(int32_t)(rnd()%21474836);
  int iz=(int)(rnd()%256),oz=(int)(rnd()%100);
  conv(x,w,expected,ci,co,h,wd,iz,oz,m);
  bool even=!(wd%2)&&!(h%2);
  for(unsigned route=1;route<=(even?3u:1u);route++){
   must(cfu_conv_layer(x,w,m,wd,h,ci,co,iz,oz,route,got,pgot)==0,"address test driver");
   if(route&1)must(verify("address_conv",got,expected,wd*h*co)==0,"address tensor");
   if(even){
    pool(expected,pexp,co,h,wd);
    if(route==1)must(cfu_pool_layer(got,pgot,wd,h,co)==0,"address standalone pool");
    must(verify("address_pool",pgot,pexp,wd*h*co/4)==0,"address pool tensor");
   }
  }
 }
 printf("RTL_ADDRESS_TESTS PASS shapes=8 including capacity boundaries\n");
}
int main(int argc,char **argv){
 Verilated::commandArgs(argc,argv);dut=new VCfu;corner_tests();address_tests();
 unsigned mismatches=0;
 for(unsigned route=1;route<=3;route++){
  for(int n=0;n<10;n++){
   must(cfu_conv_layer(data_input+n*784,data_conv1_weights,data_conv1_q31,28,28,1,8,0,0,route,c1,p1)==0,"Conv1 driver");
   if(route&1)mismatches+=verify("rtl_conv1",c1,data_conv1+n*6272,6272);
   if(route==1)must(cfu_pool_layer(c1,p1,28,28,8)==0,"standalone Pool1");
   if(route==2)must(mnist_cfu_call(0,5,0,0)&0x80000000u,"stream-only exposed stale Conv");
   mismatches+=verify("rtl_pool1",p1,data_conv1_pool+n*1568,1568);
   must(cfu_conv_layer(p1,data_conv2_weights,data_conv2_q31,14,14,8,16,0,0,route,c2,p2)==0,"Conv2 driver");
   if(route&1)mismatches+=verify("rtl_conv2",c2,data_conv2+n*3136,3136);
   if(route==1)must(cfu_pool_layer(c2,p2,14,14,16)==0,"standalone Pool2");
   mismatches+=verify("rtl_pool2",p2,data_conv2_pool+n*784,784);
   fc(p2,data_fc1_weights,f1,784,64,0,70,data_fc1_q31);
   for(int i=0;i<64;i++)r1[i]=f1[i]<70?70:f1[i];
   fc(r1,data_fc2_weights,f2,64,10,70,73,data_fc2_q31);
   mismatches+=verify("fc1",f1,data_fc1+n*64,64);
   mismatches+=verify("fc1_relu",r1,data_fc1_relu+n*64,64);
   mismatches+=verify("fc2",f2,data_fc2+n*10,10);
   int pred=0;for(int i=1;i<10;i++)if(f2[i]>f2[pred])pred=i;
   must(pred==data_labels[n],"prediction");
   printf("RTL mode=%s sample=%d prediction=%d cumulative_mismatches=%u\n",route==1?"UNFUSED":route==2?"FUSED":"BOTH",n,pred,mismatches);
  }
 }
 must(mismatches==0,"tensor comparison");
 printf("RTL_ALL_MODES PASS samples=10 modes=3 mismatches=0\n");
 printf("RTL functional simulation only; FC on host CPU; no RISC-V/FPGA benchmark.\n");
 dut->final();delete dut;return 0;
}
