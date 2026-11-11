// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCfu.h for the primary calling header

#include "VCfu__pch.h"
#include "VCfu___024root.h"

VL_ATTR_COLD void VCfu___024root___eval_static(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VCfu___024root___eval_initial(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void VCfu___024root___eval_final(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__stl(VCfu___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VCfu___024root___eval_phase__stl(VCfu___024root* vlSelf);

VL_ATTR_COLD void VCfu___024root___eval_settle(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            VCfu___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/mnt/g/Meetings/Mahmoudi/MNIST_CFU_FUSION_20261013_V1/rtl/step03/cfu.v", 77, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VCfu___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__stl(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCfu___024root___stl_sequent__TOP__0(VCfu___024root* vlSelf);

VL_ATTR_COLD void VCfu___024root___eval_stl(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VCfu___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void VCfu___024root___stl_sequent__TOP__0(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___stl_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ Cfu__DOT____VdfgRegularize_h00d1458a_0_2;
    Cfu__DOT____VdfgRegularize_h00d1458a_0_2 = 0;
    QData/*63:0*/ Cfu__DOT__requant__DOT__mag;
    Cfu__DOT__requant__DOT__mag = 0;
    QData/*63:0*/ Cfu__DOT__requant__DOT__rounded;
    Cfu__DOT__requant__DOT__rounded = 0;
    QData/*63:0*/ Cfu__DOT__requant__DOT__shifted;
    Cfu__DOT__requant__DOT__shifted = 0;
    // Body
    vlSelfRef.Cfu__DOT__mac4__DOT__p0 = (0x1ffffU & 
                                         VL_MULS_III(17, 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,9, 
                                                                      vlSelfRef.Cfu__DOT__lx
                                                                      [0U])), 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,8, 
                                                                      vlSelfRef.Cfu__DOT__lw
                                                                      [0U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p1 = (0x1ffffU & 
                                         VL_MULS_III(17, 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,9, 
                                                                      vlSelfRef.Cfu__DOT__lx
                                                                      [1U])), 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,8, 
                                                                      vlSelfRef.Cfu__DOT__lw
                                                                      [1U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p2 = (0x1ffffU & 
                                         VL_MULS_III(17, 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,9, 
                                                                      vlSelfRef.Cfu__DOT__lx
                                                                      [2U])), 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,8, 
                                                                      vlSelfRef.Cfu__DOT__lw
                                                                      [2U]))));
    vlSelfRef.Cfu__DOT__mac4__DOT__p3 = (0x1ffffU & 
                                         VL_MULS_III(17, 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,9, 
                                                                      vlSelfRef.Cfu__DOT__lx
                                                                      [3U])), 
                                                     (0x1ffffU 
                                                      & VL_EXTENDS_II(17,8, 
                                                                      vlSelfRef.Cfu__DOT__lw
                                                                      [3U]))));
    Cfu__DOT__requant__DOT__mag = ((1U & (IData)((vlSelfRef.Cfu__DOT__product 
                                                  >> 0x3fU)))
                                    ? (- vlSelfRef.Cfu__DOT__product)
                                    : vlSelfRef.Cfu__DOT__product);
    Cfu__DOT__requant__DOT__rounded = VL_SHIFTR_QQI(64,64,32, Cfu__DOT__requant__DOT__mag, 0x1fU);
    if (((0x40000000U < (0x7fffffffU & (IData)(Cfu__DOT__requant__DOT__mag))) 
         | ((0x40000000U == (0x7fffffffU & (IData)(Cfu__DOT__requant__DOT__mag))) 
            & (IData)(Cfu__DOT__requant__DOT__rounded)))) {
        Cfu__DOT__requant__DOT__rounded = (1ULL + Cfu__DOT__requant__DOT__rounded);
    }
    Cfu__DOT__requant__DOT__shifted = (((1U & (IData)(
                                                      (vlSelfRef.Cfu__DOT__product 
                                                       >> 0x3fU)))
                                         ? (- Cfu__DOT__requant__DOT__rounded)
                                         : Cfu__DOT__requant__DOT__rounded) 
                                       + (QData)((IData)(vlSelfRef.Cfu__DOT__output_zp)));
    vlSelfRef.Cfu__DOT__rounded = (0xffU & (VL_LTS_IQQ(64, Cfu__DOT__requant__DOT__shifted, (QData)((IData)(vlSelfRef.Cfu__DOT__output_zp)))
                                             ? (IData)(vlSelfRef.Cfu__DOT__output_zp)
                                             : (VL_LTS_IQQ(64, 0xffULL, Cfu__DOT__requant__DOT__shifted)
                                                 ? 0xffU
                                                 : (IData)(Cfu__DOT__requant__DOT__shifted))));
    vlSelfRef.Cfu__DOT____VdfgRegularize_h00d1458a_0_3 
        = ((0U < (IData)(vlSelfRef.Cfu__DOT__width)) 
           & ((0x20U >= (IData)(vlSelfRef.Cfu__DOT__width)) 
              & ((0U < (IData)(vlSelfRef.Cfu__DOT__height)) 
                 & (0x20U >= (IData)(vlSelfRef.Cfu__DOT__height)))));
    vlSelfRef.Cfu__DOT__plane = ((IData)(vlSelfRef.Cfu__DOT__width) 
                                 * (IData)(vlSelfRef.Cfu__DOT__height));
    vlSelfRef.Cfu__DOT__fused_valid = ((5U == (IData)(vlSelfRef.Cfu__DOT__state)) 
                                       & ((IData)(vlSelfRef.Cfu__DOT__route) 
                                          >> 1U));
    vlSelfRef.cmd_ready = ((~ ((IData)(vlSelfRef.reset) 
                               | (IData)(vlSelfRef.rsp_valid))) 
                           & (0U == (IData)(vlSelfRef.Cfu__DOT__state)));
    vlSelfRef.Cfu__DOT__total = (vlSelfRef.Cfu__DOT__plane 
                                 * (IData)(vlSelfRef.Cfu__DOT__cout));
    vlSelfRef.Cfu__DOT__pool_data = (0xffU & ((IData)(vlSelfRef.Cfu__DOT__fused_valid)
                                               ? (IData)(vlSelfRef.Cfu__DOT__quant_value)
                                               : vlSelfRef.cmd_payload_inputs_0));
    vlSelfRef.Cfu__DOT__accept = ((IData)(vlSelfRef.cmd_valid) 
                                  & (IData)(vlSelfRef.cmd_ready));
    vlSelfRef.Cfu__DOT__valid_pool = ((~ (IData)(vlSelfRef.Cfu__DOT__width)) 
                                      & ((IData)(vlSelfRef.Cfu__DOT____VdfgRegularize_h00d1458a_0_3) 
                                         & ((~ (IData)(vlSelfRef.Cfu__DOT__height)) 
                                            & ((0U 
                                                < (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                               & ((0x20U 
                                                   >= (IData)(vlSelfRef.Cfu__DOT__cout)) 
                                                  & (0x1000U 
                                                     >= 
                                                     VL_SHIFTR_III(32,32,32, vlSelfRef.Cfu__DOT__total, 2U)))))));
    vlSelfRef.Cfu__DOT__pool__DOT__pair_max = (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__left) 
                                                > (IData)(vlSelfRef.Cfu__DOT__pool_data))
                                                ? (IData)(vlSelfRef.Cfu__DOT__pool__DOT__left)
                                                : (IData)(vlSelfRef.Cfu__DOT__pool_data));
    Cfu__DOT____VdfgRegularize_h00d1458a_0_2 = ((IData)(vlSelfRef.Cfu__DOT__accept) 
                                                & (1U 
                                                   == 
                                                   (7U 
                                                    & (IData)(vlSelfRef.cmd_payload_function_id))));
    vlSelfRef.Cfu__DOT__arm = ((IData)(Cfu__DOT____VdfgRegularize_h00d1458a_0_2) 
                               & (IData)(((0U == (0x3f8U 
                                                  & (IData)(vlSelfRef.cmd_payload_function_id))) 
                                          & (IData)(vlSelfRef.Cfu__DOT__valid_pool))));
    vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid 
        = ((IData)(vlSelfRef.Cfu__DOT__fused_valid) 
           | ((IData)(Cfu__DOT____VdfgRegularize_h00d1458a_0_2) 
              & (IData)((((8U == (0x3f8U & (IData)(vlSelfRef.cmd_payload_function_id))) 
                          & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)) 
                         & (0xffU >= vlSelfRef.cmd_payload_inputs_0)))));
}

VL_ATTR_COLD void VCfu___024root___eval_triggers__stl(VCfu___024root* vlSelf);

VL_ATTR_COLD bool VCfu___024root___eval_phase__stl(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VCfu___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        VCfu___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__ico(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__act(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__nba(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCfu___024root___ctor_var_reset(VCfu___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->cmd_valid = VL_RAND_RESET_I(1);
    vlSelf->cmd_ready = VL_RAND_RESET_I(1);
    vlSelf->cmd_payload_function_id = VL_RAND_RESET_I(10);
    vlSelf->cmd_payload_inputs_0 = VL_RAND_RESET_I(32);
    vlSelf->cmd_payload_inputs_1 = VL_RAND_RESET_I(32);
    vlSelf->rsp_valid = VL_RAND_RESET_I(1);
    vlSelf->rsp_ready = VL_RAND_RESET_I(1);
    vlSelf->rsp_payload_outputs_0 = VL_RAND_RESET_I(32);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->Cfu__DOT__width = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__height = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__cin = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__cout = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__input_zp = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__output_zp = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__route = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 2048; ++__Vi0) {
        vlSelf->Cfu__DOT__inputs[__Vi0] = VL_RAND_RESET_I(8);
    }
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->Cfu__DOT__weights[__Vi0] = VL_RAND_RESET_I(8);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->Cfu__DOT__multipliers[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 8192; ++__Vi0) {
        vlSelf->Cfu__DOT__conv_results[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->Cfu__DOT__out_index = VL_RAND_RESET_I(16);
    vlSelf->Cfu__DOT__captured = VL_RAND_RESET_I(16);
    vlSelf->Cfu__DOT__ox = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__oy = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__oc = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__kernel_index = VL_RAND_RESET_I(16);
    vlSelf->Cfu__DOT__acc = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__product = VL_RAND_RESET_Q(64);
    vlSelf->Cfu__DOT__quant_value = VL_RAND_RESET_I(8);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->Cfu__DOT__lx[__Vi0] = VL_RAND_RESET_I(9);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->Cfu__DOT__lw[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->Cfu__DOT__rounded = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__accept = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__plane = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__total = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__valid_pool = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__pool_done = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__pool_count = VL_RAND_RESET_I(16);
    vlSelf->Cfu__DOT__pool_received = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__pool_armed = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__pool_w = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool_h = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool_c = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__arm = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__fused_valid = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__pool_data = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT____Vcellinp__pool__in_valid = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__t = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__ic = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__ky = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__kx = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__iy = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__ix = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT__addr = VL_RAND_RESET_I(32);
    vlSelf->Cfu__DOT____VdfgRegularize_h00d1458a_0_3 = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__mac4__DOT__p0 = VL_RAND_RESET_I(17);
    vlSelf->Cfu__DOT__mac4__DOT__p1 = VL_RAND_RESET_I(17);
    vlSelf->Cfu__DOT__mac4__DOT__p2 = VL_RAND_RESET_I(17);
    vlSelf->Cfu__DOT__mac4__DOT__p3 = VL_RAND_RESET_I(17);
    vlSelf->Cfu__DOT__pool__DOT__active = VL_RAND_RESET_I(1);
    vlSelf->Cfu__DOT__pool__DOT__w = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__h = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__c = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__col = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__row = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__chan = VL_RAND_RESET_I(8);
    vlSelf->Cfu__DOT__pool__DOT__left = VL_RAND_RESET_I(8);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->Cfu__DOT__pool__DOT__upper[__Vi0] = VL_RAND_RESET_I(8);
    }
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->Cfu__DOT__pool__DOT__results[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->Cfu__DOT__pool__DOT__pair_max = VL_RAND_RESET_I(8);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
