// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCFU__SYMS_H_
#define VERILATED_VCFU__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VCfu.h"

// INCLUDE MODULE CLASSES
#include "VCfu___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VCfu__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VCfu* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VCfu___024root                 TOP;

    // CONSTRUCTORS
    VCfu__Syms(VerilatedContext* contextp, const char* namep, VCfu* modelp);
    ~VCfu__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
