module MnistMac4(
 input signed [8:0] x0,x1,x2,x3,
 input signed [7:0] w0,w1,w2,w3,
 output signed [31:0] sum
);
 wire signed [16:0] p0=x0*w0, p1=x1*w1, p2=x2*w2, p3=x3*w3;
 assign sum={{15{p0[16]}},p0}+{{15{p1[16]}},p1}+{{15{p2[16]}},p2}+{{15{p3[16]}},p3};
endmodule
