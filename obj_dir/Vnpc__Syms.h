// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VNPC__SYMS_H_
#define VERILATED_VNPC__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODEL CLASS

#include "Vnpc.h"

// INCLUDE MODULE CLASSES
#include "Vnpc___024root.h"
#include "Vnpc___024unit.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class Vnpc__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vnpc* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vnpc___024root                 TOP;
    Vnpc___024unit                 TOP____024unit;

    // CONSTRUCTORS
    Vnpc__Syms(VerilatedContext* contextp, const char* namep, Vnpc* modelp);
    ~Vnpc__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
