// Generated from mac4.v, requant_q31.v, pool2x2_stream.v, cfu_top.v
module MnistMac4(
 input signed [8:0] x0,x1,x2,x3,
 input signed [7:0] w0,w1,w2,w3,
 output signed [31:0] sum
);
 wire signed [16:0] p0=x0*w0, p1=x1*w1, p2=x2*w2, p3=x3*w3;
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
 input [15:0] read_index,output [7:0] read_data,
 output reg [15:0] count,output reg done,
 output reg [31:0] received
);
 localparam OW=$clog2(OUT_CAP), LW=$clog2(MAX_WIDTH/2);
 reg active;
 reg [7:0] w,h,c,col,row,chan,left;
 reg [7:0] upper[0:MAX_WIDTH/2-1];
 reg [7:0] results[0:OUT_CAP-1];
 wire [7:0] pair_max=left>in_data ? left:in_data;
 assign in_ready=active;
 assign read_data=results[read_index[OW-1:0]];
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
    results[count[OW-1:0]]<=upper[col[LW:1]]>pair_max?upper[col[LW:1]]:pair_max;
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

// V1 correctness implementation: full-layer Conv START, independently armed Pool.
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
 localparam CW=$clog2(CONV_CAP), MW=$clog2(MAX_CHANNELS);
 localparam IDLE=0,FETCH=1,MAC=2,RQMUL=3,RQROUND=4,EMIT=5;
 localparam ERR=32'h80000000;
 reg [2:0] state;
 reg [7:0] width,height,cin,cout,input_zp,output_zp;
 reg [1:0] route;
 reg [7:0] inputs[0:IN_CAP-1];
 reg signed [7:0] weights[0:WEIGHT_CAP-1];
 reg signed [31:0] multipliers[0:MAX_CHANNELS-1];
 reg [7:0] conv_results[0:CONV_CAP-1];
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
 wire [31:0] plane={24'd0,width}*{24'd0,height};
 wire [31:0] kernel_len={24'd0,cin}*9;
 wire [31:0] total=plane*{24'd0,cout};
 wire valid_conv=width>0 && width<=MAX_WIDTH && height>0 && height<=32 &&
  cin>0 && cin<=MAX_CHANNELS && cout>0 && cout<=MAX_CHANNELS &&
  plane*{24'd0,cin}<=IN_CAP && kernel_len*{24'd0,cout}<=WEIGHT_CAP &&
  total<=CONV_CAP && route!=0;
 wire valid_pool=width>0 && width<=MAX_WIDTH && height>0 && height<=32 &&
  !width[0] && !height[0] && cout>0 && cout<=MAX_CHANNELS && total/4<=POOL_CAP;
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
 integer l,t,ic,ky,kx,iy,ix,addr;
 always @(posedge clk) begin
  if(reset) begin
   state<=IDLE;rsp_valid<=0;rsp_payload_outputs_0<=0;
   width<=0;height<=0;cin<=0;cout<=0;input_zp<=0;output_zp<=0;route<=1;
   out_index<=0;captured<=0;ox<=0;oy<=0;oc<=0;kernel_index<=0;acc<=0;product<=0;quant_value<=0;
   pool_armed<=0;pool_w<=0;pool_h<=0;pool_c<=0;
   for(l=0;l<4;l=l+1)begin lx[l]<=0;lw[l]<=0;end
  end else begin
   if(rsp_valid && rsp_ready) rsp_valid<=0;
   if(accept) begin
    rsp_valid<=1;rsp_payload_outputs_0<=0;
    case(family)
     0:case(fn)
      0:case(a)
       0:if(b>0 && b<=MAX_WIDTH)width<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       1:if(b>0 && b<=32)height<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       2:if(b>0 && b<=MAX_CHANNELS)cin<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       3:if(b>0 && b<=MAX_CHANNELS)cout<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       4:if(b<=255)input_zp<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       5:if(b<=255)output_zp<=b[7:0];else rsp_payload_outputs_0<=ERR|1;
       6:if(b>=1 && b<=3)route<=b[1:0];else rsp_payload_outputs_0<=ERR|1;
       default:rsp_payload_outputs_0<=ERR|1;
      endcase
      1:if(a<=IN_CAP-4 && a[1:0]==0)begin
       inputs[a]<=b[7:0];inputs[a+1]<=b[15:8];inputs[a+2]<=b[23:16];inputs[a+3]<=b[31:24];
      end else rsp_payload_outputs_0<=ERR|2;
      2:if(a<=WEIGHT_CAP-4 && a[1:0]==0)begin
       weights[a]<=b[7:0];weights[a+1]<=b[15:8];weights[a+2]<=b[23:16];weights[a+3]<=b[31:24];
      end else rsp_payload_outputs_0<=ERR|2;
      3:if(a<MAX_CHANNELS && b[31]==0)multipliers[a]<=b;else rsp_payload_outputs_0<=ERR|2;
      4:if(!valid_conv || (route[1] && (!valid_pool || !pool_armed || !pool_ready || pool_received!=0 || pool_w!=width || pool_h!=height || pool_c!=cout)))begin
       rsp_payload_outputs_0<=ERR|3;
      end else begin
       state<=FETCH;rsp_valid<=0;ox<=0;oy<=0;oc<=0;kernel_index<=0;acc<=0;out_index<=0;captured<=0;
       if(route[1])pool_armed<=0;
      end
      5:if(a<captured)rsp_payload_outputs_0<={24'd0,conv_results[a]};else rsp_payload_outputs_0<=ERR|4;
      6:rsp_payload_outputs_0<={16'd0,captured};
      7:rsp_payload_outputs_0<=32'h43465531;
      default:rsp_payload_outputs_0<=ERR|5;
     endcase
     1:case(fn)
      0:if(valid_pool)begin pool_armed<=1;pool_w<=width;pool_h<=height;pool_c<=cout;end
        else rsp_payload_outputs_0<=ERR|3;
      1:if(!pool_ready || a>255)rsp_payload_outputs_0<=ERR|6;
        else pool_armed<=0;
      2:if(a<pool_count)rsp_payload_outputs_0<={24'd0,pool_read_data};else rsp_payload_outputs_0<=ERR|4;
      3:rsp_payload_outputs_0<={15'd0,pool_done,pool_count};
      default:rsp_payload_outputs_0<=ERR|5;
     endcase
     default:rsp_payload_outputs_0<=ERR|5;
    endcase
   end
   case(state)
    FETCH:begin
     for(l=0;l<4;l=l+1)begin
      t={16'd0,kernel_index}+l;ic=t/9;ky=(t%9)/3;kx=t%3;
      iy=$signed({24'd0,oy})+ky-1;ix=$signed({24'd0,ox})+kx-1;
      if(t<kernel_len)begin
       lw[l]<=weights[oc*kernel_len+t];
       if(iy>=0 && iy<height && ix>=0 && ix<width)begin
        addr=ic*plane+iy*width+ix;
        lx[l]<=$signed({1'b0,inputs[addr]})-$signed({1'b0,input_zp});
       end else lx[l]<=0;
      end else begin lx[l]<=0;lw[l]<=0;end
     end
     state<=MAC;
    end
    MAC:begin
     acc<=acc+sum;
     if({16'd0,kernel_index}+4>=kernel_len)state<=RQMUL;
     else begin kernel_index<=kernel_index+4;state<=FETCH;end
    end
    RQMUL:begin product<=acc*multipliers[oc[MW-1:0]];state<=RQROUND;end
    RQROUND:begin quant_value<=rounded;state<=EMIT;end
    EMIT:if(!route[1] || pool_ready)begin
     if(route[0])begin conv_results[out_index[CW-1:0]]<=quant_value;captured<=captured+1;end
     if({16'd0,out_index}+1>=total)begin state<=IDLE;rsp_valid<=1;rsp_payload_outputs_0<=total;end
     else begin
      out_index<=out_index+1;kernel_index<=0;acc<=0;state<=FETCH;
      if(ox==width-1)begin
       ox<=0;if(oy==height-1)begin oy<=0;oc<=oc+1;end else oy<=oy+1;
      end else ox<=ox+1;
     end
    end
    default:;
   endcase
  end
 end
endmodule
