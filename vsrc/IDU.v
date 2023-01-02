`define INST_TYPE_R     7'b0110011
`define INST_TYPE_N_CSR 7'b1110011
`define INST_TYPE_I     7'b0010011
`define INST_TYPE_S     7'b0100011
`define INST_JAL        7'b1101111
`define INST_JALR       7'b1100111
`define INST_AUIPC      7'b0010111
`define INST_LUI        7'b0110111
`define INST_TYPE_64_I  7'b0011011
`define INST_TYPE_B     7'b1100011
`define INST_TYPE_L     7'b0000011
`define INST_TYPE_64_R  7'b0111011
`define INST_MULW       7'b0111011

import "DPI-C" function void ebreak();

module IDU (

    // from IFU
    input [31:0] inst_i,
    input [63:0] inst_addr_i,

    //from REG
    input wire [63:0] rs1_data_i,
    input wire [63:0] rs2_data_i,

    //to REG
    output reg [4:0] rs1_addr_o,
    output reg [4:0] rs2_addr_o,

    //to EXU
    output reg [63:0] op1_o,
    output reg [63:0] op2_o,
    output reg [63:0] op3_o,
    output reg [63:0] op1_jump_o,
    output reg [63:0] op2_jump_o,
    output reg [6:0] inst_type_o,
    output reg [2:0] inst_funct3_o,
    output reg [6:0] inst_funct7_o,
    output reg [4:0] reg_waddr_o,
    output reg reg_we_o,

    // to IFU
    output reg break_en
);
    wire[6:0] opcode = inst_i[6:0];
    wire[2:0] funct3 = inst_i[14:12];
    wire[6:0] funct7 = inst_i[31:25];
    wire[4:0] rd = inst_i[11:7];
    wire[4:0] rs1 = inst_i[19:15];
    wire[4:0] rs2 = inst_i[24:20];

  always @(*) begin
    // rs1_addr_o = inst_i[19:15];
    // rs2_addr_o = inst_i[24:20];

    // op1_o = 64'b0;
    // op2_o = 64'b0;
    // op3_o = 64'b0;
    // op1_jump_o = 64'b0;
    // op2_jump_o = 64'b0;
    // inst_type_o = 7'b0;
    // inst_funct3_o = 3'b0;
    // inst_funct7_o = 7'b0;
    // reg_waddr_o = 5'b0;
    // reg_we_o = 1'b0;

    if(inst_i == 32'h00100073) begin            // ebreak
        break_en = 1'b1;
        rs1_addr_o = 0;
        rs2_addr_o = 0;
        inst_type_o = 7'b0;
        inst_funct3_o = 3'b0;
        inst_funct7_o = 7'b0;
        reg_waddr_o = 5'b0;
        reg_we_o = 1'b0;
        op1_o = 64'b0;
        op2_o = 64'b0;
        op3_o = 64'b0;
        op1_jump_o = 64'b0;
        op2_jump_o = 64'b0;
        ebreak();
    end

    else begin
        break_en = 1'b0;
        case(opcode)
            `INST_TYPE_R: begin
                inst_type_o = `INST_TYPE_R;
                inst_funct3_o = funct3;
                inst_funct7_o = funct7;
                rs1_addr_o = rs1;
                rs2_addr_o = rs2;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                op1_o = rs1_data_i;
                op2_o = rs2_data_i;
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            `INST_TYPE_I: begin
                inst_type_o = `INST_TYPE_I;
                inst_funct3_o = funct3;
                inst_funct7_o = funct7;
                rs1_addr_o = rs1;
                rs2_addr_o = 0;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                op1_o = rs1_data_i;
                op2_o = {{52{inst_i[31]}}, inst_i[31:20]};
                op3_o = {58'b0, inst_i[25:20]};             // shamt
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            `INST_TYPE_L: begin
                inst_type_o = `INST_TYPE_L;
                inst_funct3_o = funct3;
                inst_funct7_o = 0;
                rs1_addr_o = rs1;
                rs2_addr_o = 0;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                op1_o = rs1_data_i;
                op2_o = {{52{inst_i[31]}}, inst_i[31:20]};
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                                
            end

            `INST_TYPE_S: begin
                inst_type_o = `INST_TYPE_S;
                inst_funct3_o = funct3;
                inst_funct7_o = 0;                
                rs1_addr_o = rs1;
                rs2_addr_o = rs2;
                reg_we_o = 0;
                reg_waddr_o = 0;
                op1_o = rs1_data_i;
                op2_o = rs2_data_i;
                op3_o = {{52{inst_i[31]}}, inst_i[31:25], inst_i[11:7]};
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            `INST_TYPE_B: begin
                inst_type_o = `INST_TYPE_B;
                inst_funct3_o = funct3;
                inst_funct7_o = 0; 
                rs1_addr_o = rs1;
                rs2_addr_o = rs2;
                reg_we_o = 0;
                reg_waddr_o = 0;
                op1_o = rs1_data_i;
                op2_o = rs2_data_i;
                op3_o = 0;
                op1_jump_o = inst_addr_i;
                op2_jump_o = {{52{inst_i[31]}}, inst_i[7], inst_i[30:25], inst_i[11:8], 1'b0};
            end

            // RV64I addition
            `INST_TYPE_64_I: begin
                inst_type_o = `INST_TYPE_64_I;
                inst_funct3_o = funct3;
                inst_funct7_o = funct7;
                rs1_addr_o = rs1;
                rs2_addr_o = 0;
                reg_we_o = 1'b1;
                reg_waddr_o = rd;
                op1_o = rs1_data_i;
                op2_o = {{52{inst_i[31]}}, inst_i[31:20]};
                op3_o = {{58{inst_i[25]}}, inst_i[25:20]};      // shamt
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            `INST_TYPE_64_R: begin
                inst_type_o = `INST_TYPE_64_R;
                inst_funct3_o = funct3;
                inst_funct7_o = funct7;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                rs1_addr_o = rs1;
                rs2_addr_o = rs2;
                op1_o = rs1_data_i;
                op2_o = rs2_data_i;
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;
            end

            // Single types

            `INST_JAL: begin
                inst_type_o = `INST_JAL;
                inst_funct3_o = 0;
                inst_funct7_o = 0;
                rs1_addr_o = 0;
                rs2_addr_o = 0;
                reg_we_o = 1'b1;
                reg_waddr_o = rd;
                op1_o = inst_addr_i;
                op2_o = 64'h4;
                op3_o = 0;
                op1_jump_o = inst_addr_i;
                op2_jump_o = {{44{inst_i[31]}}, inst_i[19:12], inst_i[20], inst_i[30:21], 1'b0};
            end

            `INST_JALR: begin
                inst_type_o = `INST_JALR;
                inst_funct3_o = funct3;
                inst_funct7_o = 0;
                rs1_addr_o = rs1;
                rs2_addr_o = 0;
                reg_waddr_o = rd;         // Default x1
                reg_we_o = 1'b1;
                op1_o = inst_addr_i;
                op2_o = 64'h4;
                op3_o = 0;
                op1_jump_o = rs1_data_i;
                op2_jump_o = {{52{inst_i[31]}}, inst_i[31:20]};
            end

            `INST_AUIPC: begin
                inst_type_o = `INST_AUIPC;
                inst_funct3_o = 0;
                inst_funct7_o = 0;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                rs1_addr_o = 0;
                rs2_addr_o = 0;
                op1_o = inst_addr_i;
                op2_o = {{32{inst_i[31]}}, inst_i[31:12], 12'b0};
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            `INST_LUI: begin
                inst_type_o = `INST_LUI;
                inst_funct3_o = 0;
                inst_funct7_o = 0;
                reg_waddr_o = rd;
                reg_we_o = 1'b1;
                rs1_addr_o = 0;
                rs2_addr_o = 0;
                op1_o = {{32{inst_i[31]}}, inst_i[31:12], 12'b0};
                op2_o = 0;
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end

            default: begin
                inst_type_o = 0;
                inst_funct3_o = 0;
                inst_funct7_o = 0;
                reg_waddr_o = 0;
                reg_we_o = 0;
                rs1_addr_o = 0;
                rs2_addr_o = 0;
                op1_o = 0;
                op2_o = 0;
                op3_o = 64'b0;
                op1_jump_o = 64'b0;
                op2_jump_o = 64'b0;                
            end
        endcase
    end
  end
    
endmodule
