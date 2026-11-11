// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCfu.h for the primary calling header

#include "VCfu__pch.h"

VL_ATTR_COLD void VCfu___024root___eval_static(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_static\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__cmd_valid__0 = vlSelfRef.cmd_valid;
    vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_function_id__0 
        = vlSelfRef.cmd_payload_function_id;
    vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_0__0 
        = vlSelfRef.cmd_payload_inputs_0;
    vlSelfRef.__Vtrigprevexpr___TOP__cmd_payload_inputs_1__0 
        = vlSelfRef.cmd_payload_inputs_1;
    vlSelfRef.__Vtrigprevexpr___TOP__rsp_ready__0 = vlSelfRef.rsp_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
}

VL_ATTR_COLD void VCfu___024root___eval_initial(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_initial\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VCfu___024root___eval_final(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_final\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VCfu___024root___eval_phase__stl(VCfu___024root* vlSelf);

VL_ATTR_COLD void VCfu___024root___eval_settle(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_settle\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VCfu___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/rtl/step03/cfu.v", 77, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = VCfu___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD bool VCfu___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VCfu___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VCfu___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void VCfu___024root___stl_sequent__TOP__0(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___stl_sequent__TOP__0\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ __VdfgRegularize_h6e95ff9d_0_3;
    __VdfgRegularize_h6e95ff9d_0_3 = 0;
    QData/*63:0*/ __VdfgRegularize_h6e95ff9d_0_5;
    __VdfgRegularize_h6e95ff9d_0_5 = 0;
    // Body
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
    __VdfgRegularize_h6e95ff9d_0_3 = ((1U & (IData)(
                                                    (vlSelfRef.Cfu__DOT__product 
                                                     >> 0x0000003fU)))
                                       ? (- vlSelfRef.Cfu__DOT__product)
                                       : vlSelfRef.Cfu__DOT__product);
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
    vlSelfRef.Cfu__DOT__fused_valid = ((5U == (IData)(vlSelfRef.Cfu__DOT__state)) 
                                       & ((IData)(vlSelfRef.Cfu__DOT__route) 
                                          >> 1U));
    vlSelfRef.cmd_ready = ((~ ((IData)(vlSelfRef.rsp_valid) 
                               | (IData)(vlSelfRef.reset))) 
                           & (0U == (IData)(vlSelfRef.Cfu__DOT__state)));
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
    vlSelfRef.Cfu__DOT__total = ((IData)(vlSelfRef.Cfu__DOT__cout) 
                                 * vlSelfRef.Cfu__DOT__plane);
    vlSelfRef.Cfu__DOT__pool_data = (0x000000ffU & 
                                     ((IData)(vlSelfRef.Cfu__DOT__fused_valid)
                                       ? (IData)(vlSelfRef.Cfu__DOT__quant_value)
                                       : vlSelfRef.cmd_payload_inputs_0));
    vlSelfRef.Cfu__DOT__accept = ((IData)(vlSelfRef.cmd_valid) 
                                  & (IData)(vlSelfRef.cmd_ready));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (((1U 
                                                  & (IData)(
                                                            (vlSelfRef.Cfu__DOT__product 
                                                             >> 0x0000003fU)))
                                                  ? 
                                                 (- __VdfgRegularize_h6e95ff9d_0_5)
                                                  : __VdfgRegularize_h6e95ff9d_0_5) 
                                                + (QData)((IData)(vlSelfRef.Cfu__DOT__output_zp)));
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
    vlSelfRef.Cfu__DOT__pool__DOT__pair_max = (((IData)(vlSelfRef.Cfu__DOT__pool__DOT__left) 
                                                > (IData)(vlSelfRef.Cfu__DOT__pool_data))
                                                ? (IData)(vlSelfRef.Cfu__DOT__pool__DOT__left)
                                                : (IData)(vlSelfRef.Cfu__DOT__pool_data));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1 = ((1U 
                                                 == 
                                                 (7U 
                                                  & (IData)(vlSelfRef.cmd_payload_function_id))) 
                                                & (IData)(vlSelfRef.Cfu__DOT__accept));
    vlSelfRef.Cfu__DOT__arm = (((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                                & (0U == (0x03f8U & (IData)(vlSelfRef.cmd_payload_function_id)))) 
                               & (IData)(vlSelfRef.Cfu__DOT__valid_pool));
    vlSelfRef.Cfu__DOT____Vcellinp__pool__in_valid 
        = ((IData)(vlSelfRef.Cfu__DOT__fused_valid) 
           | ((((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1) 
                & (IData)(vlSelfRef.Cfu__DOT__pool__DOT__active)) 
               & (8U == (0x03f8U & (IData)(vlSelfRef.cmd_payload_function_id)))) 
              & (0x000000ffU >= vlSelfRef.cmd_payload_inputs_0)));
}

VL_ATTR_COLD bool VCfu___024root___eval_phase__stl(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___eval_phase__stl\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__stl
        vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                          & vlSelfRef.__VstlTriggered[0U]) 
                                         | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCfu___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = VCfu___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                VCfu___024root___stl_sequent__TOP__0(vlSelf);
            }
        }
    }
    return (__VstlExecute);
}

