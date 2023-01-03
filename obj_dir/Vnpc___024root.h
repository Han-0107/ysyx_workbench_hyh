// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vnpc.h for the primary calling header

#ifndef VERILATED_VNPC___024ROOT_H_
#define VERILATED_VNPC___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vnpc__Syms;
class Vnpc___024unit;


//----------

VL_MODULE(Vnpc___024root) {
  public:
    // CELLS
    Vnpc___024unit* __PVT____024unit;

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT64(inst,63,0);
    VL_OUT64(pc,63,0);

    // LOCAL SIGNALS
    CData/*4:0*/ npc__DOT__rs1_addr_id_o;
    CData/*4:0*/ npc__DOT__rs2_addr_id_o;
    CData/*6:0*/ npc__DOT__inst_type_o;
    CData/*2:0*/ npc__DOT__inst_funct3_o;
    CData/*6:0*/ npc__DOT__inst_funct7_o;
    CData/*4:0*/ npc__DOT__reg_waddr_id_o;
    CData/*0:0*/ npc__DOT__reg_we_id_o;
    CData/*0:0*/ npc__DOT__break_en;
    CData/*0:0*/ npc__DOT__reg_we_ex_o;
    CData/*4:0*/ npc__DOT__reg_waddr_ex_o;
    CData/*0:0*/ npc__DOT__jump_flag;
    CData/*0:0*/ npc__DOT__exu1__DOT__mem_wen;
    CData/*7:0*/ npc__DOT__exu1__DOT__mask;
    QData/*63:0*/ npc__DOT__op1_o;
    QData/*63:0*/ npc__DOT__op2_o;
    QData/*63:0*/ npc__DOT__op3_o;
    QData/*63:0*/ npc__DOT__op1_jump;
    QData/*63:0*/ npc__DOT__op2_jump;
    QData/*63:0*/ npc__DOT__jump_addr;
    QData/*63:0*/ npc__DOT__reg_wdata_ex_o;
    QData/*63:0*/ npc__DOT__ifu1__DOT__pc_cnt;
    QData/*63:0*/ npc__DOT__exu1__DOT__mem_wdata;
    QData/*63:0*/ npc__DOT__exu1__DOT__mem_waddr;
    VlUnpacked<QData/*63:0*/, 32> npc__DOT__reg1__DOT__regs;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*4:0*/ __Vchglast__TOP__npc__DOT__rs1_addr_id_o;
    CData/*4:0*/ __Vchglast__TOP__npc__DOT__rs2_addr_id_o;
    QData/*63:0*/ __Vtask_pmem_read__0__rdata;
    QData/*63:0*/ __Vtask_pmem_read_l__49__rdata;
    QData/*63:0*/ __Vtask_pmem_read_l__50__rdata;
    QData/*63:0*/ __Vtask_pmem_read_l__51__rdata;
    QData/*63:0*/ __Vtask_pmem_read_l__52__rdata;
    QData/*63:0*/ __Vtask_pmem_read_l__53__rdata;

    // INTERNAL VARIABLES
    Vnpc__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vnpc___024root);  ///< Copying not allowed
  public:
    Vnpc___024root(const char* name);
    ~Vnpc___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vnpc__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
