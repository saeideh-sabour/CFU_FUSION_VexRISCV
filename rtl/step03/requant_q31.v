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
