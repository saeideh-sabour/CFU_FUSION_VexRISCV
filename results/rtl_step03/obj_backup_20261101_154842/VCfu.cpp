// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VCfu__pch.h"

//============================================================
// Constructors

VCfu::VCfu(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VCfu__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , cmd_valid{vlSymsp->TOP.cmd_valid}
    , cmd_ready{vlSymsp->TOP.cmd_ready}
    , rsp_valid{vlSymsp->TOP.rsp_valid}
    , rsp_ready{vlSymsp->TOP.rsp_ready}
    , reset{vlSymsp->TOP.reset}
    , cmd_payload_function_id{vlSymsp->TOP.cmd_payload_function_id}
    , cmd_payload_inputs_0{vlSymsp->TOP.cmd_payload_inputs_0}
    , cmd_payload_inputs_1{vlSymsp->TOP.cmd_payload_inputs_1}
    , rsp_payload_outputs_0{vlSymsp->TOP.rsp_payload_outputs_0}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VCfu::VCfu(const char* _vcname__)
    : VCfu(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VCfu::~VCfu() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VCfu___024root___eval_debug_assertions(VCfu___024root* vlSelf);
#endif  // VL_DEBUG
void VCfu___024root___eval_static(VCfu___024root* vlSelf);
void VCfu___024root___eval_initial(VCfu___024root* vlSelf);
void VCfu___024root___eval_settle(VCfu___024root* vlSelf);
void VCfu___024root___eval(VCfu___024root* vlSelf);

void VCfu::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VCfu::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VCfu___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VCfu___024root___eval_static(&(vlSymsp->TOP));
        VCfu___024root___eval_initial(&(vlSymsp->TOP));
        VCfu___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VCfu___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VCfu::eventsPending() { return false; }

uint64_t VCfu::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VCfu::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VCfu___024root___eval_final(VCfu___024root* vlSelf);

VL_ATTR_COLD void VCfu::final() {
    VCfu___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VCfu::hierName() const { return vlSymsp->name(); }
const char* VCfu::modelName() const { return "VCfu"; }
unsigned VCfu::threads() const { return 1; }
void VCfu::prepareClone() const { contextp()->prepareClone(); }
void VCfu::atClone() const {
    contextp()->threadPoolpOnClone();
}
