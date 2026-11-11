// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCfu.h for the primary calling header

#include "VCfu__pch.h"

void VCfu___024root___ctor_var_reset(VCfu___024root* vlSelf);

VCfu___024root::VCfu___024root(VCfu__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    VCfu___024root___ctor_var_reset(this);
}

void VCfu___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VCfu___024root::~VCfu___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
