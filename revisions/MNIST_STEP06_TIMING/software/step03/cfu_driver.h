#ifndef MNIST_CFU_DRIVER_H
#define MNIST_CFU_DRIVER_H
#include <stdint.h>
/* Caller implements bus transaction. RISC-V uses actual cfu_op*_hw, not software_cfu. */
uint32_t mnist_cfu_call(unsigned family,unsigned fn,uint32_t a,uint32_t b);
static int cfu_ok(uint32_t v){return (v&0x80000000u)==0;}
static int cfu_config(unsigned width,unsigned height,unsigned ci,unsigned co,unsigned route,unsigned iz,unsigned oz){
 uint32_t values[7]={width,height,ci,co,iz,oz,route};
 for(unsigned i=0;i<7;i++)if(!cfu_ok(mnist_cfu_call(0,0,i,values[i])))return -1;
 return 0;
}
static int cfu_load(unsigned fn,const void *ptr,unsigned n){
 const uint8_t *p=(const uint8_t *)ptr;
 for(unsigned i=0;i<n;i+=4){
  uint32_t v=0;for(unsigned j=0;j<4 && i+j<n;j++)v|=(uint32_t)p[i+j]<<(8*j);
  if(!cfu_ok(mnist_cfu_call(0,fn,i,v)))return -1;
 }
 return 0;
}
/* One software invocation per Conv layer. LOAD/config/read use multiple ISA instructions.
 * route=1 capture, route=2 internal stream, route=3 both. Stream mode arms Pool first.
 * out is optional ONLY in route=2; pooled is required in stream mode.
 */
static int cfu_conv_layer(const uint8_t *input,const int8_t *weights,const int32_t *multipliers,
 unsigned width,unsigned height,unsigned ci,unsigned co,unsigned iz,unsigned oz,unsigned route,
 uint8_t *out,uint8_t *pooled){
 unsigned total=width*height*co;
 if(cfu_config(width,height,ci,co,route,iz,oz))return -1;
 if(cfu_load(1,input,width*height*ci)||cfu_load(2,weights,co*ci*9))return -1;
 for(unsigned o=0;o<co;o++)if(!cfu_ok(mnist_cfu_call(0,3,o,(uint32_t)multipliers[o])))return -1;
 if((route&2) && !cfu_ok(mnist_cfu_call(1,0,0,0)))return -1;
 if(mnist_cfu_call(0,4,0,0)!=total)return -1;
 if(route&1){
  if(!out || mnist_cfu_call(0,6,0,0)!=total)return -1;
  for(unsigned i=0;i<total;i++){
   uint32_t v=mnist_cfu_call(0,5,i,0);if(!cfu_ok(v))return -1;out[i]=(uint8_t)v;
  }
 }else if(mnist_cfu_call(0,6,0,0)!=0)return -1;
 if(route&2){
  if(!pooled || mnist_cfu_call(1,3,0,0)!=(0x10000u|total/4))return -1;
  for(unsigned i=0;i<total/4;i++){
   uint32_t v=mnist_cfu_call(1,2,i,0);if(!cfu_ok(v))return -1;pooled[i]=(uint8_t)v;
  }
 }
 return 0;
}
/* Independent pooling custom function: CPU streams its input into op1. */
static int cfu_pool_layer(const uint8_t *input,uint8_t *out,unsigned width,unsigned height,unsigned channels){
 unsigned total=width*height*channels;
 if(cfu_config(width,height,1,channels,1,0,0))return -1;
 if(!cfu_ok(mnist_cfu_call(1,0,0,0)))return -1;
 for(unsigned i=0;i<total;i++)if(!cfu_ok(mnist_cfu_call(1,1,input[i],0)))return -1;
 if(mnist_cfu_call(1,3,0,0)!=(0x10000u|total/4))return -1;
 for(unsigned i=0;i<total/4;i++){
  uint32_t v=mnist_cfu_call(1,2,i,0);if(!cfu_ok(v))return -1;out[i]=(uint8_t)v;
 }
 return 0;
}
#endif
