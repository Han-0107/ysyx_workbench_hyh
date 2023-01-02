import "DPI-C" function void pmem_read(input longint raddr, output longint rdata);
import "DPI-C" function void pmem_write(input longint waddr, input longint wdata, input byte mask);

module MEM(ren, wen, raddr, rdata, waddr, wdata, mask);
  input             ren;
  input             wen;
  input  reg [63:0] raddr;
  output reg [63:0] rdata;
  input  reg [63:0] waddr;
  input  reg [63:0] wdata;
  input  reg [7:0]  mask;

  always @(ren, wen) begin
    if (ren) 
        pmem_read(raddr, rdata);
    else 
        rdata = 64'b0;
    if (wen) 
        pmem_write(waddr, wdata, mask);
  end
endmodule
