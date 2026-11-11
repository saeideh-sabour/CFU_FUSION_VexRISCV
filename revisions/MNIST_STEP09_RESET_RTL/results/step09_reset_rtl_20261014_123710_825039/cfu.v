// STEP06 configuration-pipeline candidate; ISA-compatible with STEP03. See README_FA.md.
module MnistMac4(
 input signed [8:0] x0,x1,x2,x3,
 input signed [7:0] w0,w1,w2,w3,
 output signed [31:0] sum
);
 (* use_dsp = "yes" *) wire signed [16:0] p0=x0*w0, p1=x1*w1, p2=x2*w2, p3=x3*w3;
 assign sum={{15{p0[16]}},p0}+{{15{p1[16]}},p1}+{{15{p2[16]}},p2}+{{15{p3[16]}},p3};
endmodule

// Product is signed accumulator * positive Q31 multiplier.
// Round nearest, ties even; UINT8 saturation and quantized ReLU.
module MnistRequantQ31(input signed [63:0] product,input [7:0] zero_point,output reg [7:0] value);
 reg [63:0] mag,rounded;
 reg signed [63:0] shifted;
 always @* begin
  mag=product[63] ? -product : product;
  rounded=mag>>31;
  if(mag[30:0]>31'h40000000 || (mag[30:0]==31'h40000000 && rounded[0])) rounded=rounded+1;
  shifted=(product[63] ? -$signed(rounded) : $signed(rounded))+$signed({56'd0,zero_point});
  if(shifted<$signed({56'd0,zero_point})) value=zero_point;
  else if(shifted>255) value=255;
  else value=shifted[7:0];
 end
endmodule

// CHW raster MaxPool2x2 stride2. Stores horizontal max of the upper row.
// UINT8: max preserves quantization scale and zero point.
module MnistPool2x2 #(
 parameter MAX_WIDTH=32, parameter OUT_CAP=4096
)(
 input clk,reset,arm,
 input [7:0] width,height,channels,
 input in_valid, output in_ready,input [7:0] in_data,
 input [15:0] read_index,output reg [7:0] read_data,
 output reg [15:0] count,output reg done,
 output reg [31:0] received
);
 localparam OW=$clog2(OUT_CAP), LW=$clog2(MAX_WIDTH/2);
 reg active;
 reg [7:0] w,h,c,col,row,chan,left;
 reg [7:0] upper[0:MAX_WIDTH/2-1];
 (* ram_style = "block" *) reg [7:0] results[0:OUT_CAP-1];
 wire [7:0] pair_max=left>in_data ? left:in_data;
 assign in_ready=active;
 always @(posedge clk) begin
  read_data<=results[read_index[OW-1:0]];
  if(!reset && !arm && in_valid && in_ready && col[0] && row[0])
   results[count[OW-1:0]]<=upper[col[LW:1]]>pair_max?upper[col[LW:1]]:pair_max;
 end
 always @(posedge clk) begin
  if(reset) begin
   active<=0;done<=0;count<=0;received<=0;col<=0;row<=0;chan<=0;
   w<=0;h<=0;c<=0;left<=0;
  end else if(arm) begin
   w<=width;h<=height;c<=channels;col<=0;row<=0;chan<=0;
   active<=1;done<=0;count<=0;received<=0;left<=0;
  end else if(in_valid && in_ready) begin
   received<=received+1;
   if(!col[0]) left<=in_data;
   else if(!row[0]) upper[col[LW:1]]<=pair_max;
   else begin
    count<=count+1;
   end
   if(col==w-1) begin
    col<=0;
    if(row==h-1) begin
     row<=0;
     if(chan==c-1) begin active<=0;done<=1;end
     else chan<=chan+1;
    end else row<=row+1;
   end else col<=col+1;
  end
 end
endmodule

// STEP05: synchronous packed RAM, serial operand gather, four-lane MAC, internal Pool stream.
// Local banks, no bus-master or main-memory access. Interface: CFU Playground.
// Only Conv3x3/stride1/pad1/no bias and MaxPool2x2/stride2 are supported.
module Cfu #(
 parameter IN_CAP=2048, WEIGHT_CAP=4096, CONV_CAP=8192, POOL_CAP=4096,
 parameter MAX_WIDTH=32, MAX_CHANNELS=32
)(
 input cmd_valid,output cmd_ready,input [9:0] cmd_payload_function_id,
 input [31:0] cmd_payload_inputs_0,cmd_payload_inputs_1,
 output reg rsp_valid,input rsp_ready,output reg [31:0] rsp_payload_outputs_0,
 input reset,clk
);
 localparam CW=$clog2(CONV_CAP), MW=$clog2(MAX_CHANNELS), IW=$clog2(IN_CAP/4), WW=$clog2(WEIGHT_CAP/4);
 localparam IDLE=0,FETCH=1,MAC=2,RQMUL=3,RQROUND=4,EMIT=5,ADDR=6,RAMREAD=7,LATCH=8,READCONV=9,READPOOL=10,CFG1=11,CFG2=12,CFG3=13;
 localparam ERR=32'h80000000;
 reg [3:0] state;
 reg [7:0] width,height,cin,cout,input_zp,output_zp;
 reg [1:0] route;
 (* ram_style = "block" *) reg [31:0] inputs[0:IN_CAP/4-1];
 (* ram_style = "block" *) reg [31:0] weights[0:WEIGHT_CAP/4-1];
 reg signed [31:0] multipliers[0:MAX_CHANNELS-1];
 (* ram_style = "block" *) reg [7:0] conv_results[0:CONV_CAP-1];
 reg [15:0] out_index,captured;
 reg [7:0] ox,oy,oc;
 reg [15:0] kernel_index;
 reg signed [31:0] acc;
 reg signed [63:0] product;
 reg [7:0] quant_value;
 reg signed [8:0] lx[0:3];
 reg signed [7:0] lw[0:3];
 wire signed [31:0] sum;
 wire [7:0] rounded;
 wire [2:0] family=cmd_payload_function_id[2:0];
 wire [6:0] fn=cmd_payload_function_id[9:3];
 wire [31:0] a=cmd_payload_inputs_0,b=cmd_payload_inputs_1;
 wire accept=cmd_valid && cmd_ready;
 // Derived dimensions and validation are registered before CONFIG responds.
 // This removes the dimension->multiply->validate->FSM/CE combinational chain.
 reg [31:0] plane,kernel_len,total,input_size,weight_size;
 reg valid_conv,valid_pool;
 wire pool_ready,pool_done;
 wire [15:0] pool_count;
 wire [31:0] pool_received;
 wire [7:0] pool_read_data;
 reg pool_armed;
 reg [7:0] pool_w,pool_h,pool_c;
 wire arm=accept && family==1 && fn==0 && valid_pool;
 wire cpu_push=accept && family==1 && fn==1 && pool_ready && a<=255;
 wire fused_valid=(state==EMIT) && route[1];
 wire [7:0] pool_data=fused_valid?quant_value:a[7:0];
 MnistMac4 mac4(lx[0],lx[1],lx[2],lx[3],lw[0],lw[1],lw[2],lw[3],sum);
 MnistRequantQ31 requant(product,output_zp,rounded);
 MnistPool2x2 #(.MAX_WIDTH(MAX_WIDTH),.OUT_CAP(POOL_CAP)) pool(
  .clk(clk),.reset(reset),.arm(arm),.width(width),.height(height),.channels(cout),
  .in_valid(fused_valid||cpu_push),.in_ready(pool_ready),.in_data(pool_data),
  .read_index(a[15:0]),.read_data(pool_read_data),.count(pool_count),.done(pool_done),.received(pool_received)
 );
 assign cmd_ready=(state==IDLE) && !rsp_valid && !reset;
 reg [1:0] lane,kx,ky;
 reg [15:0] channel_base,weight_base,input_addr,weight_addr;
 reg signed [9:0] ix,iy;
 reg sample_valid,weight_valid;
 reg [31:0] input_word,weight_word;
 reg [7:0] conv_read_data;
 wire [7:0] input_byte=input_word[{input_addr[1:0],3'b000} +: 8];
 wire signed [7:0] weight_byte=weight_word[{weight_addr[1:0],3'b000} +: 8];
 wire [15:0] sample_index=kernel_index+{14'd0,lane};
 // No memory reset: control reset invalidates counts. One write port per bank.
 always @(posedge clk) begin
  if(accept && family==0 && fn==1 && a<=IN_CAP-4 && a[1:0]==0)
   inputs[a[IW+1:2]]<=b;
  if(accept && family==0 && fn==2 && a<=WEIGHT_CAP-4 && a[1:0]==0)
   weights[a[WW+1:2]]<=b;
  if(state==RAMREAD) begin
   input_word<=inputs[input_addr[IW+1:2]];
   weight_word<=weights[weight_addr[WW+1:2]];
  end
  if(!reset && state==EMIT && (!route[1] || pool_ready) && route[0])
   conv_results[out_index[CW-1:0]]<=quant_value;
  conv_read_data<=conv_results[a[CW-1:0]];
 end
 integer l;
 always @(posedge clk) begin
  if(reset) begin
   state<=IDLE;rsp_valid<=0;rsp_payload_outputs_0<=0;
   plane<=0;kernel_len<=0;total<=0;input_size<=0;weight_size<=0;valid_conv<=0;valid_pool<=0;
   width<=0;height<=0;cin<=0;cout<=0;input_zp<=0;output_zp<=0;route<=1;
   out_index<=0;captured<=0;ox<=0;oy<=0;oc<=0;kernel_index<=0;acc<=0;product<=0;quant_value<=0;
   pool_armed<=0;pool_w<=0;pool_h<=0;pool_c<=0;
   lane<=0;kx<=0;ky<=0;channel_base<=0;weight_base<=0;
   input_addr<=0;weight_addr<=0;ix<=0;iy<=0;sample_valid<=0;weight_valid<=0;
   for(l=0;l<4;l=l+1)begin lx[l]<=0;lw[l]<=0;end
  end else begin
   if(rsp_valid && rsp_ready) rsp_valid<=0;
   if(accept) begin
    rsp_valid<=1;rsp_payload_outputs_0<=0;
    case(family)
     0:case(fn)
      0:begin
       state<=CFG1;rsp_valid<=0;
       case(a)
       0:if(b>0 && b<=MAX_WIDTH)width<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       1:if(b>0 && b<=32)height<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       2:if(b>0 && b<=MAX_CHANNELS)cin<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       3:if(b>0 && b<=MAX_CHANNELS)cout<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       4:if(b<=255)input_zp<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       5:if(b<=255)output_zp<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       6:if(b>=1 && b<=3)route<=b[1:0];else rsp_payload_outputs_0<=ERR|1;
       default:rsp_payload_outputs_0<=ERR|1;
       endcase
      end
      1:if(a<=IN_CAP-4 && a[1:0]==0)begin
// Packed 32-bit bank write is in the separate RAM process.
      end else rsp_payload_outputs_0<=ERR|2;
      2:if(a<=WEIGHT_CAP-4 && a[1:0]==0)begin
// Packed 32-bit bank write is in the separate RAM process.
      end else rsp_payload_outputs_0<=ERR|2;
      3:if(a<MAX_CHANNELS && b[31]==0)multipliers[a]<=b;else rsp_payload_outputs_0<=ERR|2;
      4:if(!valid_conv || (route[1] && (!valid_pool || !pool_armed || !pool_ready || pool_received!=0 || pool_w!=width || pool_h!=height || pool_c!=cout)))begin
       rsp_payload_outputs_0<=ERR|3;
      end else begin
       state<=FETCH;rsp_valid<=0;ox<=0;oy<=0;oc<=0;kernel_index<=0;acc<=0;out_index<=0;captured<=0;
       if(route[1])pool_armed<=0;
       lane<=0;kx<=0;ky<=0;channel_base<=0;weight_base<=0;
      end
      5:if(a<captured)begin state<=READCONV;rsp_valid<=0;end else rsp_payload_outputs_0<=ERR|4;
      6:rsp_payload_outputs_0<={16'd0,captured};
      7:rsp_payload_outputs_0<=32'h43465531;
      default:rsp_payload_outputs_0<=ERR|5;
     endcase
     1:case(fn)
      0:if(valid_pool)begin pool_armed<=1;pool_w<=width;pool_h<=height;pool_c<=cout;end
        else rsp_payload_outputs_0<=ERR|3;
      1:if(!pool_ready || a>255)rsp_payload_outputs_0<=ERR|6;
        else pool_armed<=0;
      2:if(a<pool_count)begin state<=READPOOL;rsp_valid<=0;end else rsp_payload_outputs_0<=ERR|4;
      3:rsp_payload_outputs_0<={15'd0,pool_done,pool_count};
      default:rsp_payload_outputs_0<=ERR|5;
     endcase
     default:rsp_payload_outputs_0<=ERR|5;
    endcase
   end
   case(state)
    CFG1:begin
     plane<={24'd0,width}*{24'd0,height};
     kernel_len<={24'd0,cin}*32'd9;
     state<=CFG2;
    end
    CFG2:begin
     total<=plane*{24'd0,cout};
     input_size<=plane*{24'd0,cin};
     weight_size<=kernel_len*{24'd0,cout};
     state<=CFG3;
    end
    CFG3:begin
     valid_conv<=width>0 && width<=MAX_WIDTH && height>0 && height<=32 &&
      cin>0 && cin<=MAX_CHANNELS && cout>0 && cout<=MAX_CHANNELS &&
      input_size<=IN_CAP && weight_size<=WEIGHT_CAP && total<=CONV_CAP && route!=0;
     valid_pool<=width>0 && width<=MAX_WIDTH && height>0 && height<=32 &&
      !width[0] && !height[0] && cout>0 && cout<=MAX_CHANNELS && total/4<=POOL_CAP;
     state<=IDLE;rsp_valid<=1;
    end
    // Gather four operands sequentially into lane registers. No / or % logic.
    FETCH:begin
     ix<=$signed({2'd0,ox})+$signed({8'd0,kx})-10'sd1;
     iy<=$signed({2'd0,oy})+$signed({8'd0,ky})-10'sd1;
     weight_addr<=weight_base+sample_index;
     weight_valid<={16'd0,sample_index}<kernel_len;
     state<=ADDR;
    end
    ADDR:begin
     // Address arithmetic has its own stage, separate from RAM and subtraction.
     input_addr<=channel_base+({6'd0,iy}*{8'd0,width})+{{6{ix[9]}},ix};
     sample_valid<=weight_valid && iy>=0 && iy<$signed({2'd0,height}) && ix>=0 && ix<$signed({2'd0,width});
     state<=RAMREAD;
    end
    RAMREAD:state<=LATCH;
    LATCH:begin
     lw[lane]<=weight_valid?weight_byte:8'sd0;
     lx[lane]<=sample_valid?($signed({1'b0,input_byte})-$signed({1'b0,input_zp})):9'sd0;
     if(kx==2)begin
      kx<=0;
      if(ky==2)begin ky<=0;channel_base<=channel_base+plane[15:0];end
      else ky<=ky+1;
     end else kx<=kx+1;
     if(lane==3)begin lane<=0;state<=MAC;end
     else begin lane<=lane+1;state<=FETCH;end
    end
    READCONV:begin state<=IDLE;rsp_valid<=1;rsp_payload_outputs_0<={24'd0,conv_read_data};end
    READPOOL:begin state<=IDLE;rsp_valid<=1;rsp_payload_outputs_0<={24'd0,pool_read_data};end
    MAC:begin
     acc<=acc+sum;
     if({16'd0,kernel_index}+4>=kernel_len)state<=RQMUL;
     else begin kernel_index<=kernel_index+4;state<=FETCH;end
    end
    RQMUL:begin product<=acc*multipliers[oc[MW-1:0]];state<=RQROUND;end
    RQROUND:begin quant_value<=rounded;state<=EMIT;end
    EMIT:if(!route[1] || pool_ready)begin
     if(route[0])captured<=captured+1;
     if({16'd0,out_index}+1>=total)begin state<=IDLE;rsp_valid<=1;rsp_payload_outputs_0<=total;end
     else begin
      out_index<=out_index+1;kernel_index<=0;acc<=0;state<=FETCH;
      lane<=0;kx<=0;ky<=0;channel_base<=0;
      if(ox==width-1)begin
       ox<=0;if(oy==height-1)begin oy<=0;oc<=oc+1;weight_base<=weight_base+kernel_len[15:0];end else oy<=oy+1;
      end else ox<=ox+1;
     end
    end
    default:;
   endcase
  end
 end
endmodule
