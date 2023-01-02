
module IFU (
    input wire clk,
    input wire rst,

    // from IDU
    input wire break_en,

    // from EXU
    input wire [63:0] jump_addr_i,
    input wire jump_flag_i,

    // to IDU
    output wire [31:0] inst_o,
    output wire [63:0] inst_addr_o,

    // to IM (instruction memory, made by C++)
    output wire [63:0] inst_i,
    output wire [63:0] pc_o 
);

  reg [63:0] pc_cnt = 64'h80000000;
  
  always @(posedge clk) begin
    if(rst == 1'b1 || break_en == 1'b1) begin
        pc_cnt <= 64'h80000000;
    end

    else if(jump_flag_i == 1'b1) begin
        pc_cnt <= jump_addr_i;
    end

    else begin
        pc_cnt <= pc_cnt + 64'h00000004;
    end
  end

  // always @(*) begin
  //   pmem_read(pc_cnt, inst_i);
  // end

  MEM mem_if(
    .ren(1'b1),
    .wen(1'b0),
    .raddr(pc_cnt),
    .rdata(inst_i),
    .waddr(0),
    .wdata(0),
    .mask(0)
  );

  assign inst_o = inst_i[31:0];

  assign inst_addr_o = pc_cnt;          //将pc值发给C++实现的存储器，读取对应的指令并收到inst_i

  assign pc_o = pc_cnt;

endmodule
