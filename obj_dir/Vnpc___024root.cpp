// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vnpc.h for the primary calling header

#include "Vnpc___024root.h"
#include "Vnpc__Syms.h"

#include "verilated_dpi.h"

//==========

void Vnpc___024unit____Vdpiimwrap_pmem_write_s_TOP____024unit(QData/*63:0*/ waddr, QData/*63:0*/ wdata, CData/*7:0*/ mask);
void Vnpc___024unit____Vdpiimwrap_pmem_read_TOP____024unit(QData/*63:0*/ raddr, QData/*63:0*/ &rdata);

VL_INLINE_OPT void Vnpc___024root___sequent__TOP__1(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___sequent__TOP__1\n"); );
    // Variables
    CData/*4:0*/ __Vdlyvdim0__npc__DOT__reg1__DOT__regs__v0;
    QData/*63:0*/ __Vdlyvval__npc__DOT__reg1__DOT__regs__v0;
    // Body
    if (vlSelf->npc__DOT__exu1__DOT__mem_wen) {
        Vnpc___024unit____Vdpiimwrap_pmem_write_s_TOP____024unit(vlSelf->npc__DOT__exu1__DOT__mem_waddr, vlSelf->npc__DOT__exu1__DOT__mem_wdata, (IData)(vlSelf->npc__DOT__exu1__DOT__mask));
    }
    vlSelf->npc__DOT__ifu1__DOT__pc_cnt = (((IData)(vlSelf->rst) 
                                            | (IData)(vlSelf->npc__DOT__break_en))
                                            ? 0x80000000ULL
                                            : ((IData)(vlSelf->npc__DOT__jump_flag)
                                                ? vlSelf->npc__DOT__jump_addr
                                                : (4ULL 
                                                   + vlSelf->npc__DOT__ifu1__DOT__pc_cnt)));
    __Vdlyvval__npc__DOT__reg1__DOT__regs__v0 = ((IData)(vlSelf->rst)
                                                  ? 
                                                 vlSelf->npc__DOT__reg1__DOT__regs
                                                 [vlSelf->npc__DOT__reg_waddr_ex_o]
                                                  : 
                                                 (((IData)(vlSelf->npc__DOT__reg_we_ex_o) 
                                                   & (0U 
                                                      != (IData)(vlSelf->npc__DOT__reg_waddr_ex_o)))
                                                   ? vlSelf->npc__DOT__reg_wdata_ex_o
                                                   : 
                                                  vlSelf->npc__DOT__reg1__DOT__regs
                                                  [vlSelf->npc__DOT__reg_waddr_ex_o]));
    __Vdlyvdim0__npc__DOT__reg1__DOT__regs__v0 = vlSelf->npc__DOT__reg_waddr_ex_o;
    vlSelf->npc__DOT__reg1__DOT__regs[__Vdlyvdim0__npc__DOT__reg1__DOT__regs__v0] 
        = __Vdlyvval__npc__DOT__reg1__DOT__regs__v0;
    vlSelf->pc = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
    Vnpc___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelf->npc__DOT__ifu1__DOT__pc_cnt, vlSelf->__Vtask_pmem_read__0__rdata);
    vlSelf->inst = vlSelf->__Vtask_pmem_read__0__rdata;
}

void Vnpc___024unit____Vdpiimwrap_ebreak_TOP____024unit();
void Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
void Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(QData/*63:0*/ raddr, QData/*63:0*/ &rdata);

