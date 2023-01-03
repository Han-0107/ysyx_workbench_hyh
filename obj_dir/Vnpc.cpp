// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vnpc.h"
#include "Vnpc__Syms.h"
#include "verilated_dpi.h"

//============================================================
// Constructors

Vnpc::Vnpc(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vnpc__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , inst{vlSymsp->TOP.inst}
    , pc{vlSymsp->TOP.pc}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
}

Vnpc::Vnpc(const char* _vcname__)
    : Vnpc(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vnpc::~Vnpc() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vnpc___024root___eval_initial(Vnpc___024root* vlSelf);
void Vnpc___024root___eval_settle(Vnpc___024root* vlSelf);
void Vnpc___024root___eval(Vnpc___024root* vlSelf);
QData Vnpc___024root___change_request(Vnpc___024root* vlSelf);
#ifdef VL_DEBUG
void Vnpc___024root___eval_debug_assertions(Vnpc___024root* vlSelf);
#endif  // VL_DEBUG
void Vnpc___024root___final(Vnpc___024root* vlSelf);

static void _eval_initial_loop(Vnpc__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vnpc___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vnpc___024root___eval_settle(&(vlSymsp->TOP));
        Vnpc___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vnpc___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("vsrc/npc.v", 2, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vnpc___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vnpc::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vnpc::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vnpc___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vnpc___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vnpc___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("vsrc/npc.v", 2, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vnpc___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vnpc::final() {
    Vnpc___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vnpc::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vnpc::name() const {
    return vlSymsp->name();
}
