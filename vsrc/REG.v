import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);

module REG (
    input wire clk,
    input wire rst,

    // from EXU
    input wire we_i,                    // 写寄存器标志
    input wire[4:0] waddr_i,            // 写寄存器地址
    input wire[63:0] wdata_i,           // 写寄存器数据

    // from IDU
    input wire[4:0] raddr1_i,           // 读寄存器1地址

    // to IDU
    output reg[63:0] rdata1_o,          // 读寄存器1数据

    // from IDU
    input wire[4:0] raddr2_i,           // 读寄存器2地址

    // to IDU
    output reg[63:0] rdata2_o           // 读寄存器2数据
);

    reg [63:0] regs[0:31];

    initial set_gpr_ptr(regs);

    // 写寄存器
    always @ (posedge clk) begin
        if (rst == 0) begin
            // 优先ex模块写操作
            if ((we_i == 1'b1) && (waddr_i != 0)) begin
                regs[waddr_i] <= wdata_i;
            end 
            else begin
                regs[waddr_i] <= regs[waddr_i];
            end
        end
        else begin
            regs[waddr_i] <= regs[waddr_i];
        end
    end

    // 读寄存器1
    always @ (*) begin
        if (raddr1_i == 0) begin
            rdata1_o = 0;
        end 
        // else if (raddr1_i == waddr_i && we_i == 1'b1) begin     // 如果读地址等于写地址，并且正在写操作，则直接返回写数据
        //     rdata1_o = wdata_i;
        // end 
        else begin
            rdata1_o = regs[raddr1_i];
        end
    end

    // 读寄存器2
    always @ (*) begin
        if (raddr2_i == 0) begin
            rdata2_o = 0;
        end 
        // else if (raddr2_i == waddr_i && we_i == 1'b1) begin     // 如果读地址等于写地址，并且正在写操作，则直接返回写数据
        //     rdata2_o = wdata_i;
        // end 
        else begin
            rdata2_o = regs[raddr2_i];
        end
    end

endmodule
