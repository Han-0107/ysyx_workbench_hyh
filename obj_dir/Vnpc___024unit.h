// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vnpc.h for the primary calling header

#ifndef VERILATED_VNPC___024UNIT_H_
#define VERILATED_VNPC___024UNIT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vnpc__Syms;

//----------

VL_MODULE(Vnpc___024unit) {
  public:

    // INTERNAL VARIABLES
    Vnpc__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vnpc___024unit);  ///< Copying not allowed
  public:
    Vnpc___024unit(const char* name);
    ~Vnpc___024unit();

    // INTERNAL METHODS
    void __Vconfigure(Vnpc__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
