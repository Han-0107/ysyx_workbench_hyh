
module npc (
    input wire clk,
    input wire rst,
    output wire [63:0] inst,                // instructions from IM
    output wire [63:0] pc                   // valus of pc
);

    // IFU out
    wire [31:0] inst_if_o;
    wire [63:0] inst_addr_if_o;
    
    // IDU out
    wire [4:0] rs1_addr_id_o;
    wire [4:0] rs2_addr_id_o;
    wire [63:0] op1_o;
    wire [63:0] op2_o;
    wire [63:0] op3_o;
    wire [63:0] op1_jump;
    wire [63:0] op2_jump;
    wire [6:0] inst_type_o;
    wire [2:0] inst_funct3_o;
    wire [6:0] inst_funct7_o;
    wire [4:0] reg_waddr_id_o;
    wire reg_we_id_o;
    wire break_en;

    // EXU out
    wire reg_we_ex_o;
    wire [4:0] reg_waddr_ex_o;
    wire jump_flag;
    wire [63:0] jump_addr;
    wire [63:0] reg_wdata_ex_o;

    // REG out
    wire [63:0] rdata1_o;
    wire [63:0] rdata2_o;


    IFU ifu1(
        .clk(clk),
        .rst(rst),
        .inst_i(inst),             
        .break_en(break_en),
        .inst_o(inst_if_o),
        .inst_addr_o(inst_addr_if_o),
        .pc_o(pc),    
        .jump_addr_i(jump_addr),
        .jump_flag_i(jump_flag)
    );

    IDU idu1(
        .inst_i(inst_if_o),
        .inst_addr_i(inst_addr_if_o),
        .rs1_data_i(rdata1_o),
        .rs2_data_i(rdata2_o),
        .rs1_addr_o(rs1_addr_id_o),
        .rs2_addr_o(rs2_addr_id_o),
        .op1_o(op1_o),
        .op2_o(op2_o),
        .op3_o(op3_o),
        .op1_jump_o(op1_jump),
        .op2_jump_o(op2_jump),
        .inst_type_o(inst_type_o),
        .inst_funct3_o(inst_funct3_o),
        .inst_funct7_o(inst_funct7_o),
        .reg_waddr_o(reg_waddr_id_o),
        .reg_we_o(reg_we_id_o),
        .break_en(break_en)
    );

    EXU exu1(
        .clk(clk),
        .op1_i(op1_o),
        .op2_i(op2_o),
        .op3_i(op3_o),
        .op1_jump_i(op1_jump),
        .op2_jump_i(op2_jump),
        .inst_type_i(inst_type_o),
        .inst_funct3_i(inst_funct3_o),
        .inst_funct7_i(inst_funct7_o),
        .reg_waddr_i(reg_waddr_id_o),
        .reg_we_i(reg_we_id_o),
        .reg_we_o(reg_we_ex_o),
        .reg_waddr_o(reg_waddr_ex_o),
        .reg_wdata_o(reg_wdata_ex_o),
        .jump_addr_o(jump_addr),
        .jump_flag_o(jump_flag)
    );

    REG reg1(
        .clk(clk),
        .rst(rst),
        .we_i(reg_we_ex_o),
        .waddr_i(reg_waddr_ex_o),
        .wdata_i(reg_wdata_ex_o),
        .raddr1_i(rs1_addr_id_o),
        .raddr2_i(rs2_addr_id_o),
        .rdata1_o(rdata1_o),
        .rdata2_o(rdata2_o)
    );
endmodule
