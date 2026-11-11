// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCfu.h for the primary calling header

#include "VCfu__pch.h"

bool VCfu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VCfu___024root___eval_phase__ico(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_phase__ico\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        (((((IData)(vlSelfRef.clk) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)) 
                                                           << 6U) 
                                                          | ((((IData)(vlSelfRef.reset) 
                                                               != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__reset__0)) 
                                                              << 5U) 
                                                             | (((IData)(vlSelfRef.rsp_ready) 
                                                                 != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rsp_ready__0)) 
                                                                << 4U))) 
                                                         | ((((vlSelfRef.cmd_payload_inputs_1 
                                                               != vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_1__0) 
                                                              << 3U) 
                                                             | ((vlSelfRef.cmd_payload_inputs_0 
                                                                 != vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_0__0) 
                                                                << 2U)) 
                                                            | ((((IData)(vlSelfRef.cmd_payload_function_id) 
                                                                 != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_function_id__0)) 
                                                                << 1U) 
                                                               | ((IData)(vlSelfRef.cmd_valid) 
                                                                  != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__cmd_valid__0)))))));
        vlSelfRef.__Vtrigprevexpr___TOP__cmd_valid__0 
            = vlSelfRef.cmd_valid;
        vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_function_id__0 
            = vlSelfRef.cmd_payload_function_id;
        vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_0__0 
            = vlSelfRef.cmd_payload_inputs_0;
        vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_1__0 
            = vlSelfRef.cmd_payload_inputs_1;
        vlSelfRef.__Vtrigprevexpr___TOP__rsp_ready__0 
            = vlSelfRef.rsp_ready;
        vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (4ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (8ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000010ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000020ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000040ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCfu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = VCfu___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_ico
            if ((4ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_sequent__TOP__0
                    vlSelfRef.Cfu__DOT__pool_data = 
                        (0x000000ffU & ((IData)(vlSelfRef.Cfu__DOT__fused_valid)
                                         ? (IData)(vlSelfRef.Cfu__DOT__quant_value)
                                         : vlSelfRef.cmd_payload_inputs_0));
                    vlSelfRef.Cfu__DOT__pool__DOT__pair_max 
                        = (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__left) 
                            > (IData)(vlSelfRef.Cfu__DOT__pool_data))
                            ? (IData)(vlSelfRef.Cfu__DOT__pool__DOT__left)
                            : (IData)(vlSelfRef.Cfu__DOT__pool_data));
                }
            }
            if ((0x0000000000000020ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_sequent__TOP__1
                    vlSelfRef.cmd_ready = ((~ ((IData)(vlSelfRef.rsp_valid) 
                                               | (IData)(vlSelfRef.reset))) 
                                           & (0U == (IData)(vlSelfRef.Cfu__DOT__state)));
                }
            }
            if ((0x0000000000000021ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_comb__TOP__0
                    vlSelfRef.Cfu__DOT__accept = ((IData)(vlSelfRef.cmd_valid) 
                                                  & (IData)(vlSelfRef.cmd_ready));
                }
            }
            if ((0x0000000000000023ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_comb__TOP__1
                    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1 
                        = ((1U == (7U & (IData)(vlSelfRef.cmd_payload_function_id))) 
                           & (IData)(vlSelfRef.Cfu__DOT__accept));
                    vlSelfRef.Cfu__DOT__arm = (((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                                                & (0U 
                                                   == 
                                                   (0x03f8U 
                                                    & (IData)(vlSelfRef.cmd_payload_function_id)))) 
                                               & (IData)(vlSelfRef.Cfu__DOT__valid_pool));
                }
            }
            if ((0x0000000000000027ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_comb__TOP__2
                    vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid 
                        = ((IData)(vlSelfRef.Cfu__DOT__fused_valid) 
                           | ((((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                                & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)) 
                               & (8U == (0x03f8U & (IData)(vlSelfRef.cmd_payload_function_id)))) 
                              & (0x000000ffU >= vlSelfRef.cmd_payload_inputs_0)));
                }
            }
        }
    }
    return (__VicoExecute);
}

