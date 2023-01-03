// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vnpc.h for the primary calling header

#include "Vnpc___024unit.h"
#include "Vnpc__Syms.h"

#include "verilated_dpi.h"

//==========


void Vnpc___024unit___ctor_var_reset(Vnpc___024unit* vlSelf);

Vnpc___024unit::Vnpc___024unit(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vnpc___024unit___ctor_var_reset(this);
}

void Vnpc___024unit::__Vconfigure(Vnpc__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vnpc___024unit::~Vnpc___024unit() {
}

void Vnpc___024unit___ctor_var_reset(Vnpc___024unit* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vnpc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vnpc___024unit___ctor_var_reset\n"); );
}
