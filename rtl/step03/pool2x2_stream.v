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