bool VCfu___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void VCfu___024root___nba_sequent__TOP__0(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___nba_sequent__TOP__0\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ __VdfgRegularize_h6e95ff9d_0_3;
    __VdfgRegularize_h6e95ff9d_0_3 = 0;
    QData/*63:0*/ __VdfgRegularize_h6e95ff9d_0_5;
    __VdfgRegularize_h6e95ff9d_0_5 = 0;
    CData/*2:0*/ __Vdly__Cfu__DOT__state;
    __Vdly__Cfu__DOT__state = 0;
    CData/*0:0*/ __Vdly__rsp_valid;
    __Vdly__rsp_valid = 0;
    SData/*15:0*/ __Vdly__Cfu__DOT__out_index;
    __Vdly__Cfu__DOT__out_index = 0;
    SData/*15:0*/ __Vdly__Cfu__DOT__captured;
    __Vdly__Cfu__DOT__captured = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__ox;
    __Vdly__Cfu__DOT__ox = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__oy;
    __Vdly__Cfu__DOT__oy = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__oc;
    __Vdly__Cfu__DOT__oc = 0;
    SData/*15:0*/ __Vdly__Cfu__DOT__kernel_index;
    __Vdly__Cfu__DOT__kernel_index = 0;
    IData/*31:0*/ __Vdly__Cfu__DOT__acc;
    __Vdly__Cfu__DOT__acc = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__quant_value;
    __Vdly__Cfu__DOT__quant_value = 0;
    CData/*0:0*/ __Vdly__Cfu__DOT__pool_armed;
    __Vdly__Cfu__DOT__pool_armed = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool_w;
    __Vdly__Cfu__DOT__pool_w = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool_h;
    __Vdly__Cfu__DOT__pool_h = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool_c;
    __Vdly__Cfu__DOT__pool_c = 0;
    CData/*0:0*/ __Vdly__Cfu__DOT__pool__DOT__active;
    __Vdly__Cfu__DOT__pool__DOT__active = 0;
    SData/*15:0*/ __Vdly__Cfu__DOT__pool_count;
    __Vdly__Cfu__DOT__pool_count = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool__DOT__col;
    __Vdly__Cfu__DOT__pool__DOT__col = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool__DOT__row;
    __Vdly__Cfu__DOT__pool__DOT__row = 0;
    CData/*7:0*/ __Vdly__Cfu__DOT__pool__DOT__chan;
    __Vdly__Cfu__DOT__pool__DOT__chan = 0;
    IData/*31:0*/ __Vdly__Cfu__DOT__pool_received;
    __Vdly__Cfu__DOT__pool_received = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v0;
    __VdlySet__Cfu__DOT__lx__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__lw__v4;
    __VdlyVal__Cfu__DOT__lw__v4 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lw__v4;
    __VdlySet__Cfu__DOT__lw__v4 = 0;
    SData/*8:0*/ __VdlyVal__Cfu__DOT__lx__v4;
    __VdlyVal__Cfu__DOT__lx__v4 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v4;
    __VdlySet__Cfu__DOT__lx__v4 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v5;
    __VdlySet__Cfu__DOT__lx__v5 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v6;
    __VdlySet__Cfu__DOT__lx__v6 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__lw__v6;
    __VdlyVal__Cfu__DOT__lw__v6 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lw__v6;
    __VdlySet__Cfu__DOT__lw__v6 = 0;
    SData/*8:0*/ __VdlyVal__Cfu__DOT__lx__v7;
    __VdlyVal__Cfu__DOT__lx__v7 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v7;
    __VdlySet__Cfu__DOT__lx__v7 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v8;
    __VdlySet__Cfu__DOT__lx__v8 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v9;
    __VdlySet__Cfu__DOT__lx__v9 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__lw__v8;
    __VdlyVal__Cfu__DOT__lw__v8 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lw__v8;
    __VdlySet__Cfu__DOT__lw__v8 = 0;
    SData/*8:0*/ __VdlyVal__Cfu__DOT__lx__v10;
    __VdlyVal__Cfu__DOT__lx__v10 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v10;
    __VdlySet__Cfu__DOT__lx__v10 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v11;
    __VdlySet__Cfu__DOT__lx__v11 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v12;
    __VdlySet__Cfu__DOT__lx__v12 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__lw__v10;
    __VdlyVal__Cfu__DOT__lw__v10 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lw__v10;
    __VdlySet__Cfu__DOT__lw__v10 = 0;
    SData/*8:0*/ __VdlyVal__Cfu__DOT__lx__v13;
    __VdlyVal__Cfu__DOT__lx__v13 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v13;
    __VdlySet__Cfu__DOT__lx__v13 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v14;
    __VdlySet__Cfu__DOT__lx__v14 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__lx__v15;
    __VdlySet__Cfu__DOT__lx__v15 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__conv_results__v0;
    __VdlyVal__Cfu__DOT__conv_results__v0 = 0;
    SData/*12:0*/ __VdlyDim0__Cfu__DOT__conv_results__v0;
    __VdlyDim0__Cfu__DOT__conv_results__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__conv_results__v0;
    __VdlySet__Cfu__DOT__conv_results__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__inputs__v0;
    __VdlyVal__Cfu__DOT__inputs__v0 = 0;
    SData/*10:0*/ __VdlyDim0__Cfu__DOT__inputs__v0;
    __VdlyDim0__Cfu__DOT__inputs__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__inputs__v0;
    __VdlySet__Cfu__DOT__inputs__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__inputs__v1;
    __VdlyVal__Cfu__DOT__inputs__v1 = 0;
    SData/*10:0*/ __VdlyDim0__Cfu__DOT__inputs__v1;
    __VdlyDim0__Cfu__DOT__inputs__v1 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__inputs__v2;
    __VdlyVal__Cfu__DOT__inputs__v2 = 0;
    SData/*10:0*/ __VdlyDim0__Cfu__DOT__inputs__v2;
    __VdlyDim0__Cfu__DOT__inputs__v2 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__inputs__v3;
    __VdlyVal__Cfu__DOT__inputs__v3 = 0;
    SData/*10:0*/ __VdlyDim0__Cfu__DOT__inputs__v3;
    __VdlyDim0__Cfu__DOT__inputs__v3 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__weights__v0;
    __VdlyVal__Cfu__DOT__weights__v0 = 0;
    SData/*11:0*/ __VdlyDim0__Cfu__DOT__weights__v0;
    __VdlyDim0__Cfu__DOT__weights__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__weights__v0;
    __VdlySet__Cfu__DOT__weights__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__weights__v1;
    __VdlyVal__Cfu__DOT__weights__v1 = 0;
    SData/*11:0*/ __VdlyDim0__Cfu__DOT__weights__v1;
    __VdlyDim0__Cfu__DOT__weights__v1 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__weights__v2;
    __VdlyVal__Cfu__DOT__weights__v2 = 0;
    SData/*11:0*/ __VdlyDim0__Cfu__DOT__weights__v2;
    __VdlyDim0__Cfu__DOT__weights__v2 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__weights__v3;
    __VdlyVal__Cfu__DOT__weights__v3 = 0;
    SData/*11:0*/ __VdlyDim0__Cfu__DOT__weights__v3;
    __VdlyDim0__Cfu__DOT__weights__v3 = 0;
    IData/*31:0*/ __VdlyVal__Cfu__DOT__multipliers__v0;
    __VdlyVal__Cfu__DOT__multipliers__v0 = 0;
    CData/*4:0*/ __VdlyDim0__Cfu__DOT__multipliers__v0;
    __VdlyDim0__Cfu__DOT__multipliers__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__multipliers__v0;
    __VdlySet__Cfu__DOT__multipliers__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__pool__DOT__results__v0;
    __VdlyVal__Cfu__DOT__pool__DOT__results__v0 = 0;
    SData/*11:0*/ __VdlyDim0__Cfu__DOT__pool__DOT__results__v0;
    __VdlyDim0__Cfu__DOT__pool__DOT__results__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__pool__DOT__results__v0;
    __VdlySet__Cfu__DOT__pool__DOT__results__v0 = 0;
    CData/*7:0*/ __VdlyVal__Cfu__DOT__pool__DOT__upper__v0;
    __VdlyVal__Cfu__DOT__pool__DOT__upper__v0 = 0;
    CData/*3:0*/ __VdlyDim0__Cfu__DOT__pool__DOT__upper__v0;
    __VdlyDim0__Cfu__DOT__pool__DOT__upper__v0 = 0;
    CData/*0:0*/ __VdlySet__Cfu__DOT__pool__DOT__upper__v0;
    __VdlySet__Cfu__DOT__pool__DOT__upper__v0 = 0;
    // Body
    __Vdly__Cfu__DOT__pool_received = vlSelfRef.Cfu__DOT__pool_received;
    __VdlySet__Cfu__DOT__multipliers__v0 = 0U;
    __VdlySet__Cfu__DOT__inputs__v0 = 0U;
    __VdlySet__Cfu__DOT__weights__v0 = 0U;
    __Vdly__Cfu__DOT__pool_count = vlSelfRef.Cfu__DOT__pool_count;
    __Vdly__Cfu__DOT__pool__DOT__col = vlSelfRef.Cfu__DOT__pool__DOT__col;
    __Vdly__Cfu__DOT__pool__DOT__row = vlSelfRef.Cfu__DOT__pool__DOT__row;
    __Vdly__Cfu__DOT__pool__DOT__chan = vlSelfRef.Cfu__DOT__pool__DOT__chan;
    __VdlySet__Cfu__DOT__pool__DOT__results__v0 = 0U;
    __VdlySet__Cfu__DOT__pool__DOT__upper__v0 = 0U;
    __Vdly__Cfu__DOT__pool__DOT__active = vlSelfRef.Cfu__DOT__pool__DOT__active;
    __Vdly__Cfu__DOT__out_index = vlSelfRef.Cfu__DOT__out_index;
    __Vdly__Cfu__DOT__captured = vlSelfRef.Cfu__DOT__captured;
    __Vdly__Cfu__DOT__ox = vlSelfRef.Cfu__DOT__ox;
    __Vdly__Cfu__DOT__oy = vlSelfRef.Cfu__DOT__oy;
    __Vdly__Cfu__DOT__oc = vlSelfRef.Cfu__DOT__oc;
    __Vdly__Cfu__DOT__kernel_index = vlSelfRef.Cfu__DOT__kernel_index;
    __Vdly__Cfu__DOT__acc = vlSelfRef.Cfu__DOT__acc;
    __Vdly__Cfu__DOT__pool_armed = vlSelfRef.Cfu__DOT__pool_armed;
    __Vdly__Cfu__DOT__pool_w = vlSelfRef.Cfu__DOT__pool_w;
    __Vdly__Cfu__DOT__pool_h = vlSelfRef.Cfu__DOT__pool_h;
    __Vdly__Cfu__DOT__pool_c = vlSelfRef.Cfu__DOT__pool_c;
    __VdlySet__Cfu__DOT__conv_results__v0 = 0U;
    __Vdly__Cfu__DOT__quant_value = vlSelfRef.Cfu__DOT__quant_value;
    __Vdly__rsp_valid = vlSelfRef.rsp_valid;
    __VdlySet__Cfu__DOT__lw__v4 = 0U;
    __VdlySet__Cfu__DOT__lw__v6 = 0U;
    __VdlySet__Cfu__DOT__lw__v8 = 0U;
    __VdlySet__Cfu__DOT__lw__v10 = 0U;
    __VdlySet__Cfu__DOT__lx__v4 = 0U;
    __VdlySet__Cfu__DOT__lx__v5 = 0U;
    __VdlySet__Cfu__DOT__lx__v7 = 0U;
    __VdlySet__Cfu__DOT__lx__v8 = 0U;
    __VdlySet__Cfu__DOT__lx__v10 = 0U;
    __VdlySet__Cfu__DOT__lx__v11 = 0U;
    __VdlySet__Cfu__DOT__lx__v13 = 0U;
    __VdlySet__Cfu__DOT__lx__v14 = 0U;
    __Vdly__Cfu__DOT__state = vlSelfRef.Cfu__DOT__state;
    __VdlySet__Cfu__DOT__lx__v0 = 0U;
    __VdlySet__Cfu__DOT__lx__v6 = 0U;
    __VdlySet__Cfu__DOT__lx__v9 = 0U;
    __VdlySet__Cfu__DOT__lx__v12 = 0U;
    __VdlySet__Cfu__DOT__lx__v15 = 0U;
    if (vlSelfRef.reset) {
        __Vdly__Cfu__DOT__pool_received = 0U;
        __Vdly__Cfu__DOT__state = 0U;
        __Vdly__rsp_valid = 0U;
        vlSelfRef.rsp_payload_outputs_0 = 0U;
        __Vdly__Cfu__DOT__out_index = 0U;
        __Vdly__Cfu__DOT__captured = 0U;
        __Vdly__Cfu__DOT__ox = 0U;
        __Vdly__Cfu__DOT__oy = 0U;
        __Vdly__Cfu__DOT__oc = 0U;
        __Vdly__Cfu__DOT__kernel_index = 0U;
        __Vdly__Cfu__DOT__acc = 0U;
        vlSelfRef.Cfu__DOT__product = 0ULL;
        __Vdly__Cfu__DOT__quant_value = 0U;
        __Vdly__Cfu__DOT__pool_armed = 0U;
        __Vdly__Cfu__DOT__pool_w = 0U;
        __Vdly__Cfu__DOT__pool_h = 0U;
        __Vdly__Cfu__DOT__pool_c = 0U;
        __VdlySet__Cfu__DOT__lx__v0 = 1U;
        vlSelfRef.Cfu__DOT__cin = 0U;
        vlSelfRef.Cfu__DOT__input_zp = 0U;
        vlSelfRef.Cfu__DOT__output_zp = 0U;
        vlSelfRef.Cfu__DOT__route = 1U;
        __Vdly__Cfu__DOT__pool__DOT__active = 0U;
        vlSelfRef.Cfu__DOT__pool_done = 0U;
        __Vdly__Cfu__DOT__pool_count = 0U;
        __Vdly__Cfu__DOT__pool__DOT__col = 0U;
        __Vdly__Cfu__DOT__pool__DOT__row = 0U;
        __Vdly__Cfu__DOT__pool__DOT__chan = 0U;
        vlSelfRef.Cfu__DOT__pool__DOT__left = 0U;
        vlSelfRef.Cfu__DOT__pool__DOT__c = 0U;
        vlSelfRef.Cfu__DOT__pool__DOT__w = 0U;
        vlSelfRef.Cfu__DOT__pool__DOT__h = 0U;
        vlSelfRef.Cfu__DOT__cout = 0U;
        vlSelfRef.Cfu__DOT__width = 0U;
        vlSelfRef.Cfu__DOT__height = 0U;
    } else {
        if (((IData)(vlSelfRef.rsp_valid) & (IData)(vlSelfRef.rsp_ready))) {
            __Vdly__rsp_valid = 0U;
        }
        if (vlSelfRef.Cfu__DOT__arm) {
            __Vdly__Cfu__DOT__pool_received = 0U;
        } else if (((IData)(vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid) 
                    & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active))) {
            __Vdly__Cfu__DOT__pool_received = ((IData)(1U) 
                                               + vlSelfRef.Cfu__DOT__pool_received);
        }
        if (vlSelfRef.Cfu__DOT__accept) {
            __Vdly__rsp_valid = 1U;
            vlSelfRef.rsp_payload_outputs_0 = 0U;
            if ((0U == (7U & (IData)(vlSelfRef.cmd_payload_function_id)))) {
                if (((((((((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U))) 
                           | (1U == (0x0000007fU & 
                                     ((IData)(vlSelfRef.cmd_payload_function_id) 
                                      >> 3U)))) | (2U 
                                                   == 
                                                   (0x0000007fU 
                                                    & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                       >> 3U)))) 
                         | (3U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U)))) 
                        | (4U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                 >> 3U)))) 
                       | (5U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                >> 3U)))) 
                      | (6U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) 
                     | (7U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                              >> 3U))))) {
                    if ((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) {
                        if ((0U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U & (~ ((0U < vlSelfRef.cmd_payload_inputs_1) 
                                          & (0x00000020U 
                                             >= vlSelfRef.cmd_payload_inputs_1))))) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((1U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U & (~ ((0U < vlSelfRef.cmd_payload_inputs_1) 
                                          & (0x00000020U 
                                             >= vlSelfRef.cmd_payload_inputs_1))))) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((2U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U & (~ ((0U < vlSelfRef.cmd_payload_inputs_1) 
                                          & (0x00000020U 
                                             >= vlSelfRef.cmd_payload_inputs_1))))) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((3U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U & (~ ((0U < vlSelfRef.cmd_payload_inputs_1) 
                                          & (0x00000020U 
                                             >= vlSelfRef.cmd_payload_inputs_1))))) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((4U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((0x000000ffU < vlSelfRef.cmd_payload_inputs_1)) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((5U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((0x000000ffU < vlSelfRef.cmd_payload_inputs_1)) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else if ((6U == vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U & (~ ((1U <= vlSelfRef.cmd_payload_inputs_1) 
                                          & (3U >= vlSelfRef.cmd_payload_inputs_1))))) {
                                vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                            }
                        } else {
                            vlSelfRef.rsp_payload_outputs_0 = 0x80000001U;
                        }
                    } else if ((1U == (0x0000007fU 
                                       & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                          >> 3U)))) {
                        if ((1U & (~ ((0x000007fcU 
                                       >= vlSelfRef.cmd_payload_inputs_0) 
                                      & (0U == (3U 
                                                & vlSelfRef.cmd_payload_inputs_0)))))) {
                            vlSelfRef.rsp_payload_outputs_0 = 0x80000002U;
                        }
                    } else if ((2U == (0x0000007fU 
                                       & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                          >> 3U)))) {
                        if ((1U & (~ ((0x00000ffcU 
                                       >= vlSelfRef.cmd_payload_inputs_0) 
                                      & (0U == (3U 
                                                & vlSelfRef.cmd_payload_inputs_0)))))) {
                            vlSelfRef.rsp_payload_outputs_0 = 0x80000002U;
                        }
                    } else if ((3U == (0x0000007fU 
                                       & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                          >> 3U)))) {
                        if ((1U & (~ ((0x00000020U 
                                       > vlSelfRef.cmd_payload_inputs_0) 
                                      & (~ (vlSelfRef.cmd_payload_inputs_1 
                                            >> 0x1fU)))))) {
                            vlSelfRef.rsp_payload_outputs_0 = 0x80000002U;
                        }
                    } else if ((4U == (0x0000007fU 
                                       & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                          >> 3U)))) {
                        if ((1U & ((~ ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2) 
                                       & ((0U < (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                          & ((0x20U 
                                              >= (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                             & ((0U 
                                                 < (IData)(vlSelfRef.Cfu__DOT__cin)) 
                                                & ((0x20U 
                                                    >= (IData)(vlSelfRef.Cfu__DOT__cin)) 
                                                   & ((0x00000800U 
                                                       >= 
                                                       ((IData)(vlSelfRef.Cfu__DOT__cin) 
                                                        * vlSelfRef.Cfu__DOT__plane)) 
                                                      & ((0x00001000U 
                                                          >= 
                                                          ((IData)(9U) 
                                                           * 
                                                           ((IData)(vlSelfRef.Cfu__DOT__cout) 
                                                            * (IData)(vlSelfRef.Cfu__DOT__cin)))) 
                                                         & ((0x00002000U 
                                                             >= vlSelfRef.Cfu__DOT__total) 
                                                            & (0U 
                                                               != (IData)(vlSelfRef.Cfu__DOT__route))))))))))) 
                                   | (((IData)(vlSelfRef.Cfu__DOT__route) 
                                       >> 1U) & (((
                                                   ((((~ (IData)(vlSelfRef.Cfu__DOT__valid_pool)) 
                                                      | (~ (IData)(vlSelfRef.Cfu__DOT__pool_armed))) 
                                                     | (~ (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active))) 
                                                    | (0U 
                                                       != vlSelfRef.Cfu__DOT__pool_received)) 
                                                   | ((IData)(vlSelfRef.Cfu__DOT__pool_w) 
                                                      != (IData)(vlSelfRef.Cfu__DOT__width))) 
                                                  | ((IData)(vlSelfRef.Cfu__DOT__pool_h) 
                                                     != (IData)(vlSelfRef.Cfu__DOT__height))) 
                                                 | ((IData)(vlSelfRef.Cfu__DOT__pool_c) 
                                                    != (IData)(vlSelfRef.Cfu__DOT__cout))))))) {
                            vlSelfRef.rsp_payload_outputs_0 = 0x80000003U;
                        } else {
                            __Vdly__Cfu__DOT__state = 1U;
                            __Vdly__rsp_valid = 0U;
                            __Vdly__Cfu__DOT__ox = 0U;
                            __Vdly__Cfu__DOT__oy = 0U;
                            __Vdly__Cfu__DOT__oc = 0U;
                            __Vdly__Cfu__DOT__kernel_index = 0U;
                            __Vdly__Cfu__DOT__acc = 0U;
                            __Vdly__Cfu__DOT__out_index = 0U;
                            __Vdly__Cfu__DOT__captured = 0U;
                            if ((2U & (IData)(vlSelfRef.Cfu__DOT__route))) {
                                __Vdly__Cfu__DOT__pool_armed = 0U;
                            }
                        }
                    } else {
                        vlSelfRef.rsp_payload_outputs_0 
                            = ((5U == (0x0000007fU 
                                       & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                          >> 3U))) ? 
                               ((vlSelfRef.cmd_payload_inputs_0 
                                 < (IData)(vlSelfRef.Cfu__DOT__captured))
                                 ? vlSelfRef.Cfu__DOT__conv_results
                                [(0x00001fffU & vlSelfRef.cmd_payload_inputs_0)]
                                 : 0x80000004U) : (
                                                   (6U 
                                                    == 
                                                    (0x0000007fU 
                                                     & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                        >> 3U)))
                                                    ? (IData)(vlSelfRef.Cfu__DOT__captured)
                                                    : 0x43465531U));
                    }
                } else {
                    vlSelfRef.rsp_payload_outputs_0 = 0x80000005U;
                }
            } else if ((1U == (7U & (IData)(vlSelfRef.cmd_payload_function_id)))) {
                if ((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                           >> 3U)))) {
                    if (vlSelfRef.Cfu__DOT__valid_pool) {
                        __Vdly__Cfu__DOT__pool_armed = 1U;
                        __Vdly__Cfu__DOT__pool_w = vlSelfRef.Cfu__DOT__width;
                        __Vdly__Cfu__DOT__pool_h = vlSelfRef.Cfu__DOT__height;
                        __Vdly__Cfu__DOT__pool_c = vlSelfRef.Cfu__DOT__cout;
                    } else {
                        vlSelfRef.rsp_payload_outputs_0 = 0x80000003U;
                    }
                } else if ((1U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U)))) {
                    if ((1U & ((~ (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)) 
                               | (0x000000ffU < vlSelfRef.cmd_payload_inputs_0)))) {
                        vlSelfRef.rsp_payload_outputs_0 = 0x80000006U;
                    } else {
                        __Vdly__Cfu__DOT__pool_armed = 0U;
                    }
                } else {
                    vlSelfRef.rsp_payload_outputs_0 
                        = ((2U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U)))
                            ? ((vlSelfRef.cmd_payload_inputs_0 
                                < (IData)(vlSelfRef.Cfu__DOT__pool_count))
                                ? vlSelfRef.Cfu__DOT__pool__DOT__results
                               [(0x00000fffU & vlSelfRef.cmd_payload_inputs_0)]
                                : 0x80000004U) : ((3U 
                                                   == 
                                                   (0x0000007fU 
                                                    & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                       >> 3U)))
                                                   ? 
                                                  (((IData)(vlSelfRef.Cfu__DOT__pool_done) 
                                                    << 0x00000010U) 
                                                   | (IData)(vlSelfRef.Cfu__DOT__pool_count))
                                                   : 0x80000005U));
                }
            } else {
                vlSelfRef.rsp_payload_outputs_0 = 0x80000005U;
            }
        }
        if (vlSelfRef.Cfu__DOT__arm) {
            __Vdly__Cfu__DOT__pool__DOT__col = 0U;
            __Vdly__Cfu__DOT__pool__DOT__row = 0U;
            __Vdly__Cfu__DOT__pool__DOT__chan = 0U;
            __Vdly__Cfu__DOT__pool__DOT__active = 1U;
            vlSelfRef.Cfu__DOT__pool_done = 0U;
            __Vdly__Cfu__DOT__pool_count = 0U;
            vlSelfRef.Cfu__DOT__pool__DOT__left = 0U;
            vlSelfRef.Cfu__DOT__pool__DOT__c = vlSelfRef.Cfu__DOT__cout;
            vlSelfRef.Cfu__DOT__pool__DOT__w = vlSelfRef.Cfu__DOT__width;
            vlSelfRef.Cfu__DOT__pool__DOT__h = vlSelfRef.Cfu__DOT__height;
        } else if (((IData)(vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid) 
                    & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active))) {
            if ((1U & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__col))) {
                if ((1U & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__row))) {
                    __VdlyVal__Cfu__DOT__pool__DOT__results__v0 
                        = ((vlSelfRef.Cfu__DOT__pool__DOT__upper
                            [(0x0000000fU & ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__col) 
                                             >> 1U))] 
                            > (IData)(vlSelfRef.Cfu__DOT__pool__DOT__pair_max))
                            ? vlSelfRef.Cfu__DOT__pool__DOT__upper
                           [(0x0000000fU & ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__col) 
                                            >> 1U))]
                            : (IData)(vlSelfRef.Cfu__DOT__pool__DOT__pair_max));
                    __VdlyDim0__Cfu__DOT__pool__DOT__results__v0 
                        = (0x00000fffU & (IData)(vlSelfRef.Cfu__DOT__pool_count));
                    __VdlySet__Cfu__DOT__pool__DOT__results__v0 = 1U;
                    __Vdly__Cfu__DOT__pool_count = 
                        (0x0000ffffU & ((IData)(1U) 
                                        + (IData)(vlSelfRef.Cfu__DOT__pool_count)));
                } else {
                    __VdlyVal__Cfu__DOT__pool__DOT__upper__v0 
                        = vlSelfRef.Cfu__DOT__pool__DOT__pair_max;
                    __VdlyDim0__Cfu__DOT__pool__DOT__upper__v0 
                        = (0x0000000fU & ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__col) 
                                          >> 1U));
                    __VdlySet__Cfu__DOT__pool__DOT__upper__v0 = 1U;
                }
            } else {
                vlSelfRef.Cfu__DOT__pool__DOT__left 
                    = vlSelfRef.Cfu__DOT__pool_data;
            }
            if (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__col) 
                 == ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__w) 
                     - (IData)(1U)))) {
                __Vdly__Cfu__DOT__pool__DOT__col = 0U;
                if (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__row) 
                     == ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__h) 
                         - (IData)(1U)))) {
                    __Vdly__Cfu__DOT__pool__DOT__row = 0U;
                    if (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__chan) 
                         == ((IData)(vlSelfRef.Cfu__DOT__pool__DOT__c) 
                             - (IData)(1U)))) {
                        __Vdly__Cfu__DOT__pool__DOT__active = 0U;
                        vlSelfRef.Cfu__DOT__pool_done = 1U;
                    } else {
                        __Vdly__Cfu__DOT__pool__DOT__chan 
                            = (0x000000ffU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.Cfu__DOT__pool__DOT__chan)));
                    }
                } else {
                    __Vdly__Cfu__DOT__pool__DOT__row 
                        = (0x000000ffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.Cfu__DOT__pool__DOT__row)));
                }
            } else {
                __Vdly__Cfu__DOT__pool__DOT__col = 
                    (0x000000ffU & ((IData)(1U) + (IData)(vlSelfRef.Cfu__DOT__pool__DOT__col)));
            }
        }
        if ((1U == (IData)(vlSelfRef.Cfu__DOT__state))) {
            vlSelfRef.Cfu__DOT__t = vlSelfRef.Cfu__DOT__kernel_index;
            vlSelfRef.Cfu__DOT__ic = VL_DIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U));
            __Vdly__Cfu__DOT__state = 2U;
            vlSelfRef.Cfu__DOT__ky = VL_DIVS_III(32, 
                                                 VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U)), (IData)(3U));
            vlSelfRef.Cfu__DOT__kx = VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(3U));
            vlSelfRef.Cfu__DOT__iy = (((IData)(vlSelfRef.Cfu__DOT__oy) 
                                       + vlSelfRef.Cfu__DOT__ky) 
                                      - (IData)(1U));
            vlSelfRef.Cfu__DOT__ix = (((IData)(vlSelfRef.Cfu__DOT__ox) 
                                       + vlSelfRef.Cfu__DOT__kx) 
                                      - (IData)(1U));
            if ((vlSelfRef.Cfu__DOT__t < ((IData)(9U) 
                                          * (IData)(vlSelfRef.Cfu__DOT__cin)))) {
                __VdlyVal__Cfu__DOT__lw__v4 = vlSelfRef.Cfu__DOT__weights
                    [(0x00000fffU & (((IData)(9U) * 
                                      ((IData)(vlSelfRef.Cfu__DOT__oc) 
                                       * (IData)(vlSelfRef.Cfu__DOT__cin))) 
                                     + vlSelfRef.Cfu__DOT__t))];
                __VdlySet__Cfu__DOT__lw__v4 = 1U;
                if ((((VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__iy) 
                       & (vlSelfRef.Cfu__DOT__iy < (IData)(vlSelfRef.Cfu__DOT__height))) 
                      & VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__ix)) 
                     & (vlSelfRef.Cfu__DOT__ix < (IData)(vlSelfRef.Cfu__DOT__width)))) {
                    vlSelfRef.Cfu__DOT__addr = (((vlSelfRef.Cfu__DOT__ic 
                                                  * vlSelfRef.Cfu__DOT__plane) 
                                                 + 
                                                 (vlSelfRef.Cfu__DOT__iy 
                                                  * (IData)(vlSelfRef.Cfu__DOT__width))) 
                                                + vlSelfRef.Cfu__DOT__ix);
                    __VdlyVal__Cfu__DOT__lx__v4 = (0x000001ffU 
                                                   & (vlSelfRef.Cfu__DOT__inputs
                                                      [
                                                      (0x000007ffU 
                                                       & vlSelfRef.Cfu__DOT__addr)] 
                                                      - (IData)(vlSelfRef.Cfu__DOT__input_zp)));
                    __VdlySet__Cfu__DOT__lx__v4 = 1U;
                } else {
                    __VdlySet__Cfu__DOT__lx__v5 = 1U;
                }
            } else {
                __VdlySet__Cfu__DOT__lx__v6 = 1U;
            }
            vlSelfRef.Cfu__DOT__t = ((IData)(1U) + (IData)(vlSelfRef.Cfu__DOT__kernel_index));
            vlSelfRef.Cfu__DOT__ic = VL_DIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U));
            vlSelfRef.Cfu__DOT__ky = VL_DIVS_III(32, 
                                                 VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U)), (IData)(3U));
            vlSelfRef.Cfu__DOT__kx = VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(3U));
            vlSelfRef.Cfu__DOT__iy = (((IData)(vlSelfRef.Cfu__DOT__oy) 
                                       + vlSelfRef.Cfu__DOT__ky) 
                                      - (IData)(1U));
            vlSelfRef.Cfu__DOT__ix = (((IData)(vlSelfRef.Cfu__DOT__ox) 
                                       + vlSelfRef.Cfu__DOT__kx) 
                                      - (IData)(1U));
            if ((vlSelfRef.Cfu__DOT__t < ((IData)(9U) 
                                          * (IData)(vlSelfRef.Cfu__DOT__cin)))) {
                __VdlyVal__Cfu__DOT__lw__v6 = vlSelfRef.Cfu__DOT__weights
                    [(0x00000fffU & (((IData)(9U) * 
                                      ((IData)(vlSelfRef.Cfu__DOT__oc) 
                                       * (IData)(vlSelfRef.Cfu__DOT__cin))) 
                                     + vlSelfRef.Cfu__DOT__t))];
                __VdlySet__Cfu__DOT__lw__v6 = 1U;
                if ((((VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__iy) 
                       & (vlSelfRef.Cfu__DOT__iy < (IData)(vlSelfRef.Cfu__DOT__height))) 
                      & VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__ix)) 
                     & (vlSelfRef.Cfu__DOT__ix < (IData)(vlSelfRef.Cfu__DOT__width)))) {
                    vlSelfRef.Cfu__DOT__addr = (((vlSelfRef.Cfu__DOT__ic 
                                                  * vlSelfRef.Cfu__DOT__plane) 
                                                 + 
                                                 (vlSelfRef.Cfu__DOT__iy 
                                                  * (IData)(vlSelfRef.Cfu__DOT__width))) 
                                                + vlSelfRef.Cfu__DOT__ix);
                    __VdlyVal__Cfu__DOT__lx__v7 = (0x000001ffU 
                                                   & (vlSelfRef.Cfu__DOT__inputs
                                                      [
                                                      (0x000007ffU 
                                                       & vlSelfRef.Cfu__DOT__addr)] 
                                                      - (IData)(vlSelfRef.Cfu__DOT__input_zp)));
                    __VdlySet__Cfu__DOT__lx__v7 = 1U;
                } else {
                    __VdlySet__Cfu__DOT__lx__v8 = 1U;
                }
            } else {
                __VdlySet__Cfu__DOT__lx__v9 = 1U;
            }
            vlSelfRef.Cfu__DOT__t = ((IData)(2U) + (IData)(vlSelfRef.Cfu__DOT__kernel_index));
            vlSelfRef.Cfu__DOT__ic = VL_DIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U));
            vlSelfRef.Cfu__DOT__ky = VL_DIVS_III(32, 
                                                 VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U)), (IData)(3U));
            vlSelfRef.Cfu__DOT__kx = VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(3U));
            vlSelfRef.Cfu__DOT__iy = (((IData)(vlSelfRef.Cfu__DOT__oy) 
                                       + vlSelfRef.Cfu__DOT__ky) 
                                      - (IData)(1U));
            vlSelfRef.Cfu__DOT__ix = (((IData)(vlSelfRef.Cfu__DOT__ox) 
                                       + vlSelfRef.Cfu__DOT__kx) 
                                      - (IData)(1U));
            if ((vlSelfRef.Cfu__DOT__t < ((IData)(9U) 
                                          * (IData)(vlSelfRef.Cfu__DOT__cin)))) {
                __VdlyVal__Cfu__DOT__lw__v8 = vlSelfRef.Cfu__DOT__weights
                    [(0x00000fffU & (((IData)(9U) * 
                                      ((IData)(vlSelfRef.Cfu__DOT__oc) 
                                       * (IData)(vlSelfRef.Cfu__DOT__cin))) 
                                     + vlSelfRef.Cfu__DOT__t))];
                __VdlySet__Cfu__DOT__lw__v8 = 1U;
                if ((((VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__iy) 
                       & (vlSelfRef.Cfu__DOT__iy < (IData)(vlSelfRef.Cfu__DOT__height))) 
                      & VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__ix)) 
                     & (vlSelfRef.Cfu__DOT__ix < (IData)(vlSelfRef.Cfu__DOT__width)))) {
                    vlSelfRef.Cfu__DOT__addr = (((vlSelfRef.Cfu__DOT__ic 
                                                  * vlSelfRef.Cfu__DOT__plane) 
                                                 + 
                                                 (vlSelfRef.Cfu__DOT__iy 
                                                  * (IData)(vlSelfRef.Cfu__DOT__width))) 
                                                + vlSelfRef.Cfu__DOT__ix);
                    __VdlyVal__Cfu__DOT__lx__v10 = 
                        (0x000001ffU & (vlSelfRef.Cfu__DOT__inputs
                                        [(0x000007ffU 
                                          & vlSelfRef.Cfu__DOT__addr)] 
                                        - (IData)(vlSelfRef.Cfu__DOT__input_zp)));
                    __VdlySet__Cfu__DOT__lx__v10 = 1U;
                } else {
                    __VdlySet__Cfu__DOT__lx__v11 = 1U;
                }
            } else {
                __VdlySet__Cfu__DOT__lx__v12 = 1U;
            }
            vlSelfRef.Cfu__DOT__t = ((IData)(3U) + (IData)(vlSelfRef.Cfu__DOT__kernel_index));
            vlSelfRef.Cfu__DOT__ic = VL_DIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U));
            vlSelfRef.Cfu__DOT__ky = VL_DIVS_III(32, 
                                                 VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(9U)), (IData)(3U));
            vlSelfRef.Cfu__DOT__kx = VL_MODDIVS_III(32, vlSelfRef.Cfu__DOT__t, (IData)(3U));
            vlSelfRef.Cfu__DOT__iy = (((IData)(vlSelfRef.Cfu__DOT__oy) 
                                       + vlSelfRef.Cfu__DOT__ky) 
                                      - (IData)(1U));
            vlSelfRef.Cfu__DOT__ix = (((IData)(vlSelfRef.Cfu__DOT__ox) 
                                       + vlSelfRef.Cfu__DOT__kx) 
                                      - (IData)(1U));
            if ((vlSelfRef.Cfu__DOT__t < ((IData)(9U) 
                                          * (IData)(vlSelfRef.Cfu__DOT__cin)))) {
                __VdlyVal__Cfu__DOT__lw__v10 = vlSelfRef.Cfu__DOT__weights
                    [(0x00000fffU & (((IData)(9U) * 
                                      ((IData)(vlSelfRef.Cfu__DOT__oc) 
                                       * (IData)(vlSelfRef.Cfu__DOT__cin))) 
                                     + vlSelfRef.Cfu__DOT__t))];
                __VdlySet__Cfu__DOT__lw__v10 = 1U;
                if ((((VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__iy) 
                       & (vlSelfRef.Cfu__DOT__iy < (IData)(vlSelfRef.Cfu__DOT__height))) 
                      & VL_LTES_III(32, 0U, vlSelfRef.Cfu__DOT__ix)) 
                     & (vlSelfRef.Cfu__DOT__ix < (IData)(vlSelfRef.Cfu__DOT__width)))) {
                    vlSelfRef.Cfu__DOT__addr = (((vlSelfRef.Cfu__DOT__ic 
                                                  * vlSelfRef.Cfu__DOT__plane) 
                                                 + 
                                                 (vlSelfRef.Cfu__DOT__iy 
                                                  * (IData)(vlSelfRef.Cfu__DOT__width))) 
                                                + vlSelfRef.Cfu__DOT__ix);
                    __VdlyVal__Cfu__DOT__lx__v13 = 
                        (0x000001ffU & (vlSelfRef.Cfu__DOT__inputs
                                        [(0x000007ffU 
                                          & vlSelfRef.Cfu__DOT__addr)] 
                                        - (IData)(vlSelfRef.Cfu__DOT__input_zp)));
                    __VdlySet__Cfu__DOT__lx__v13 = 1U;
                } else {
                    __VdlySet__Cfu__DOT__lx__v14 = 1U;
                }
            } else {
                __VdlySet__Cfu__DOT__lx__v15 = 1U;
            }
        } else if ((2U == (IData)(vlSelfRef.Cfu__DOT__state))) {
            __Vdly__Cfu__DOT__acc = (vlSelfRef.Cfu__DOT__acc 
                                     + ((((- (IData)(
                                                     (1U 
                                                      & (vlSelfRef.Cfu__DOT__mac4__DOT__p0 
                                                         >> 0x00000010U)))) 
                                          << 0x00000011U) 
                                         | vlSelfRef.Cfu__DOT__mac4__DOT__p0) 
                                        + ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.Cfu__DOT__mac4__DOT__p1 
                                                            >> 0x00000010U)))) 
                                             << 0x00000011U) 
                                            | vlSelfRef.Cfu__DOT__mac4__DOT__p1) 
                                           + ((((- (IData)(
                                                           (1U 
                                                            & (vlSelfRef.Cfu__DOT__mac4__DOT__p2 
                                                               >> 0x00000010U)))) 
                                                << 0x00000011U) 
                                               | vlSelfRef.Cfu__DOT__mac4__DOT__p2) 
                                              + (((- (IData)(
                                                             (1U 
                                                              & (vlSelfRef.Cfu__DOT__mac4__DOT__p3 
                                                                 >> 0x00000010U)))) 
                                                  << 0x00000011U) 
                                                 | vlSelfRef.Cfu__DOT__mac4__DOT__p3)))));
            if ((((IData)(4U) + (IData)(vlSelfRef.Cfu__DOT__kernel_index)) 
                 >= ((IData)(9U) * (IData)(vlSelfRef.Cfu__DOT__cin)))) {
                __Vdly__Cfu__DOT__state = 3U;
            } else {
                __Vdly__Cfu__DOT__kernel_index = (0x0000ffffU 
                                                  & ((IData)(4U) 
                                                     + (IData)(vlSelfRef.Cfu__DOT__kernel_index)));
                __Vdly__Cfu__DOT__state = 1U;
            }
        } else if ((3U == (IData)(vlSelfRef.Cfu__DOT__state))) {
            vlSelfRef.Cfu__DOT__product = VL_MULS_QQQ(64, 
                                                      VL_EXTENDS_QI(64,32, vlSelfRef.Cfu__DOT__acc), 
                                                      VL_EXTENDS_QI(64,32, vlSelfRef.Cfu__DOT__multipliers
                                                                    [
                                                                    (0x0000001fU 
                                                                     & (IData)(vlSelfRef.Cfu__DOT__oc))]));
            __Vdly__Cfu__DOT__state = 4U;
        } else if ((4U == (IData)(vlSelfRef.Cfu__DOT__state))) {
            __Vdly__Cfu__DOT__quant_value = (0x000000ffU 
                                             & (VL_LTS_IQQ(64, vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0, (QData)((IData)(vlSelfRef.Cfu__DOT__output_zp)))
                                                 ? (IData)(vlSelfRef.Cfu__DOT__output_zp)
                                                 : 
                                                ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0) 
                                                 | (- (IData)(
                                                              VL_LTS_IQQ(64, 0x00000000000000ffULL, vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))))));
            __Vdly__Cfu__DOT__state = 5U;
        } else if ((5U == (IData)(vlSelfRef.Cfu__DOT__state))) {
            if ((1U & ((~ ((IData)(vlSelfRef.Cfu__DOT__route) 
                           >> 1U)) | (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)))) {
                if ((1U & (IData)(vlSelfRef.Cfu__DOT__route))) {
                    __Vdly__Cfu__DOT__captured = (0x0000ffffU 
                                                  & ((IData)(1U) 
                                                     + (IData)(vlSelfRef.Cfu__DOT__captured)));
                    __VdlyVal__Cfu__DOT__conv_results__v0 
                        = vlSelfRef.Cfu__DOT__quant_value;
                    __VdlyDim0__Cfu__DOT__conv_results__v0 
                        = (0x00001fffU & (IData)(vlSelfRef.Cfu__DOT__out_index));
                    __VdlySet__Cfu__DOT__conv_results__v0 = 1U;
                }
                if ((((IData)(1U) + (IData)(vlSelfRef.Cfu__DOT__out_index)) 
                     >= vlSelfRef.Cfu__DOT__total)) {
                    __Vdly__Cfu__DOT__state = 0U;
                    __Vdly__rsp_valid = 1U;
                    vlSelfRef.rsp_payload_outputs_0 
                        = vlSelfRef.Cfu__DOT__total;
                } else {
                    __Vdly__Cfu__DOT__out_index = (0x0000ffffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlSelfRef.Cfu__DOT__out_index)));
                    if (((IData)(vlSelfRef.Cfu__DOT__ox) 
                         == ((IData)(vlSelfRef.Cfu__DOT__width) 
                             - (IData)(1U)))) {
                        if (((IData)(vlSelfRef.Cfu__DOT__oy) 
                             == ((IData)(vlSelfRef.Cfu__DOT__height) 
                                 - (IData)(1U)))) {
                            __Vdly__Cfu__DOT__oc = 
                                (0x000000ffU & ((IData)(1U) 
                                                + (IData)(vlSelfRef.Cfu__DOT__oc)));
                            __Vdly__Cfu__DOT__oy = 0U;
                        } else {
                            __Vdly__Cfu__DOT__oy = 
                                (0x000000ffU & ((IData)(1U) 
                                                + (IData)(vlSelfRef.Cfu__DOT__oy)));
                        }
                        __Vdly__Cfu__DOT__ox = 0U;
                    } else {
                        __Vdly__Cfu__DOT__ox = (0x000000ffU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.Cfu__DOT__ox)));
                    }
                    __Vdly__Cfu__DOT__kernel_index = 0U;
                    __Vdly__Cfu__DOT__acc = 0U;
                    __Vdly__Cfu__DOT__state = 1U;
                }
            }
        }
        if (vlSelfRef.Cfu__DOT__accept) {
            if ((0U == (7U & (IData)(vlSelfRef.cmd_payload_function_id)))) {
                if (((((((((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U))) 
                           | (1U == (0x0000007fU & 
                                     ((IData)(vlSelfRef.cmd_payload_function_id) 
                                      >> 3U)))) | (2U 
                                                   == 
                                                   (0x0000007fU 
                                                    & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                       >> 3U)))) 
                         | (3U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U)))) 
                        | (4U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                 >> 3U)))) 
                       | (5U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                >> 3U)))) 
                      | (6U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) 
                     | (7U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                              >> 3U))))) {
                    if ((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) {
                        if ((0U != vlSelfRef.cmd_payload_inputs_0)) {
                            if ((1U != vlSelfRef.cmd_payload_inputs_0)) {
                                if ((2U == vlSelfRef.cmd_payload_inputs_0)) {
                                    if (((0U < vlSelfRef.cmd_payload_inputs_1) 
                                         & (0x00000020U 
                                            >= vlSelfRef.cmd_payload_inputs_1))) {
                                        vlSelfRef.Cfu__DOT__cin 
                                            = (0x000000ffU 
                                               & vlSelfRef.cmd_payload_inputs_1);
                                    }
                                }
                                if ((2U != vlSelfRef.cmd_payload_inputs_0)) {
                                    if ((3U != vlSelfRef.cmd_payload_inputs_0)) {
                                        if ((4U == vlSelfRef.cmd_payload_inputs_0)) {
                                            if ((0x000000ffU 
                                                 >= vlSelfRef.cmd_payload_inputs_1)) {
                                                vlSelfRef.Cfu__DOT__input_zp 
                                                    = 
                                                    (0x000000ffU 
                                                     & vlSelfRef.cmd_payload_inputs_1);
                                            }
                                        }
                                        if ((4U != vlSelfRef.cmd_payload_inputs_0)) {
                                            if ((5U 
                                                 == vlSelfRef.cmd_payload_inputs_0)) {
                                                if (
                                                    (0x000000ffU 
                                                     >= vlSelfRef.cmd_payload_inputs_1)) {
                                                    vlSelfRef.Cfu__DOT__output_zp 
                                                        = 
                                                        (0x000000ffU 
                                                         & vlSelfRef.cmd_payload_inputs_1);
                                                }
                                            }
                                            if ((5U 
                                                 != vlSelfRef.cmd_payload_inputs_0)) {
                                                if (
                                                    (6U 
                                                     == vlSelfRef.cmd_payload_inputs_0)) {
                                                    if (
                                                        ((1U 
                                                          <= vlSelfRef.cmd_payload_inputs_1) 
                                                         & (3U 
                                                            >= vlSelfRef.cmd_payload_inputs_1))) {
                                                        vlSelfRef.Cfu__DOT__route 
                                                            = 
                                                            (3U 
                                                             & vlSelfRef.cmd_payload_inputs_1);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if ((3U == vlSelfRef.cmd_payload_inputs_0)) {
                                        if (((0U < vlSelfRef.cmd_payload_inputs_1) 
                                             & (0x00000020U 
                                                >= vlSelfRef.cmd_payload_inputs_1))) {
                                            vlSelfRef.Cfu__DOT__cout 
                                                = (0x000000ffU 
                                                   & vlSelfRef.cmd_payload_inputs_1);
                                        }
                                    }
                                }
                            }
                            if ((1U == vlSelfRef.cmd_payload_inputs_0)) {
                                if (((0U < vlSelfRef.cmd_payload_inputs_1) 
                                     & (0x00000020U 
                                        >= vlSelfRef.cmd_payload_inputs_1))) {
                                    vlSelfRef.Cfu__DOT__height 
                                        = (0x000000ffU 
                                           & vlSelfRef.cmd_payload_inputs_1);
                                }
                            }
                        }
                        if ((0U == vlSelfRef.cmd_payload_inputs_0)) {
                            if (((0U < vlSelfRef.cmd_payload_inputs_1) 
                                 & (0x00000020U >= vlSelfRef.cmd_payload_inputs_1))) {
                                vlSelfRef.Cfu__DOT__width 
                                    = (0x000000ffU 
                                       & vlSelfRef.cmd_payload_inputs_1);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.reset)))) {
        if (vlSelfRef.Cfu__DOT__accept) {
            if ((0U == (7U & (IData)(vlSelfRef.cmd_payload_function_id)))) {
                if (((((((((0U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U))) 
                           | (1U == (0x0000007fU & 
                                     ((IData)(vlSelfRef.cmd_payload_function_id) 
                                      >> 3U)))) | (2U 
                                                   == 
                                                   (0x0000007fU 
                                                    & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                       >> 3U)))) 
                         | (3U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                  >> 3U)))) 
                        | (4U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                 >> 3U)))) 
                       | (5U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                >> 3U)))) 
                      | (6U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) 
                     | (7U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                              >> 3U))))) {
                    if ((0U != (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) {
                        if ((1U != (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                   >> 3U)))) {
                            if ((2U != (0x0000007fU 
                                        & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                           >> 3U)))) {
                                if ((3U == (0x0000007fU 
                                            & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                               >> 3U)))) {
                                    if (((0x00000020U 
                                          > vlSelfRef.cmd_payload_inputs_0) 
                                         & (~ (vlSelfRef.cmd_payload_inputs_1 
                                               >> 0x1fU)))) {
                                        __VdlyVal__Cfu__DOT__multipliers__v0 
                                            = vlSelfRef.cmd_payload_inputs_1;
                                        __VdlyDim0__Cfu__DOT__multipliers__v0 
                                            = (0x0000001fU 
                                               & vlSelfRef.cmd_payload_inputs_0);
                                        __VdlySet__Cfu__DOT__multipliers__v0 = 1U;
                                    }
                                }
                            }
                            if ((2U == (0x0000007fU 
                                        & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                           >> 3U)))) {
                                if (((0x00000ffcU >= vlSelfRef.cmd_payload_inputs_0) 
                                     & (0U == (3U & vlSelfRef.cmd_payload_inputs_0)))) {
                                    __VdlyVal__Cfu__DOT__weights__v0 
                                        = (0x000000ffU 
                                           & vlSelfRef.cmd_payload_inputs_1);
                                    __VdlyDim0__Cfu__DOT__weights__v0 
                                        = (0x00000fffU 
                                           & vlSelfRef.cmd_payload_inputs_0);
                                    __VdlySet__Cfu__DOT__weights__v0 = 1U;
                                    __VdlyVal__Cfu__DOT__weights__v1 
                                        = (0x000000ffU 
                                           & (vlSelfRef.cmd_payload_inputs_1 
                                              >> 8U));
                                    __VdlyDim0__Cfu__DOT__weights__v1 
                                        = (0x00000fffU 
                                           & ((IData)(1U) 
                                              + vlSelfRef.cmd_payload_inputs_0));
                                    __VdlyVal__Cfu__DOT__weights__v2 
                                        = (0x000000ffU 
                                           & (vlSelfRef.cmd_payload_inputs_1 
                                              >> 0x10U));
                                    __VdlyDim0__Cfu__DOT__weights__v2 
                                        = (0x00000fffU 
                                           & ((IData)(2U) 
                                              + vlSelfRef.cmd_payload_inputs_0));
                                    __VdlyVal__Cfu__DOT__weights__v3 
                                        = (vlSelfRef.cmd_payload_inputs_1 
                                           >> 0x18U);
                                    __VdlyDim0__Cfu__DOT__weights__v3 
                                        = (0x00000fffU 
                                           & ((IData)(3U) 
                                              + vlSelfRef.cmd_payload_inputs_0));
                                }
                            }
                        }
                        if ((1U == (0x0000007fU & ((IData)(vlSelfRef.cmd_payload_function_id) 
                                                   >> 3U)))) {
                            if (((0x000007fcU >= vlSelfRef.cmd_payload_inputs_0) 
                                 & (0U == (3U & vlSelfRef.cmd_payload_inputs_0)))) {
                                __VdlyVal__Cfu__DOT__inputs__v0 
                                    = (0x000000ffU 
                                       & vlSelfRef.cmd_payload_inputs_1);
                                __VdlyDim0__Cfu__DOT__inputs__v0 
                                    = (0x000007ffU 
                                       & vlSelfRef.cmd_payload_inputs_0);
                                __VdlySet__Cfu__DOT__inputs__v0 = 1U;
                                __VdlyVal__Cfu__DOT__inputs__v1 
                                    = (0x000000ffU 
                                       & (vlSelfRef.cmd_payload_inputs_1 
                                          >> 8U));
                                __VdlyDim0__Cfu__DOT__inputs__v1 
                                    = (0x000007ffU 
                                       & ((IData)(1U) 
                                          + vlSelfRef.cmd_payload_inputs_0));
                                __VdlyVal__Cfu__DOT__inputs__v2 
                                    = (0x000000ffU 
                                       & (vlSelfRef.cmd_payload_inputs_1 
                                          >> 0x10U));
                                __VdlyDim0__Cfu__DOT__inputs__v2 
                                    = (0x000007ffU 
                                       & ((IData)(2U) 
                                          + vlSelfRef.cmd_payload_inputs_0));
                                __VdlyVal__Cfu__DOT__inputs__v3 
                                    = (vlSelfRef.cmd_payload_inputs_1 
                                       >> 0x18U);
                                __VdlyDim0__Cfu__DOT__inputs__v3 
                                    = (0x000007ffU 
                                       & ((IData)(3U) 
                                          + vlSelfRef.cmd_payload_inputs_0));
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.Cfu__DOT__out_index = __Vdly__Cfu__DOT__out_index;
    vlSelfRef.Cfu__DOT__captured = __Vdly__Cfu__DOT__captured;
    vlSelfRef.Cfu__DOT__ox = __Vdly__Cfu__DOT__ox;
    vlSelfRef.Cfu__DOT__oy = __Vdly__Cfu__DOT__oy;
    vlSelfRef.Cfu__DOT__oc = __Vdly__Cfu__DOT__oc;
    vlSelfRef.Cfu__DOT__kernel_index = __Vdly__Cfu__DOT__kernel_index;
    vlSelfRef.Cfu__DOT__acc = __Vdly__Cfu__DOT__acc;
    vlSelfRef.Cfu__DOT__pool_armed = __Vdly__Cfu__DOT__pool_armed;
    vlSelfRef.Cfu__DOT__pool_w = __Vdly__Cfu__DOT__pool_w;
    vlSelfRef.Cfu__DOT__pool_h = __Vdly__Cfu__DOT__pool_h;
    vlSelfRef.Cfu__DOT__pool_c = __Vdly__Cfu__DOT__pool_c;
    vlSelfRef.Cfu__DOT__pool_received = __Vdly__Cfu__DOT__pool_received;
    if (__VdlySet__Cfu__DOT__multipliers__v0) {
        vlSelfRef.Cfu__DOT__multipliers[__VdlyDim0__Cfu__DOT__multipliers__v0] 
            = __VdlyVal__Cfu__DOT__multipliers__v0;
    }
    if (__VdlySet__Cfu__DOT__conv_results__v0) {
        vlSelfRef.Cfu__DOT__conv_results[__VdlyDim0__Cfu__DOT__conv_results__v0] 
            = __VdlyVal__Cfu__DOT__conv_results__v0;
    }
    if (__VdlySet__Cfu__DOT__weights__v0) {
        vlSelfRef.Cfu__DOT__weights[__VdlyDim0__Cfu__DOT__weights__v0] 
            = __VdlyVal__Cfu__DOT__weights__v0;
        vlSelfRef.Cfu__DOT__weights[__VdlyDim0__Cfu__DOT__weights__v1] 
            = __VdlyVal__Cfu__DOT__weights__v1;
        vlSelfRef.Cfu__DOT__weights[__VdlyDim0__Cfu__DOT__weights__v2] 
            = __VdlyVal__Cfu__DOT__weights__v2;
        vlSelfRef.Cfu__DOT__weights[__VdlyDim0__Cfu__DOT__weights__v3] 
            = __VdlyVal__Cfu__DOT__weights__v3;
    }
    if (__VdlySet__Cfu__DOT__inputs__v0) {
        vlSelfRef.Cfu__DOT__inputs[__VdlyDim0__Cfu__DOT__inputs__v0] 
            = __VdlyVal__Cfu__DOT__inputs__v0;
        vlSelfRef.Cfu__DOT__inputs[__VdlyDim0__Cfu__DOT__inputs__v1] 
            = __VdlyVal__Cfu__DOT__inputs__v1;
        vlSelfRef.Cfu__DOT__inputs[__VdlyDim0__Cfu__DOT__inputs__v2] 
            = __VdlyVal__Cfu__DOT__inputs__v2;
        vlSelfRef.Cfu__DOT__inputs[__VdlyDim0__Cfu__DOT__inputs__v3] 
            = __VdlyVal__Cfu__DOT__inputs__v3;
    }
    vlSelfRef.Cfu__DOT__quant_value = __Vdly__Cfu__DOT__quant_value;
    vlSelfRef.rsp_valid = __Vdly__rsp_valid;
    vlSelfRef.Cfu__DOT__state = __Vdly__Cfu__DOT__state;
    if (__VdlySet__Cfu__DOT__lx__v0) {
        vlSelfRef.Cfu__DOT__lw[0U] = 0U;
        vlSelfRef.Cfu__DOT__lw[1U] = 0U;
        vlSelfRef.Cfu__DOT__lw[2U] = 0U;
        vlSelfRef.Cfu__DOT__lw[3U] = 0U;
        vlSelfRef.Cfu__DOT__lx[0U] = 0U;
        vlSelfRef.Cfu__DOT__lx[1U] = 0U;
        vlSelfRef.Cfu__DOT__lx[2U] = 0U;
        vlSelfRef.Cfu__DOT__lx[3U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lw__v4) {
        vlSelfRef.Cfu__DOT__lw[0U] = __VdlyVal__Cfu__DOT__lw__v4;
    }
    if (__VdlySet__Cfu__DOT__lx__v6) {
        vlSelfRef.Cfu__DOT__lw[0U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lw__v6) {
        vlSelfRef.Cfu__DOT__lw[1U] = __VdlyVal__Cfu__DOT__lw__v6;
    }
    if (__VdlySet__Cfu__DOT__lx__v9) {
        vlSelfRef.Cfu__DOT__lw[1U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lw__v8) {
        vlSelfRef.Cfu__DOT__lw[2U] = __VdlyVal__Cfu__DOT__lw__v8;
    }
    if (__VdlySet__Cfu__DOT__lx__v12) {
        vlSelfRef.Cfu__DOT__lw[2U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lw__v10) {
        vlSelfRef.Cfu__DOT__lw[3U] = __VdlyVal__Cfu__DOT__lw__v10;
    }
    if (__VdlySet__Cfu__DOT__lx__v4) {
        vlSelfRef.Cfu__DOT__lx[0U] = __VdlyVal__Cfu__DOT__lx__v4;
    }
    if (__VdlySet__Cfu__DOT__lx__v5) {
        vlSelfRef.Cfu__DOT__lx[0U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v6) {
        vlSelfRef.Cfu__DOT__lx[0U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v7) {
        vlSelfRef.Cfu__DOT__lx[1U] = __VdlyVal__Cfu__DOT__lx__v7;
    }
    if (__VdlySet__Cfu__DOT__lx__v8) {
        vlSelfRef.Cfu__DOT__lx[1U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v9) {
        vlSelfRef.Cfu__DOT__lx[1U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v10) {
        vlSelfRef.Cfu__DOT__lx[2U] = __VdlyVal__Cfu__DOT__lx__v10;
    }
    if (__VdlySet__Cfu__DOT__lx__v11) {
        vlSelfRef.Cfu__DOT__lx[2U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v12) {
        vlSelfRef.Cfu__DOT__lx[2U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v13) {
        vlSelfRef.Cfu__DOT__lx[3U] = __VdlyVal__Cfu__DOT__lx__v13;
    }
    if (__VdlySet__Cfu__DOT__lx__v14) {
        vlSelfRef.Cfu__DOT__lx[3U] = 0U;
    }
    if (__VdlySet__Cfu__DOT__lx__v15) {
        vlSelfRef.Cfu__DOT__lw[3U] = 0U;
        vlSelfRef.Cfu__DOT__lx[3U] = 0U;
    }
    __VdfgRegularize_h6e95ff9d_0_3 = ((1U & (IData)(
                                                    (vlSelfRef.Cfu__DOT__product 
                                                     >> 0x0000003fU)))
                                       ? (- vlSelfRef.Cfu__DOT__product)
                                       : vlSelfRef.Cfu__DOT__product);
    vlSelfRef.cmd_ready = ((~ ((IData)(vlSelfRef.rsp_valid) 
                               | (IData)(vlSelfRef.reset))) 
                           & (0U == (IData)(vlSelfRef.Cfu__DOT__state)));
    vlSelfRef.Cfu__DOT__mac4__DOT__p0 = (0x0001ffffU 
                                         & VL_MULS_III(17, 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,9, vlSelfRef.Cfu__DOT__lx[0U])), 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,8, vlSelfRef.Cfu__DOT__lw[0U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p1 = (0x0001ffffU 
                                         & VL_MULS_III(17, 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,9, vlSelfRef.Cfu__DOT__lx[1U])), 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,8, vlSelfRef.Cfu__DOT__lw[1U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p2 = (0x0001ffffU 
                                         & VL_MULS_III(17, 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,9, vlSelfRef.Cfu__DOT__lx[2U])), 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,8, vlSelfRef.Cfu__DOT__lw[2U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p3 = (0x0001ffffU 
                                         & VL_MULS_III(17, 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,9, vlSelfRef.Cfu__DOT__lx[3U])), 
                                                       (0x0001ffffU 
                                                        & VL_EXTENDS_II(17,8, vlSelfRef.Cfu__DOT__lw[3U]))));
    __VdfgRegularize_h6e95ff9d_0_5 = ((__VdfgRegularize_h6e95ff9d_0_3 
                                       >> 0x0000001fU) 
                                      + (QData)((IData)(
                                                        ((0x40000000U 
                                                          < 
                                                          (0x7fffffffU 
                                                           & (IData)(__VdfgRegularize_h6e95ff9d_0_3))) 
                                                         | (IData)(
                                                                   (0x00000000c0000000ULL 
                                                                    == 
                                                                    (0x00000000ffffffffULL 
                                                                     & __VdfgRegularize_h6e95ff9d_0_3)))))));
    vlSelfRef.Cfu__DOT__pool__DOT__col = __Vdly__Cfu__DOT__pool__DOT__col;
    vlSelfRef.Cfu__DOT__pool__DOT__row = __Vdly__Cfu__DOT__pool__DOT__row;
    vlSelfRef.Cfu__DOT__pool__DOT__chan = __Vdly__Cfu__DOT__pool__DOT__chan;
    vlSelfRef.Cfu__DOT__pool_count = __Vdly__Cfu__DOT__pool_count;
    if (__VdlySet__Cfu__DOT__pool__DOT__results__v0) {
        vlSelfRef.Cfu__DOT__pool__DOT__results[__VdlyDim0__Cfu__DOT__pool__DOT__results__v0] 
            = __VdlyVal__Cfu__DOT__pool__DOT__results__v0;
    }
    if (__VdlySet__Cfu__DOT__pool__DOT__upper__v0) {
        vlSelfRef.Cfu__DOT__pool__DOT__upper[__VdlyDim0__Cfu__DOT__pool__DOT__upper__v0] 
            = __VdlyVal__Cfu__DOT__pool__DOT__upper__v0;
    }
    vlSelfRef.Cfu__DOT__pool__DOT__active = __Vdly__Cfu__DOT__pool__DOT__active;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (((1U 
                                                  & (IData)(
                                                            (vlSelfRef.Cfu__DOT__product 
                                                             >> 0x0000003fU)))
                                                  ? 
                                                 (- __VdfgRegularize_h6e95ff9d_0_5)
                                                  : __VdfgRegularize_h6e95ff9d_0_5) 
                                                + (QData)((IData)(vlSelfRef.Cfu__DOT__output_zp)));
    vlSelfRef.Cfu__DOT__fused_valid = ((5U == (IData)(vlSelfRef.Cfu__DOT__state)) 
                                       & ((IData)(vlSelfRef.Cfu__DOT__route) 
                                          >> 1U));
    vlSelfRef.Cfu__DOT__pool_data = (0x000000ffU & 
                                     ((IData)(vlSelfRef.Cfu__DOT__fused_valid)
                                       ? (IData)(vlSelfRef.Cfu__DOT__quant_value)
                                       : vlSelfRef.cmd_payload_inputs_0));
    vlSelfRef.Cfu__DOT__pool__DOT__pair_max = (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__left) 
                                                > (IData)(vlSelfRef.Cfu__DOT__pool_data))
                                                ? (IData)(vlSelfRef.Cfu__DOT__pool__DOT__left)
                                                : (IData)(vlSelfRef.Cfu__DOT__pool_data));
    vlSelfRef.Cfu__DOT__accept = ((IData)(vlSelfRef.cmd_valid) 
                                  & (IData)(vlSelfRef.cmd_ready));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1 = ((1U 
                                                 == 
                                                 (7U 
                                                  & (IData)(vlSelfRef.cmd_payload_function_id))) 
                                                & (IData)(vlSelfRef.Cfu__DOT__accept));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2 = ((0U 
                                                 < (IData)(vlSelfRef.Cfu__DOT__width)) 
                                                & ((0x20U 
                                                    >= (IData)(vlSelfRef.Cfu__DOT__width)) 
                                                   & ((0U 
                                                       < (IData)(vlSelfRef.Cfu__DOT__height)) 
                                                      & (0x20U 
                                                         >= (IData)(vlSelfRef.Cfu__DOT__height)))));
    vlSelfRef.Cfu__DOT__plane = ((IData)(vlSelfRef.Cfu__DOT__height) 
                                 * (IData)(vlSelfRef.Cfu__DOT__width));
    vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid 
        = ((IData)(vlSelfRef.Cfu__DOT__fused_valid) 
           | ((((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)) 
               & (8U == (0x03f8U & (IData)(vlSelfRef.cmd_payload_function_id)))) 
              & (0x000000ffU >= vlSelfRef.cmd_payload_inputs_0)));
    vlSelfRef.Cfu__DOT__total = ((IData)(vlSelfRef.Cfu__DOT__cout) 
                                 * vlSelfRef.Cfu__DOT__plane);
    vlSelfRef.Cfu__DOT__valid_pool = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2) 
                                      & ((0U < (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                         & ((0x20U 
                                             >= (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                            & ((~ (IData)(vlSelfRef.Cfu__DOT__width)) 
                                               & ((~ (IData)(vlSelfRef.Cfu__DOT__height)) 
                                                  & (0x00001000U 
                                                     >= 
                                                     (vlSelfRef.Cfu__DOT__total 
                                                      >> 2U)))))));
    vlSelfRef.Cfu__DOT__arm = (((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                                & (0U == (0x03f8U & (IData)(vlSelfRef.cmd_payload_function_id)))) 
                               & (IData)(vlSelfRef.Cfu__DOT__valid_pool));
}

void VCfu___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VCfu___024root___eval_phase__act(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_phase__act\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.clk) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCfu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    VCfu___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void VCfu___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool VCfu___024root___eval_phase__nba(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_phase__nba\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = VCfu___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                VCfu___024root___nba_sequent__TOP__0(vlSelf);
            }
        }
        VCfu___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void VCfu___024root___eval(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VCfu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("/home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/rtl/step03/cfu.v", 77, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = VCfu___024root___eval_phase__ico(vlSelf);
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VCfu___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/rtl/step03/cfu.v", 77, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VCfu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/rtl/step03/cfu.v", 77, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = VCfu___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = VCfu___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void VCfu___024root___eval_debug_assertions(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_debug_assertions\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.cmd_valid & 0xfeU)))) {
        Verilated::overWidthError("cmd_valid");
    }
    if (VL_UNLIKELY(((vlSelfRef.cmd_payload_function_id 
                      & 0xfc00U)))) {
        Verilated::overWidthError("cmd_payload_function_id");
    }
    if (VL_UNLIKELY(((vlSelfRef.rsp_ready & 0xfeU)))) {
        Verilated::overWidthError("rsp_ready");
    }
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");
    }
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
}
#endif  // VL_DEBUG
