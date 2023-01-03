// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at vsrc/IDU.v:15:30
    extern void ebreak();
    // DPI import at vsrc/EXU.v:15:30
    extern void no_match();
    // DPI import at vsrc/MEM.v:1:30
    extern void pmem_read(long long raddr, long long* rdata);
    // DPI import at vsrc/EXU.v:16:30
    extern void pmem_read_l(long long raddr, long long* rdata);
    // DPI import at vsrc/MEM.v:2:30
    extern void pmem_write(long long waddr, long long wdata, char mask);
    // DPI import at vsrc/EXU.v:17:30
    extern void pmem_write_s(long long waddr, long long wdata, char mask);
    // DPI import at vsrc/REG.v:1:30
    extern void set_gpr_ptr(const svOpenArrayHandle a);

#ifdef __cplusplus
}
#endif
