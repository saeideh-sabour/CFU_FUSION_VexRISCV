// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCfu.h for the primary calling header

#include "VCfu__pch.h"
#include "VCfu__Syms.h"
#include "VCfu___024root.h"

void VCfu___024root___ctor_var_reset(VCfu___024root* vlSelf);

VCfu___024root::VCfu___024root(VCfu__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VCfu___024root___ctor_var_reset(this);
}

void VCfu___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VCfu___024root::~VCfu___024root() {
}