bool VCfu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(VCfu___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( cmd_valid)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( cmd_payload_function_id)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( cmd_payload_inputs_0)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( cmd_payload_inputs_1)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( rsp_ready)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( reset)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @( clk)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool VCfu___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VCfu___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VCfu___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCfu___024root___ctor_var_reset(VCfu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCfu___024root___ctor_var_reset\n"); );
    VCfu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->cmd_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15271417814813862642ull);
    vlSelf->cmd_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7995897193997220869ull);
    vlSelf->cmd_payload_function_id = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 6341658374547602449ull);
    vlSelf->cmd_payload_inputs_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5090902211731559383ull);
    vlSelf->cmd_payload_inputs_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4353949643659258655ull);
    vlSelf->rsp_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1421612161635894276ull);
    vlSelf->rsp_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11749926944769377044ull);
    vlSelf->rsp_payload_outputs_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4106283163885505612ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->Cfu__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13087696225557209601ull);
    vlSelf->Cfu__DOT__width = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11641363208258575258ull);
    vlSelf->Cfu__DOT__height = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4093029362285720432ull);
    vlSelf->Cfu__DOT__cin = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15201031112377415064ull);
    vlSelf->Cfu__DOT__cout = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9598703086134305561ull);
    vlSelf->Cfu__DOT__input_zp = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11557109744440175495ull);
    vlSelf->Cfu__DOT__output_zp = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7831840731054921497ull);
    vlSelf->Cfu__DOT__route = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 270227384272770164ull);
    for (int __Vi0 = 0; __Vi0 < 2048; ++__Vi0) {
        vlSelf->Cfu__DOT__inputs[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4998189603870633285ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->Cfu__DOT__weights[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17782173465543066492ull);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->Cfu__DOT__multipliers[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11568573740324292374ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8192; ++__Vi0) {
        vlSelf->Cfu__DOT__conv_results[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1004471814864447179ull);
    }
    vlSelf->Cfu__DOT__out_index = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1941280110146583832ull);
    vlSelf->Cfu__DOT__captured = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1738928441410614840ull);
    vlSelf->Cfu__DOT__ox = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10127645929072484040ull);
    vlSelf->Cfu__DOT__oy = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15736930913961245457ull);
    vlSelf->Cfu__DOT__oc = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 322172332794688866ull);
    vlSelf->Cfu__DOT__kernel_index = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11804942099923891888ull);
    vlSelf->Cfu__DOT__acc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2272595943676908215ull);
    vlSelf->Cfu__DOT__product = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18078605823873416522ull);
    vlSelf->Cfu__DOT__quant_value = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6117662365237085946ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->Cfu__DOT__lx[__Vi0] = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 5244984289515377011ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->Cfu__DOT__lw[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4120467071609038301ull);
    }
    vlSelf->Cfu__DOT__accept = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7823523663100605384ull);
    vlSelf->Cfu__DOT__plane = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8075128898967694363ull);
    vlSelf->Cfu__DOT__total = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 103961383574290991ull);
    vlSelf->Cfu__DOT__valid_pool = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6055411571161656349ull);
    vlSelf->Cfu__DOT__pool_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14167693376357865820ull);
    vlSelf->Cfu__DOT__pool_count = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6638271205543255388ull);
    vlSelf->Cfu__DOT__pool_received = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17330947998817742798ull);
    vlSelf->Cfu__DOT__pool_armed = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9488919239445553533ull);
    vlSelf->Cfu__DOT__pool_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15234519408690679399ull);
    vlSelf->Cfu__DOT__pool_h = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 977043192967298624ull);
    vlSelf->Cfu__DOT__pool_c = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2258372621848478267ull);
    vlSelf->Cfu__DOT__arm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11992325306643040279ull);
    vlSelf->Cfu__DOT__fused_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 641717344661267111ull);
    vlSelf->Cfu__DOT__pool_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16243724641430356036ull);
    vlSelf->Cfu__DOT____Vcellinp__pool__in_valid = 0;
    vlSelf->Cfu__DOT__t = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9008718543265529762ull);
    vlSelf->Cfu__DOT__ic = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8540883099083749749ull);
    vlSelf->Cfu__DOT__ky = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17055426789402666079ull);
    vlSelf->Cfu__DOT__kx = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2959457811867284101ull);
    vlSelf->Cfu__DOT__iy = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12091027914346241623ull);
    vlSelf->Cfu__DOT__ix = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 778295037095992355ull);
    vlSelf->Cfu__DOT__addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7308306031926614734ull);
    vlSelf->Cfu__DOT__pool__DOT__active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15201476928601695229ull);
    vlSelf->Cfu__DOT__pool__DOT__w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13573382948318562633ull);
    vlSelf->Cfu__DOT__pool__DOT__h = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16491133961235913907ull);
    vlSelf->Cfu__DOT__pool__DOT__c = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1829596596734525624ull);
    vlSelf->Cfu__DOT__pool__DOT__col = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16876186185141712034ull);
    vlSelf->Cfu__DOT__pool__DOT__row = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6499349168484195340ull);
    vlSelf->Cfu__DOT__pool__DOT__chan = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14715186248588426618ull);
    vlSelf->Cfu__DOT__pool__DOT__left = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12234901872824249222ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->Cfu__DOT__pool__DOT__upper[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16972510326498645454ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->Cfu__DOT__pool__DOT__results[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9004336852206311228ull);
    }
    vlSelf->Cfu__DOT__pool__DOT__pair_max = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16831851654257477356ull);
    vlSelf->Cfu__DOT__mac4__DOT__p0 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 10357107406686833909ull);
    vlSelf->Cfu__DOT__mac4__DOT__p1 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 11598008231467421905ull);
    vlSelf->Cfu__DOT__mac4__DOT__p2 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 12754741623437718718ull);
    vlSelf->Cfu__DOT__mac4__DOT__p3 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 4964376139283881237ull);
    vlSelf->__VdfgRegularize_h6e95ff9d_0_0 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_1 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_2 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__cmd_valid__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__cmd_payload_function_id__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__cmd_payload_inputs_0__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__cmd_payload_inputs_1__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rsp_ready__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__reset__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
