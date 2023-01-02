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

import "DPI-C" function void no_match();
import "DPI-C" function void pmem_read_l(input longint raddr, output longint rdata);
import "DPI-C" function void pmem_write_s(input longint waddr, input longint wdata, input byte mask);
module EXU (

    input   clk,
    
    //from IDU
    input  wire [63:0] op1_i,
    input  wire [63:0] op2_i,
    input  wire [63:0] op3_i,
    input  wire [63:0] op1_jump_i,
    input  wire [63:0] op2_jump_i,
    input  wire [6:0] inst_type_i,
    input  wire [2:0] inst_funct3_i,
    input  wire [6:0] inst_funct7_i,
    input  wire [4:0] reg_waddr_i,
    input  wire reg_we_i,

    // to REG
    output reg reg_we_o,                     
    output wire [4:0] reg_waddr_o,           
    output reg [63:0] reg_wdata_o,          

    // to IFU
    output wire jump_flag_o,
    output wire [63:0] jump_addr_o
);
    wire [63:0] op1_add_op2;
    wire [63:0] op1_jump_add_op2_jump;
    wire op1_eq_op2;
    wire [63:0] op1_mul_op2;
    wire [63:0] op1_sub_op2;
    wire op1_ge_op2_signed;
    wire op1_ge_op2_unsigned;
    wire [63:0] op1_movl_l_op3;
    wire [63:0] op1_movr_l_op3;
    wire [63:0] op1_movl_a_op3;
    wire [63:0] op1_movr_a_op3;
    wire [31:0] op1_movl64r_l_op2; 
    wire [31:0] op1_movr64r_a_op2;  
    wire [31:0] op1_div_op2;
    wire [31:0] op1_rem_op2;
    wire [31:0] op1_movr64i_l_op3;
    wire [31:0] op1_movr64i_a_op3;
    wire [31:0] op1_movl64i_l_op3;
    wire [31:0] op1_movr64r_l_op2;
    wire signed [31:0] op1_h_temp;
    wire signed [63:0] op1_temp;

    assign reg_waddr_o = reg_waddr_i;
    assign op1_add_op2 = op1_i + op2_i;
    assign op1_jump_add_op2_jump = op1_jump_i + op2_jump_i;
    assign op1_eq_op2 = (op1_i == op2_i);
    assign op1_mul_op2 = op1_i * op2_i;
    assign op1_sub_op2 = op1_i - op2_i;
    assign op1_ge_op2_signed = ($signed(op1_i) >= $signed(op2_i));
    assign op1_ge_op2_unsigned = (op1_i >= op2_i);
    assign op1_div_op2 = op1_i[31:0] / op2_i[31:0];
    assign op1_rem_op2 = op1_i[31:0] % op2_i[31:0];

    assign op1_h_temp = op1_i[31:0];
    assign op1_temp = op1_i;
    assign op1_movl_l_op3 = op1_i << op3_i[5:0];
    assign op1_movr_l_op3 = op1_i >> op3_i[5:0];
    assign op1_movl_a_op3 = op1_temp <<< op3_i[5:0];
    assign op1_movr_a_op3 = op1_temp >>> op3_i[5:0];     
    assign op1_movr64i_l_op3 = op1_i[31:0] >> op3_i[5:0];
    assign op1_movr64i_a_op3 = op1_h_temp >>> op3_i[5:0];
    assign op1_movl64i_l_op3 = op1_i[31:0] << op3_i[5:0];
    assign op1_movr64r_l_op2 = op1_i[31:0] >> op2_i[4:0];
    assign op1_movl64r_l_op2 = op1_i[31:0] << op2_i[4:0];
    assign op1_movr64r_a_op2 = op1_h_temp >>> op2_i[4:0];

    reg mem_wen;
    reg [7:0] mask;
    reg [63:0] mem_rdata;
    reg [63:0] mem_raddr;
    reg [63:0] mem_wdata;
    reg [63:0] mem_waddr;

  always @(*) begin
    mem_wen = 0;
    mask = 0;
    mem_rdata = 0;
    mem_raddr = 0;
    mem_wdata = 0;
    mem_waddr = 0;

    case (inst_type_i)
        `INST_TYPE_R: begin
            case(inst_funct7_i)
                7'b0000000: begin
                    case (inst_funct3_i)
                        3'b000: begin                          // add
                            reg_wdata_o = op1_add_op2;
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;
                        end
                        3'b111: begin                           // and
                            reg_wdata_o = op1_i & op2_i;
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                            
                        end
                        3'b010: begin                           // slt
                            reg_wdata_o = {63'b0, ~op1_ge_op2_signed};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                                
                        end
                        3'b011: begin                           // sltu
                            reg_wdata_o = {63'b0, ~op1_ge_op2_unsigned};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                              
                        end
                        3'b110: begin                           // or
                            reg_wdata_o = op1_i | op2_i;
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                            
                        end
                        default: begin
                            no_match();
                        end
                    endcase
                end
                7'b0100000: begin                           
                    case(inst_funct3_i)
                        3'b000: begin                          // sub
                            reg_wdata_o = op1_sub_op2;
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;
                        end
                        default: begin
                            no_match();
                        end                        
                        endcase
                end
                7'b0000001: begin
                    case(inst_funct3_i)
                        3'b000: begin                          // mul
                            reg_wdata_o = op1_mul_op2;
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;
                        end
                        3'b101: begin                           // divu
                            reg_wdata_o = {32'b0, op1_div_op2};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                            
                        end                        
                        default: begin
                            no_match();
                        end
                    endcase
                end
                default: begin
                    no_match();
                end                  
            endcase
        end

        `INST_TYPE_I: begin
            case(inst_funct3_i)
                3'b000: begin                               // addi
                    reg_wdata_o = op1_add_op2;
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b011: begin                               // sltiu
                    reg_wdata_o = {63'b0, ~op1_ge_op2_unsigned};
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b101: begin                               
                    case(inst_funct7_i[6:1])
                        6'b000000: begin                   // srli
                            reg_wdata_o = op1_movr_l_op3;      
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                              
                        end
                        6'b010000: begin                   // srai
                            reg_wdata_o = op1_movr_a_op3;      
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;  
                        end
                        default: begin
                            no_match();
                        end  
                    endcase
                  
                end
                3'b001: begin                               // slli
                    reg_wdata_o = op1_movl_l_op3;      
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                         
                end
                3'b111: begin                               // andi
                    reg_wdata_o = op1_i & op2_i;
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                3'b100: begin                               // xori
                    reg_wdata_o = op1_i ^ op2_i;
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                default: begin
                    no_match();
                end                  
            endcase
        end

        `INST_TYPE_B: begin
            case(inst_funct3_i)
                3'b000: begin                              // beq
                    reg_wdata_o = 0;
                    reg_we_o = reg_we_i;
                    jump_flag_o = op1_eq_op2;
                    jump_addr_o = {64{(op1_eq_op2)}} & op1_jump_add_op2_jump;
                end
                3'b001: begin                              // bne
                    reg_wdata_o = 0;
                    reg_we_o = reg_we_i;
                    jump_flag_o = ~op1_eq_op2;
                    jump_addr_o = {64{(~op1_eq_op2)}} & op1_jump_add_op2_jump;
                end
                3'b100: begin                               // blt
                    reg_wdata_o = 0;
                    reg_we_o = reg_we_i;
                    jump_flag_o = ~op1_ge_op2_signed;
                    jump_addr_o = {64{(~op1_ge_op2_signed)}} & op1_jump_add_op2_jump;                     
                end
                3'b101: begin                               // bge
                    reg_wdata_o = 0;
                    reg_we_o = reg_we_i;
                    jump_flag_o = op1_ge_op2_signed;
                    jump_addr_o = {64{(op1_ge_op2_signed)}} & op1_jump_add_op2_jump;                    
                end
                3'b110: begin                               // bltu
                    reg_wdata_o = 0;
                    reg_we_o = reg_we_i;
                    jump_flag_o = ~op1_ge_op2_unsigned;
                    jump_addr_o = {64{(~op1_ge_op2_unsigned)}} & op1_jump_add_op2_jump;                    
                end
                default: begin
                    no_match();
                end                  
            endcase
        end

        `INST_TYPE_64_I: begin
            case(inst_funct3_i)
                3'b000: begin                              // addiw
                    reg_wdata_o = {{32{op1_add_op2[31]}}, op1_add_op2[31:0]};
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b001: begin                               // slliw
                    reg_wdata_o = (op3_i[5] == 0) ? {{32{op1_movl64i_l_op3[31]}}, op1_movl64i_l_op3[31:0]} : 0;
                    reg_we_o = (op3_i[5] == 0) ? reg_we_i : 0;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                3'b101: begin                              
                    case(inst_funct7_i)
                        7'b0000000: begin                   // srliw
                            reg_wdata_o = {{32{op1_movr64i_l_op3[31]}}, op1_movr64i_l_op3[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                             
                        end
                        7'b0100000: begin                   // sraiw
                            reg_wdata_o = {{32{op1_movr64i_a_op3[31]}}, op1_movr64i_a_op3[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                             
                        end
                        default: begin
                            no_match();
                        end
                    endcase
                       
                end
                default: begin
                    no_match();
                end                  
            endcase
        end

        `INST_TYPE_64_R: begin
            case(inst_funct7_i)
                7'b0000000: begin                           // addw
                    case(inst_funct3_i)
                        3'b000: begin
                            reg_wdata_o = {{32{op1_add_op2[31]}}, op1_add_op2[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;
                        end
                        3'b001: begin                       // sllw
                            reg_wdata_o = {{32{op1_movl64r_l_op2[31]}}, op1_movl64r_l_op2[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                            
                        end
                        3'b101: begin                       // srlw
                            reg_wdata_o = {{32{op1_movr64r_l_op2[31]}}, op1_movr64r_l_op2[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                             
                        end
                        default: begin
                            no_match();
                        end                          
                    endcase
                end
                7'b0100000: begin
                    case(inst_funct3_i)                     // subw
                        3'b000: begin
                            reg_wdata_o = {{32{op1_sub_op2[31]}}, op1_sub_op2[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;
                        end
                        3'b101: begin                       // sraw
                            reg_wdata_o = {{32{op1_movr64r_a_op2[31]}}, op1_movr64r_a_op2[31:0]};
                            reg_we_o = reg_we_i;
                            jump_flag_o = 0;
                            jump_addr_o = 0;                          
                        end
                        default: begin
                            no_match();
                        end                          
                    endcase                    
                end
                7'b0000001: begin                           // mulw
                    case(inst_funct3_i)
                        3'b000: begin
                            jump_flag_o = 1'b0;
                            jump_addr_o = 0;
                            reg_we_o = reg_we_i;
                            reg_wdata_o = {{32{op1_mul_op2[31]}}, op1_mul_op2[31:0]};                            
                        end
                        3'b100: begin                       // divw
                            jump_flag_o = 1'b0;
                            jump_addr_o = 0;
                            reg_we_o = reg_we_i;
                            reg_wdata_o = {{32{op1_div_op2[31]}}, op1_div_op2};                             
                        end
                        3'b110: begin                       // remw
                            jump_flag_o = 1'b0;
                            jump_addr_o = 0;
                            reg_we_o = reg_we_i;
                            reg_wdata_o = {{32{op1_rem_op2[31]}}, op1_rem_op2};                             
                        end
                        default: begin
                            no_match();
                        end                           
                    endcase
                end
                default: begin
                    no_match();
                end  
            endcase
        end

        `INST_TYPE_S: begin
            case(inst_funct3_i)
                3'b011: begin                               // sd
                    mem_wen = 1'b1;
                    mask = 8'b11111111;                            
                    mem_wdata = op2_i;
                    mem_waddr = op1_i + op3_i;
                    // pmem_write_s(mem_waddr, mem_wdata, mask);
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b010: begin                               // sw
                    mem_wen = 1'b1;
                    mask = 8'b00001111;                           
                    mem_wdata = op2_i;
                    mem_waddr = op1_i + op3_i;
                    // pmem_write_s(mem_waddr, mem_wdata, mask);
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                3'b001: begin                               // sh
                    mem_wen = 1'b1;
                    mask = 8'b00000011;                           
                    mem_wdata = op2_i;
                    mem_waddr = op1_i + op3_i;
                    // pmem_write_s(mem_waddr, mem_wdata, mask);
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b000: begin                               // sb
                    mem_wen = 1'b1;
                    mask = 8'b00000001;                           
                    mem_wdata = op2_i;
                    mem_waddr = op1_i + op3_i;
                    // pmem_write_s(mem_waddr, mem_wdata, mask);
                    reg_we_o = reg_we_i;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                default: begin
                    no_match();
                end                
            endcase
        end

        `INST_TYPE_L: begin
            case(inst_funct3_i)
                3'b010: begin                             // lw
                    // mem_ren = 1'b1;
                    mem_raddr = op1_add_op2;
                    pmem_read_l(mem_raddr, mem_rdata);
                    reg_waddr_o = reg_waddr_i;
                    reg_we_o = reg_we_i;
                    reg_wdata_o = {{32{mem_rdata[31]}}, mem_rdata[31:0]};
                    jump_flag_o = 0;
                    jump_addr_o = 0;
                end
                3'b011: begin                             // ld
                    // mem_ren = 1'b1;
                    mem_raddr = op1_add_op2;
                    pmem_read_l(mem_raddr, mem_rdata);
                    reg_waddr_o = reg_waddr_i;
                    reg_we_o = reg_we_i;
                    reg_wdata_o = mem_rdata;
                    jump_flag_o = 0;
                    jump_addr_o = 0;                    
                end
                3'h001: begin                             // lh
                    // mem_ren = 1'b1;
                    mem_raddr = op1_add_op2;
                    pmem_read_l(mem_raddr, mem_rdata);
                    reg_waddr_o = reg_waddr_i;
                    reg_we_o = reg_we_i;
                    reg_wdata_o = {{48{mem_rdata[15]}}, mem_rdata[15:0]};
                    jump_flag_o = 0;
                    jump_addr_o = 0;                        
                end
                3'b101: begin                              // lhu
                    // mem_ren = 1'b1;
                    mem_raddr = op1_add_op2;
                    pmem_read_l(mem_raddr, mem_rdata);
                    reg_waddr_o = reg_waddr_i;
                    reg_we_o = reg_we_i;
                    reg_wdata_o = {48'b0, mem_rdata[15:0]};
                    jump_flag_o = 0;
                    jump_addr_o = 0;                       
                end
                3'b100: begin                              // lbu
                    // mem_ren = 1'b1;
                    mem_raddr = op1_add_op2;
                    pmem_read_l(mem_raddr, mem_rdata);
                    reg_waddr_o = reg_waddr_i;
                    reg_we_o = reg_we_i;
                    reg_wdata_o = {56'b0, mem_rdata[7:0]};
                    jump_flag_o = 0;
                    jump_addr_o = 0;                       
                end
                default: begin
                    no_match();
                end 
            endcase
        end

        `INST_JAL, `INST_JALR: begin                        // jal jalr
            jump_flag_o = 1'b1;
            jump_addr_o = op1_jump_add_op2_jump;
            reg_we_o = reg_we_i;
            reg_wdata_o = op1_add_op2;
        end

        `INST_AUIPC, `INST_LUI: begin                       // auipc lui
            jump_flag_o = 1'b0;
            jump_addr_o = 0;
            reg_we_o = reg_we_i;
            reg_wdata_o = op1_add_op2;
        end

        default: begin
            no_match();
        end

    endcase
    
end

always @(posedge clk ) begin
    if(mem_wen == 1) begin
        pmem_write_s(mem_waddr, mem_wdata, mask);
    end
end

//   MEM mem_ex(
//     .ren(mem_ren),
//     .wen(mem_wen),
//     .raddr(mem_raddr),
//     .rdata(mem_rdata),
//     .waddr(mem_waddr),
//     .wdata(mem_wdata),
//     .mask(mask)
//   );

endmodule