VL_INLINE_OPT void Vnpc___024root___combo__TOP__4(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___combo__TOP__4\n"); );
    // Variables
    CData/*0:0*/ npc__DOT__exu1__DOT__op1_eq_op2;
    CData/*0:0*/ npc__DOT__exu1__DOT__op1_ge_op2_signed;
    CData/*0:0*/ npc__DOT__exu1__DOT__op1_ge_op2_unsigned;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movl64r_l_op2;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movr64r_a_op2;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_div_op2;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_rem_op2;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movr64i_l_op3;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movr64i_a_op3;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movl64i_l_op3;
    IData/*31:0*/ npc__DOT__exu1__DOT__op1_movr64r_l_op2;
    QData/*63:0*/ npc__DOT__rdata1_o;
    QData/*63:0*/ npc__DOT__rdata2_o;
    QData/*63:0*/ npc__DOT__exu1__DOT__op1_add_op2;
    QData/*63:0*/ npc__DOT__exu1__DOT__op1_jump_add_op2_jump;
    QData/*63:0*/ npc__DOT__exu1__DOT__op1_mul_op2;
    QData/*63:0*/ npc__DOT__exu1__DOT__op1_sub_op2;
    QData/*63:0*/ npc__DOT__exu1__DOT__mem_rdata;
    QData/*63:0*/ npc__DOT__exu1__DOT__mem_raddr;
    // Body
    npc__DOT__rdata1_o = ((0U == (IData)(vlSelf->npc__DOT__rs1_addr_id_o))
                           ? 0ULL : vlSelf->npc__DOT__reg1__DOT__regs
                          [vlSelf->npc__DOT__rs1_addr_id_o]);
    npc__DOT__rdata2_o = ((0U == (IData)(vlSelf->npc__DOT__rs2_addr_id_o))
                           ? 0ULL : vlSelf->npc__DOT__reg1__DOT__regs
                          [vlSelf->npc__DOT__rs2_addr_id_o]);
    if ((0x100073U == (IData)(vlSelf->inst))) {
        vlSelf->npc__DOT__break_en = 1U;
        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
        vlSelf->npc__DOT__inst_type_o = 0U;
        vlSelf->npc__DOT__inst_funct3_o = 0U;
        vlSelf->npc__DOT__inst_funct7_o = 0U;
        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
        vlSelf->npc__DOT__reg_we_id_o = 0U;
        vlSelf->npc__DOT__op1_o = 0ULL;
        vlSelf->npc__DOT__op2_o = 0ULL;
        vlSelf->npc__DOT__op3_o = 0ULL;
        vlSelf->npc__DOT__op1_jump = 0ULL;
        vlSelf->npc__DOT__op2_jump = 0ULL;
        Vnpc___024unit____Vdpiimwrap_ebreak_TOP____024unit();
    } else {
        vlSelf->npc__DOT__break_en = 0U;
        if ((1U & (IData)((vlSelf->inst >> 6U)))) {
            if ((1U & (IData)((vlSelf->inst >> 5U)))) {
                if ((1U & (IData)((vlSelf->inst >> 4U)))) {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 3U)))) {
                    if ((1U & (IData)((vlSelf->inst 
                                       >> 2U)))) {
                        if ((1U & (IData)((vlSelf->inst 
                                           >> 1U)))) {
                            if ((1U & (IData)(vlSelf->inst))) {
                                vlSelf->npc__DOT__inst_type_o = 0x6fU;
                                vlSelf->npc__DOT__inst_funct3_o = 0U;
                                vlSelf->npc__DOT__inst_funct7_o = 0U;
                                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                                vlSelf->npc__DOT__reg_we_id_o = 1U;
                                vlSelf->npc__DOT__reg_waddr_id_o 
                                    = (0x1fU & (IData)(
                                                       (vlSelf->inst 
                                                        >> 7U)));
                                vlSelf->npc__DOT__op1_o 
                                    = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
                                vlSelf->npc__DOT__op2_o = 4ULL;
                                vlSelf->npc__DOT__op3_o = 0ULL;
                                vlSelf->npc__DOT__op1_jump 
                                    = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
                                vlSelf->npc__DOT__op2_jump 
                                    = (((- (QData)((IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelf->inst 
                                                                       >> 0x1fU)))))) 
                                        << 0x14U) | (QData)((IData)(
                                                                    ((0xff000U 
                                                                      & ((IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0xcU)) 
                                                                         << 0xcU)) 
                                                                     | ((0x800U 
                                                                         & ((IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x14U)) 
                                                                            << 0xbU)) 
                                                                        | (0x7feU 
                                                                           & ((IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x15U)) 
                                                                              << 1U)))))));
                            } else {
                                vlSelf->npc__DOT__inst_type_o = 0U;
                                vlSelf->npc__DOT__inst_funct3_o = 0U;
                                vlSelf->npc__DOT__inst_funct7_o = 0U;
                                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                                vlSelf->npc__DOT__reg_we_id_o = 0U;
                                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                                vlSelf->npc__DOT__op1_o = 0ULL;
                                vlSelf->npc__DOT__op2_o = 0ULL;
                                vlSelf->npc__DOT__op3_o = 0ULL;
                                vlSelf->npc__DOT__op1_jump = 0ULL;
                                vlSelf->npc__DOT__op2_jump = 0ULL;
                            }
                        } else {
                            vlSelf->npc__DOT__inst_type_o = 0U;
                            vlSelf->npc__DOT__inst_funct3_o = 0U;
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                            vlSelf->npc__DOT__reg_we_id_o = 0U;
                            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__op1_o = 0ULL;
                            vlSelf->npc__DOT__op2_o = 0ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        }
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 2U)))) {
                    if ((1U & (IData)((vlSelf->inst 
                                       >> 1U)))) {
                        if ((1U & (IData)(vlSelf->inst))) {
                            vlSelf->npc__DOT__inst_type_o = 0x67U;
                            vlSelf->npc__DOT__inst_funct3_o 
                                = (7U & (IData)((vlSelf->inst 
                                                 >> 0xcU)));
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__rs1_addr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 0xfU)));
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 7U)));
                            vlSelf->npc__DOT__reg_we_id_o = 1U;
                            vlSelf->npc__DOT__op1_o 
                                = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
                            vlSelf->npc__DOT__op2_o = 4ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump 
                                = npc__DOT__rdata1_o;
                            vlSelf->npc__DOT__op2_jump 
                                = (((- (QData)((IData)(
                                                       (1U 
                                                        & (IData)(
                                                                  (vlSelf->inst 
                                                                   >> 0x1fU)))))) 
                                    << 0xcU) | (QData)((IData)(
                                                               (0xfffU 
                                                                & (IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x14U))))));
                        } else {
                            vlSelf->npc__DOT__inst_type_o = 0U;
                            vlSelf->npc__DOT__inst_funct3_o = 0U;
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                            vlSelf->npc__DOT__reg_we_id_o = 0U;
                            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__op1_o = 0ULL;
                            vlSelf->npc__DOT__op2_o = 0ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        }
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 1U)))) {
                    if ((1U & (IData)(vlSelf->inst))) {
                        vlSelf->npc__DOT__inst_type_o = 0x63U;
                        vlSelf->npc__DOT__inst_funct3_o 
                            = (7U & (IData)((vlSelf->inst 
                                             >> 0xcU)));
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 0xfU)));
                        vlSelf->npc__DOT__rs2_addr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 0x14U)));
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                        vlSelf->npc__DOT__op2_o = npc__DOT__rdata2_o;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump 
                            = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
                        vlSelf->npc__DOT__op2_jump 
                            = (((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelf->inst 
                                                               >> 0x1fU)))))) 
                                << 0xcU) | (QData)((IData)(
                                                           ((0x800U 
                                                             & ((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 7U)) 
                                                                << 0xbU)) 
                                                            | ((0x7e0U 
                                                                & ((IData)(
                                                                           (vlSelf->inst 
                                                                            >> 0x19U)) 
                                                                   << 5U)) 
                                                               | (0x1eU 
                                                                  & ((IData)(
                                                                             (vlSelf->inst 
                                                                              >> 8U)) 
                                                                     << 1U)))))));
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            }
        } else if ((1U & (IData)((vlSelf->inst >> 5U)))) {
            if ((1U & (IData)((vlSelf->inst >> 4U)))) {
                if ((1U & (IData)((vlSelf->inst >> 3U)))) {
                    if ((1U & (IData)((vlSelf->inst 
                                       >> 2U)))) {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    } else if ((1U & (IData)((vlSelf->inst 
                                              >> 1U)))) {
                        if ((1U & (IData)(vlSelf->inst))) {
                            vlSelf->npc__DOT__inst_type_o = 0x3bU;
                            vlSelf->npc__DOT__inst_funct3_o 
                                = (7U & (IData)((vlSelf->inst 
                                                 >> 0xcU)));
                            vlSelf->npc__DOT__inst_funct7_o 
                                = (0x7fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 0x19U)));
                            vlSelf->npc__DOT__reg_waddr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 7U)));
                            vlSelf->npc__DOT__reg_we_id_o = 1U;
                            vlSelf->npc__DOT__rs1_addr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 0xfU)));
                            vlSelf->npc__DOT__rs2_addr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 0x14U)));
                            vlSelf->npc__DOT__op1_o 
                                = npc__DOT__rdata1_o;
                            vlSelf->npc__DOT__op2_o 
                                = npc__DOT__rdata2_o;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        } else {
                            vlSelf->npc__DOT__inst_type_o = 0U;
                            vlSelf->npc__DOT__inst_funct3_o = 0U;
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                            vlSelf->npc__DOT__reg_we_id_o = 0U;
                            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__op1_o = 0ULL;
                            vlSelf->npc__DOT__op2_o = 0ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        }
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 2U)))) {
                    if ((1U & (IData)((vlSelf->inst 
                                       >> 1U)))) {
                        if ((1U & (IData)(vlSelf->inst))) {
                            vlSelf->npc__DOT__inst_type_o = 0x37U;
                            vlSelf->npc__DOT__inst_funct3_o = 0U;
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o 
                                = (0x1fU & (IData)(
                                                   (vlSelf->inst 
                                                    >> 7U)));
                            vlSelf->npc__DOT__reg_we_id_o = 1U;
                            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__op1_o 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU))))))) 
                                    << 0x20U) | (QData)((IData)(
                                                                ((IData)(
                                                                         (vlSelf->inst 
                                                                          >> 0xcU)) 
                                                                 << 0xcU))));
                            vlSelf->npc__DOT__op2_o = 0ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        } else {
                            vlSelf->npc__DOT__inst_type_o = 0U;
                            vlSelf->npc__DOT__inst_funct3_o = 0U;
                            vlSelf->npc__DOT__inst_funct7_o = 0U;
                            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                            vlSelf->npc__DOT__reg_we_id_o = 0U;
                            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                            vlSelf->npc__DOT__op1_o = 0ULL;
                            vlSelf->npc__DOT__op2_o = 0ULL;
                            vlSelf->npc__DOT__op3_o = 0ULL;
                            vlSelf->npc__DOT__op1_jump = 0ULL;
                            vlSelf->npc__DOT__op2_jump = 0ULL;
                        }
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 1U)))) {
                    if ((1U & (IData)(vlSelf->inst))) {
                        vlSelf->npc__DOT__inst_type_o = 0x33U;
                        vlSelf->npc__DOT__inst_funct3_o 
                            = (7U & (IData)((vlSelf->inst 
                                             >> 0xcU)));
                        vlSelf->npc__DOT__inst_funct7_o 
                            = (0x7fU & (IData)((vlSelf->inst 
                                                >> 0x19U)));
                        vlSelf->npc__DOT__rs1_addr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 0xfU)));
                        vlSelf->npc__DOT__rs2_addr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 0x14U)));
                        vlSelf->npc__DOT__reg_waddr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 7U)));
                        vlSelf->npc__DOT__reg_we_id_o = 1U;
                        vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                        vlSelf->npc__DOT__op2_o = npc__DOT__rdata2_o;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else if ((1U & (IData)((vlSelf->inst 
                                      >> 3U)))) {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            } else if ((1U & (IData)((vlSelf->inst 
                                      >> 2U)))) {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            } else if ((1U & (IData)((vlSelf->inst 
                                      >> 1U)))) {
                if ((1U & (IData)(vlSelf->inst))) {
                    vlSelf->npc__DOT__inst_type_o = 0x23U;
                    vlSelf->npc__DOT__inst_funct3_o 
                        = (7U & (IData)((vlSelf->inst 
                                         >> 0xcU)));
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o 
                        = (0x1fU & (IData)((vlSelf->inst 
                                            >> 0xfU)));
                    vlSelf->npc__DOT__rs2_addr_id_o 
                        = (0x1fU & (IData)((vlSelf->inst 
                                            >> 0x14U)));
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                    vlSelf->npc__DOT__op2_o = npc__DOT__rdata2_o;
                    vlSelf->npc__DOT__op3_o = (((- (QData)((IData)(
                                                                   (1U 
                                                                    & (IData)(
                                                                              (vlSelf->inst 
                                                                               >> 0x1fU)))))) 
                                                << 0xcU) 
                                               | (QData)((IData)(
                                                                 ((0xfe0U 
                                                                   & ((IData)(
                                                                              (vlSelf->inst 
                                                                               >> 0x19U)) 
                                                                      << 5U)) 
                                                                  | (0x1fU 
                                                                     & (IData)(
                                                                               (vlSelf->inst 
                                                                                >> 7U)))))));
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            }
        } else if ((1U & (IData)((vlSelf->inst >> 4U)))) {
            if ((1U & (IData)((vlSelf->inst >> 3U)))) {
                if ((1U & (IData)((vlSelf->inst >> 2U)))) {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                } else if ((1U & (IData)((vlSelf->inst 
                                          >> 1U)))) {
                    if ((1U & (IData)(vlSelf->inst))) {
                        vlSelf->npc__DOT__inst_type_o = 0x1bU;
                        vlSelf->npc__DOT__inst_funct3_o 
                            = (7U & (IData)((vlSelf->inst 
                                             >> 0xcU)));
                        vlSelf->npc__DOT__inst_funct7_o 
                            = (0x7fU & (IData)((vlSelf->inst 
                                                >> 0x19U)));
                        vlSelf->npc__DOT__rs1_addr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 0xfU)));
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 1U;
                        vlSelf->npc__DOT__reg_waddr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 7U)));
                        vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                        vlSelf->npc__DOT__op2_o = (
                                                   ((- (QData)((IData)(
                                                                       (1U 
                                                                        & (IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x1fU)))))) 
                                                    << 0xcU) 
                                                   | (QData)((IData)(
                                                                     (0xfffU 
                                                                      & (IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x14U))))));
                        vlSelf->npc__DOT__op3_o = (
                                                   ((- (QData)((IData)(
                                                                       (1U 
                                                                        & (IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x19U)))))) 
                                                    << 6U) 
                                                   | (QData)((IData)(
                                                                     (0x3fU 
                                                                      & (IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x14U))))));
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else if ((1U & (IData)((vlSelf->inst 
                                      >> 2U)))) {
                if ((1U & (IData)((vlSelf->inst >> 1U)))) {
                    if ((1U & (IData)(vlSelf->inst))) {
                        vlSelf->npc__DOT__inst_type_o = 0x17U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o 
                            = (0x1fU & (IData)((vlSelf->inst 
                                                >> 7U)));
                        vlSelf->npc__DOT__reg_we_id_o = 1U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = vlSelf->npc__DOT__ifu1__DOT__pc_cnt;
                        vlSelf->npc__DOT__op2_o = (
                                                   ((QData)((IData)(
                                                                    (- (IData)(
                                                                               (1U 
                                                                                & (IData)(
                                                                                (vlSelf->inst 
                                                                                >> 0x1fU))))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     ((IData)(
                                                                              (vlSelf->inst 
                                                                               >> 0xcU)) 
                                                                      << 0xcU))));
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    } else {
                        vlSelf->npc__DOT__inst_type_o = 0U;
                        vlSelf->npc__DOT__inst_funct3_o = 0U;
                        vlSelf->npc__DOT__inst_funct7_o = 0U;
                        vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                        vlSelf->npc__DOT__reg_we_id_o = 0U;
                        vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                        vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                        vlSelf->npc__DOT__op1_o = 0ULL;
                        vlSelf->npc__DOT__op2_o = 0ULL;
                        vlSelf->npc__DOT__op3_o = 0ULL;
                        vlSelf->npc__DOT__op1_jump = 0ULL;
                        vlSelf->npc__DOT__op2_jump = 0ULL;
                    }
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else if ((1U & (IData)((vlSelf->inst 
                                      >> 1U)))) {
                if ((1U & (IData)(vlSelf->inst))) {
                    vlSelf->npc__DOT__inst_type_o = 0x13U;
                    vlSelf->npc__DOT__inst_funct3_o 
                        = (7U & (IData)((vlSelf->inst 
                                         >> 0xcU)));
                    vlSelf->npc__DOT__inst_funct7_o 
                        = (0x7fU & (IData)((vlSelf->inst 
                                            >> 0x19U)));
                    vlSelf->npc__DOT__rs1_addr_id_o 
                        = (0x1fU & (IData)((vlSelf->inst 
                                            >> 0xfU)));
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o 
                        = (0x1fU & (IData)((vlSelf->inst 
                                            >> 7U)));
                    vlSelf->npc__DOT__reg_we_id_o = 1U;
                    vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                    vlSelf->npc__DOT__op2_o = (((- (QData)((IData)(
                                                                   (1U 
                                                                    & (IData)(
                                                                              (vlSelf->inst 
                                                                               >> 0x1fU)))))) 
                                                << 0xcU) 
                                               | (QData)((IData)(
                                                                 (0xfffU 
                                                                  & (IData)(
                                                                            (vlSelf->inst 
                                                                             >> 0x14U))))));
                    vlSelf->npc__DOT__op3_o = (QData)((IData)(
                                                              (0x3fU 
                                                               & (IData)(
                                                                         (vlSelf->inst 
                                                                          >> 0x14U)))));
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                } else {
                    vlSelf->npc__DOT__inst_type_o = 0U;
                    vlSelf->npc__DOT__inst_funct3_o = 0U;
                    vlSelf->npc__DOT__inst_funct7_o = 0U;
                    vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                    vlSelf->npc__DOT__reg_we_id_o = 0U;
                    vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                    vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                    vlSelf->npc__DOT__op1_o = 0ULL;
                    vlSelf->npc__DOT__op2_o = 0ULL;
                    vlSelf->npc__DOT__op3_o = 0ULL;
                    vlSelf->npc__DOT__op1_jump = 0ULL;
                    vlSelf->npc__DOT__op2_jump = 0ULL;
                }
            } else {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            }
        } else if ((1U & (IData)((vlSelf->inst >> 3U)))) {
            vlSelf->npc__DOT__inst_type_o = 0U;
            vlSelf->npc__DOT__inst_funct3_o = 0U;
            vlSelf->npc__DOT__inst_funct7_o = 0U;
            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
            vlSelf->npc__DOT__reg_we_id_o = 0U;
            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
            vlSelf->npc__DOT__op1_o = 0ULL;
            vlSelf->npc__DOT__op2_o = 0ULL;
            vlSelf->npc__DOT__op3_o = 0ULL;
            vlSelf->npc__DOT__op1_jump = 0ULL;
            vlSelf->npc__DOT__op2_jump = 0ULL;
        } else if ((1U & (IData)((vlSelf->inst >> 2U)))) {
            vlSelf->npc__DOT__inst_type_o = 0U;
            vlSelf->npc__DOT__inst_funct3_o = 0U;
            vlSelf->npc__DOT__inst_funct7_o = 0U;
            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
            vlSelf->npc__DOT__reg_we_id_o = 0U;
            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
            vlSelf->npc__DOT__op1_o = 0ULL;
            vlSelf->npc__DOT__op2_o = 0ULL;
            vlSelf->npc__DOT__op3_o = 0ULL;
            vlSelf->npc__DOT__op1_jump = 0ULL;
            vlSelf->npc__DOT__op2_jump = 0ULL;
        } else if ((1U & (IData)((vlSelf->inst >> 1U)))) {
            if ((1U & (IData)(vlSelf->inst))) {
                vlSelf->npc__DOT__inst_type_o = 3U;
                vlSelf->npc__DOT__inst_funct3_o = (7U 
                                                   & (IData)(
                                                             (vlSelf->inst 
                                                              >> 0xcU)));
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = (0x1fU 
                                                   & (IData)(
                                                             (vlSelf->inst 
                                                              >> 0xfU)));
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 
                    (0x1fU & (IData)((vlSelf->inst 
                                      >> 7U)));
                vlSelf->npc__DOT__reg_we_id_o = 1U;
                vlSelf->npc__DOT__op1_o = npc__DOT__rdata1_o;
                vlSelf->npc__DOT__op2_o = (((- (QData)((IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))))) 
                                            << 0xcU) 
                                           | (QData)((IData)(
                                                             (0xfffU 
                                                              & (IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x14U))))));
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            } else {
                vlSelf->npc__DOT__inst_type_o = 0U;
                vlSelf->npc__DOT__inst_funct3_o = 0U;
                vlSelf->npc__DOT__inst_funct7_o = 0U;
                vlSelf->npc__DOT__reg_waddr_id_o = 0U;
                vlSelf->npc__DOT__reg_we_id_o = 0U;
                vlSelf->npc__DOT__rs1_addr_id_o = 0U;
                vlSelf->npc__DOT__rs2_addr_id_o = 0U;
                vlSelf->npc__DOT__op1_o = 0ULL;
                vlSelf->npc__DOT__op2_o = 0ULL;
                vlSelf->npc__DOT__op3_o = 0ULL;
                vlSelf->npc__DOT__op1_jump = 0ULL;
                vlSelf->npc__DOT__op2_jump = 0ULL;
            }
        } else {
            vlSelf->npc__DOT__inst_type_o = 0U;
            vlSelf->npc__DOT__inst_funct3_o = 0U;
            vlSelf->npc__DOT__inst_funct7_o = 0U;
            vlSelf->npc__DOT__reg_waddr_id_o = 0U;
            vlSelf->npc__DOT__reg_we_id_o = 0U;
            vlSelf->npc__DOT__rs1_addr_id_o = 0U;
            vlSelf->npc__DOT__rs2_addr_id_o = 0U;
            vlSelf->npc__DOT__op1_o = 0ULL;
            vlSelf->npc__DOT__op2_o = 0ULL;
            vlSelf->npc__DOT__op3_o = 0ULL;
            vlSelf->npc__DOT__op1_jump = 0ULL;
            vlSelf->npc__DOT__op2_jump = 0ULL;
        }
    }
    vlSelf->npc__DOT__reg_waddr_ex_o = vlSelf->npc__DOT__reg_waddr_id_o;
    npc__DOT__exu1__DOT__op1_jump_add_op2_jump = (vlSelf->npc__DOT__op1_jump 
                                                  + vlSelf->npc__DOT__op2_jump);
    npc__DOT__exu1__DOT__op1_add_op2 = (vlSelf->npc__DOT__op1_o 
                                        + vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_eq_op2 = (vlSelf->npc__DOT__op1_o 
                                       == vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_mul_op2 = (vlSelf->npc__DOT__op1_o 
                                        * vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_sub_op2 = (vlSelf->npc__DOT__op1_o 
                                        - vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_ge_op2_signed = VL_GTES_IQQ(1,64,64, vlSelf->npc__DOT__op1_o, vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_ge_op2_unsigned = (vlSelf->npc__DOT__op1_o 
                                                >= vlSelf->npc__DOT__op2_o);
    npc__DOT__exu1__DOT__op1_div_op2 = VL_DIV_III(32, (IData)(vlSelf->npc__DOT__op1_o), (IData)(vlSelf->npc__DOT__op2_o));
    npc__DOT__exu1__DOT__op1_rem_op2 = VL_MODDIV_III(32, (IData)(vlSelf->npc__DOT__op1_o), (IData)(vlSelf->npc__DOT__op2_o));
    if ((0x1fU >= (0x3fU & (IData)(vlSelf->npc__DOT__op3_o)))) {
        npc__DOT__exu1__DOT__op1_movr64i_l_op3 = ((IData)(vlSelf->npc__DOT__op1_o) 
                                                  >> 
                                                  (0x3fU 
                                                   & (IData)(vlSelf->npc__DOT__op3_o)));
        npc__DOT__exu1__DOT__op1_movr64i_a_op3 = VL_SHIFTRS_III(32,32,6, (IData)(vlSelf->npc__DOT__op1_o), 
                                                                (0x3fU 
                                                                 & (IData)(vlSelf->npc__DOT__op3_o)));
        npc__DOT__exu1__DOT__op1_movl64i_l_op3 = ((IData)(vlSelf->npc__DOT__op1_o) 
                                                  << 
                                                  (0x3fU 
                                                   & (IData)(vlSelf->npc__DOT__op3_o)));
    } else {
        npc__DOT__exu1__DOT__op1_movr64i_l_op3 = 0U;
        npc__DOT__exu1__DOT__op1_movr64i_a_op3 = (- 
                                                  ((IData)(vlSelf->npc__DOT__op1_o) 
                                                   >> 0x1fU));
        npc__DOT__exu1__DOT__op1_movl64i_l_op3 = 0U;
    }
    npc__DOT__exu1__DOT__op1_movr64r_l_op2 = ((IData)(vlSelf->npc__DOT__op1_o) 
                                              >> (0x1fU 
                                                  & (IData)(vlSelf->npc__DOT__op2_o)));
    npc__DOT__exu1__DOT__op1_movl64r_l_op2 = ((IData)(vlSelf->npc__DOT__op1_o) 
                                              << (0x1fU 
                                                  & (IData)(vlSelf->npc__DOT__op2_o)));
    npc__DOT__exu1__DOT__op1_movr64r_a_op2 = VL_SHIFTRS_III(32,32,5, (IData)(vlSelf->npc__DOT__op1_o), 
                                                            (0x1fU 
                                                             & (IData)(vlSelf->npc__DOT__op2_o)));
    vlSelf->npc__DOT__exu1__DOT__mem_wen = 0U;
    vlSelf->npc__DOT__exu1__DOT__mask = 0U;
    npc__DOT__exu1__DOT__mem_rdata = 0ULL;
    npc__DOT__exu1__DOT__mem_raddr = 0ULL;
    vlSelf->npc__DOT__exu1__DOT__mem_wdata = 0ULL;
    vlSelf->npc__DOT__exu1__DOT__mem_waddr = 0ULL;
    if ((0x40U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        if ((0x20U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((0x10U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            } else if ((8U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                        if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                            vlSelf->npc__DOT__jump_flag = 1U;
                            vlSelf->npc__DOT__jump_addr 
                                = npc__DOT__exu1__DOT__op1_jump_add_op2_jump;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = npc__DOT__exu1__DOT__op1_add_op2;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                        vlSelf->npc__DOT__jump_flag = 1U;
                        vlSelf->npc__DOT__jump_addr 
                            = npc__DOT__exu1__DOT__op1_jump_add_op2_jump;
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__reg_wdata_ex_o 
                            = npc__DOT__exu1__DOT__op1_add_op2;
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((4U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                            } else {
                                vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag 
                                    = (1U & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_unsigned)));
                                vlSelf->npc__DOT__jump_addr 
                                    = ((- (QData)((IData)(
                                                          (1U 
                                                           & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_unsigned)))))) 
                                       & npc__DOT__exu1__DOT__op1_jump_add_op2_jump);
                            }
                        } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag 
                                = npc__DOT__exu1__DOT__op1_ge_op2_signed;
                            vlSelf->npc__DOT__jump_addr 
                                = ((- (QData)((IData)(npc__DOT__exu1__DOT__op1_ge_op2_signed))) 
                                   & npc__DOT__exu1__DOT__op1_jump_add_op2_jump);
                        } else {
                            vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag 
                                = (1U & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_signed)));
                            vlSelf->npc__DOT__jump_addr 
                                = ((- (QData)((IData)(
                                                      (1U 
                                                       & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_signed)))))) 
                                   & npc__DOT__exu1__DOT__op1_jump_add_op2_jump);
                        }
                    } else if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag 
                            = (1U & (~ (IData)(npc__DOT__exu1__DOT__op1_eq_op2)));
                        vlSelf->npc__DOT__jump_addr 
                            = ((- (QData)((IData)((1U 
                                                   & (~ (IData)(npc__DOT__exu1__DOT__op1_eq_op2)))))) 
                               & npc__DOT__exu1__DOT__op1_jump_add_op2_jump);
                    } else {
                        vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag 
                            = npc__DOT__exu1__DOT__op1_eq_op2;
                        vlSelf->npc__DOT__jump_addr 
                            = ((- (QData)((IData)(npc__DOT__exu1__DOT__op1_eq_op2))) 
                               & npc__DOT__exu1__DOT__op1_jump_add_op2_jump);
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        }
    } else if ((0x20U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        if ((0x10U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((8U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                        if ((0U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                            if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (1U 
                                                                    & (IData)(
                                                                              (npc__DOT__exu1__DOT__op1_add_op2 
                                                                               >> 0x1fU))))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_add_op2)));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else if ((1U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (npc__DOT__exu1__DOT__op1_movl64r_l_op2 
                                                                    >> 0x1fU))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movl64r_l_op2)));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else if ((5U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (npc__DOT__exu1__DOT__op1_movr64r_l_op2 
                                                                    >> 0x1fU))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movr64r_l_op2)));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else {
                                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                            }
                        } else if ((0x20U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                            if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (1U 
                                                                    & (IData)(
                                                                              (npc__DOT__exu1__DOT__op1_sub_op2 
                                                                               >> 0x1fU))))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_sub_op2)));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else if ((5U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (npc__DOT__exu1__DOT__op1_movr64r_a_op2 
                                                                    >> 0x1fU))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movr64r_a_op2)));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else {
                                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                            }
                        } else if ((1U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                            if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (1U 
                                                                    & (IData)(
                                                                              (npc__DOT__exu1__DOT__op1_mul_op2 
                                                                               >> 0x1fU))))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_mul_op2)));
                            } else if ((4U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (npc__DOT__exu1__DOT__op1_div_op2 
                                                                    >> 0x1fU))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_div_op2)));
                            } else if ((6U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (((QData)((IData)(
                                                        (- (IData)(
                                                                   (npc__DOT__exu1__DOT__op1_rem_op2 
                                                                    >> 0x1fU))))) 
                                        << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_rem_op2)));
                            } else {
                                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                            }
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__reg_wdata_ex_o 
                            = npc__DOT__exu1__DOT__op1_add_op2;
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((0U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                        if ((4U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                    vlSelf->npc__DOT__reg_wdata_ex_o 
                                        = (vlSelf->npc__DOT__op1_o 
                                           & vlSelf->npc__DOT__op2_o);
                                    vlSelf->npc__DOT__reg_we_ex_o 
                                        = vlSelf->npc__DOT__reg_we_id_o;
                                    vlSelf->npc__DOT__jump_flag = 0U;
                                    vlSelf->npc__DOT__jump_addr = 0ULL;
                                } else {
                                    vlSelf->npc__DOT__reg_wdata_ex_o 
                                        = (vlSelf->npc__DOT__op1_o 
                                           | vlSelf->npc__DOT__op2_o);
                                    vlSelf->npc__DOT__reg_we_ex_o 
                                        = vlSelf->npc__DOT__reg_we_id_o;
                                    vlSelf->npc__DOT__jump_flag = 0U;
                                    vlSelf->npc__DOT__jump_addr = 0ULL;
                                }
                            } else {
                                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                            }
                        } else if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (QData)((IData)(
                                                      (1U 
                                                       & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_unsigned)))));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            } else {
                                vlSelf->npc__DOT__reg_wdata_ex_o 
                                    = (QData)((IData)(
                                                      (1U 
                                                       & (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_signed)))));
                                vlSelf->npc__DOT__reg_we_ex_o 
                                    = vlSelf->npc__DOT__reg_we_id_o;
                                vlSelf->npc__DOT__jump_flag = 0U;
                                vlSelf->npc__DOT__jump_addr = 0ULL;
                            }
                        } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        } else {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = npc__DOT__exu1__DOT__op1_add_op2;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        }
                    } else if ((0x20U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                        if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = npc__DOT__exu1__DOT__op1_sub_op2;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else if ((1U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                        if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = npc__DOT__exu1__DOT__op1_mul_op2;
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else if ((5U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (QData)((IData)(npc__DOT__exu1__DOT__op1_div_op2));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else if ((8U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        } else if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((4U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                } else if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        vlSelf->npc__DOT__exu1__DOT__mem_wen = 1U;
                        vlSelf->npc__DOT__exu1__DOT__mask = 0xffU;
                        vlSelf->npc__DOT__exu1__DOT__mem_wdata 
                            = vlSelf->npc__DOT__op2_o;
                        vlSelf->npc__DOT__exu1__DOT__mem_waddr 
                            = (vlSelf->npc__DOT__op1_o 
                               + vlSelf->npc__DOT__op3_o);
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    } else {
                        vlSelf->npc__DOT__exu1__DOT__mem_wen = 1U;
                        vlSelf->npc__DOT__exu1__DOT__mask = 0xfU;
                        vlSelf->npc__DOT__exu1__DOT__mem_wdata 
                            = vlSelf->npc__DOT__op2_o;
                        vlSelf->npc__DOT__exu1__DOT__mem_waddr 
                            = (vlSelf->npc__DOT__op1_o 
                               + vlSelf->npc__DOT__op3_o);
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    }
                } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    vlSelf->npc__DOT__exu1__DOT__mem_wen = 1U;
                    vlSelf->npc__DOT__exu1__DOT__mask = 3U;
                    vlSelf->npc__DOT__exu1__DOT__mem_wdata 
                        = vlSelf->npc__DOT__op2_o;
                    vlSelf->npc__DOT__exu1__DOT__mem_waddr 
                        = (vlSelf->npc__DOT__op1_o 
                           + vlSelf->npc__DOT__op3_o);
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                } else {
                    vlSelf->npc__DOT__exu1__DOT__mem_wen = 1U;
                    vlSelf->npc__DOT__exu1__DOT__mask = 1U;
                    vlSelf->npc__DOT__exu1__DOT__mem_wdata 
                        = vlSelf->npc__DOT__op2_o;
                    vlSelf->npc__DOT__exu1__DOT__mem_waddr 
                        = (vlSelf->npc__DOT__op1_o 
                           + vlSelf->npc__DOT__op3_o);
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        }
    } else if ((0x10U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        if ((8U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    if ((0U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        vlSelf->npc__DOT__reg_wdata_ex_o 
                            = (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (npc__DOT__exu1__DOT__op1_add_op2 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_add_op2)));
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    } else if ((1U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        if ((1U & (IData)((vlSelf->npc__DOT__op3_o 
                                           >> 5U)))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o = 0ULL;
                            vlSelf->npc__DOT__reg_we_ex_o = 0U;
                        } else {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (npc__DOT__exu1__DOT__op1_movl64i_l_op3 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movl64i_l_op3)));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = (1U & (IData)(vlSelf->npc__DOT__reg_we_id_o));
                        }
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    } else if ((5U == (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        if ((0U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (npc__DOT__exu1__DOT__op1_movr64i_l_op3 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movr64i_l_op3)));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else if ((0x20U == (IData)(vlSelf->npc__DOT__inst_funct7_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (npc__DOT__exu1__DOT__op1_movr64i_a_op3 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__op1_movr64i_a_op3)));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                } else {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
                if ((4U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (vlSelf->npc__DOT__op1_o 
                                   & vlSelf->npc__DOT__op2_o);
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        if ((0U == (0x3fU & ((IData)(vlSelf->npc__DOT__inst_funct7_o) 
                                             >> 1U)))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = (vlSelf->npc__DOT__op1_o 
                                   >> (0x3fU & (IData)(vlSelf->npc__DOT__op3_o)));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else if ((0x10U == (0x3fU 
                                              & ((IData)(vlSelf->npc__DOT__inst_funct7_o) 
                                                 >> 1U)))) {
                            vlSelf->npc__DOT__reg_wdata_ex_o 
                                = VL_SHIFTRS_QQI(64,64,6, vlSelf->npc__DOT__op1_o, 
                                                 (0x3fU 
                                                  & (IData)(vlSelf->npc__DOT__op3_o)));
                            vlSelf->npc__DOT__reg_we_ex_o 
                                = vlSelf->npc__DOT__reg_we_id_o;
                            vlSelf->npc__DOT__jump_flag = 0U;
                            vlSelf->npc__DOT__jump_addr = 0ULL;
                        } else {
                            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                        }
                    } else {
                        vlSelf->npc__DOT__reg_wdata_ex_o 
                            = (vlSelf->npc__DOT__op1_o 
                               ^ vlSelf->npc__DOT__op2_o);
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    }
                } else if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                        vlSelf->npc__DOT__reg_wdata_ex_o 
                            = (QData)((IData)((1U & 
                                               (~ (IData)(npc__DOT__exu1__DOT__op1_ge_op2_unsigned)))));
                        vlSelf->npc__DOT__reg_we_ex_o 
                            = vlSelf->npc__DOT__reg_we_id_o;
                        vlSelf->npc__DOT__jump_flag = 0U;
                        vlSelf->npc__DOT__jump_addr = 0ULL;
                    } else {
                        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                    }
                } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = (vlSelf->npc__DOT__op1_o 
                           << (0x3fU & (IData)(vlSelf->npc__DOT__op3_o)));
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                } else {
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                }
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        }
    } else if ((8U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
    } else if ((4U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
    } else if ((2U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
        if ((1U & (IData)(vlSelf->npc__DOT__inst_type_o))) {
            if ((4U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
                } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    npc__DOT__exu1__DOT__mem_raddr 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                    Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(npc__DOT__exu1__DOT__mem_raddr, vlSelf->__Vtask_pmem_read_l__49__rdata);
                    vlSelf->npc__DOT__reg_waddr_ex_o 
                        = vlSelf->npc__DOT__reg_waddr_id_o;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                    npc__DOT__exu1__DOT__mem_rdata 
                        = vlSelf->__Vtask_pmem_read_l__49__rdata;
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = (QData)((IData)((0xffffU 
                                           & (IData)(npc__DOT__exu1__DOT__mem_rdata))));
                } else {
                    npc__DOT__exu1__DOT__mem_raddr 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                    Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(npc__DOT__exu1__DOT__mem_raddr, vlSelf->__Vtask_pmem_read_l__50__rdata);
                    vlSelf->npc__DOT__reg_waddr_ex_o 
                        = vlSelf->npc__DOT__reg_waddr_id_o;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                    npc__DOT__exu1__DOT__mem_rdata 
                        = vlSelf->__Vtask_pmem_read_l__50__rdata;
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = (QData)((IData)((0xffU & (IData)(npc__DOT__exu1__DOT__mem_rdata))));
                }
            } else if ((2U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                    npc__DOT__exu1__DOT__mem_raddr 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                    Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(npc__DOT__exu1__DOT__mem_raddr, vlSelf->__Vtask_pmem_read_l__51__rdata);
                    vlSelf->npc__DOT__reg_waddr_ex_o 
                        = vlSelf->npc__DOT__reg_waddr_id_o;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                    npc__DOT__exu1__DOT__mem_rdata 
                        = vlSelf->__Vtask_pmem_read_l__51__rdata;
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = npc__DOT__exu1__DOT__mem_rdata;
                } else {
                    npc__DOT__exu1__DOT__mem_raddr 
                        = npc__DOT__exu1__DOT__op1_add_op2;
                    Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(npc__DOT__exu1__DOT__mem_raddr, vlSelf->__Vtask_pmem_read_l__52__rdata);
                    vlSelf->npc__DOT__reg_waddr_ex_o 
                        = vlSelf->npc__DOT__reg_waddr_id_o;
                    vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                    vlSelf->npc__DOT__jump_flag = 0U;
                    vlSelf->npc__DOT__jump_addr = 0ULL;
                    npc__DOT__exu1__DOT__mem_rdata 
                        = vlSelf->__Vtask_pmem_read_l__52__rdata;
                    vlSelf->npc__DOT__reg_wdata_ex_o 
                        = (((QData)((IData)((- (IData)(
                                                       (1U 
                                                        & (IData)(
                                                                  (npc__DOT__exu1__DOT__mem_rdata 
                                                                   >> 0x1fU))))))) 
                            << 0x20U) | (QData)((IData)(npc__DOT__exu1__DOT__mem_rdata)));
                }
            } else if ((1U & (IData)(vlSelf->npc__DOT__inst_funct3_o))) {
                npc__DOT__exu1__DOT__mem_raddr = npc__DOT__exu1__DOT__op1_add_op2;
                Vnpc___024unit____Vdpiimwrap_pmem_read_l_TOP____024unit(npc__DOT__exu1__DOT__mem_raddr, vlSelf->__Vtask_pmem_read_l__53__rdata);
                vlSelf->npc__DOT__reg_waddr_ex_o = vlSelf->npc__DOT__reg_waddr_id_o;
                vlSelf->npc__DOT__reg_we_ex_o = vlSelf->npc__DOT__reg_we_id_o;
                vlSelf->npc__DOT__jump_flag = 0U;
                vlSelf->npc__DOT__jump_addr = 0ULL;
                npc__DOT__exu1__DOT__mem_rdata = vlSelf->__Vtask_pmem_read_l__53__rdata;
                vlSelf->npc__DOT__reg_wdata_ex_o = 
                    (((- (QData)((IData)((1U & (IData)(
                                                       (npc__DOT__exu1__DOT__mem_rdata 
                                                        >> 0xfU)))))) 
                      << 0x10U) | (QData)((IData)((0xffffU 
                                                   & (IData)(npc__DOT__exu1__DOT__mem_rdata)))));
            } else {
                Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
            }
        } else {
            Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
        }
    } else {
        Vnpc___024unit____Vdpiimwrap_no_match_TOP____024unit();
    }
}

void Vnpc___024root___eval(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vnpc___024root___sequent__TOP__1(vlSelf);
    }
    Vnpc___024root___combo__TOP__4(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

QData Vnpc___024root___change_request_1(Vnpc___024root* vlSelf);

VL_INLINE_OPT QData Vnpc___024root___change_request(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___change_request\n"); );
    // Body
    return (Vnpc___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vnpc___024root___change_request_1(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlSelf->npc__DOT__rs1_addr_id_o ^ vlSelf->__Vchglast__TOP__npc__DOT__rs1_addr_id_o)
         | (vlSelf->npc__DOT__rs2_addr_id_o ^ vlSelf->__Vchglast__TOP__npc__DOT__rs2_addr_id_o));
    VL_DEBUG_IF( if(__req && ((vlSelf->npc__DOT__rs1_addr_id_o ^ vlSelf->__Vchglast__TOP__npc__DOT__rs1_addr_id_o))) VL_DBG_MSGF("        CHANGE: vsrc/npc.v:14: npc.rs1_addr_id_o\n"); );
    VL_DEBUG_IF( if(__req && ((vlSelf->npc__DOT__rs2_addr_id_o ^ vlSelf->__Vchglast__TOP__npc__DOT__rs2_addr_id_o))) VL_DBG_MSGF("        CHANGE: vsrc/npc.v:15: npc.rs2_addr_id_o\n"); );
    // Final
    vlSelf->__Vchglast__TOP__npc__DOT__rs1_addr_id_o 
        = vlSelf->npc__DOT__rs1_addr_id_o;
    vlSelf->__Vchglast__TOP__npc__DOT__rs2_addr_id_o 
        = vlSelf->npc__DOT__rs2_addr_id_o;
    return __req;
}

#ifdef VL_DEBUG
void Vnpc___024root___eval_debug_assertions(Vnpc___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vnpc___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
