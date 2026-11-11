// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VCfu.h for the primary calling header

#ifndef VERILATED_VCFU___024ROOT_H_
#define VERILATED_VCFU___024ROOT_H_  // guard

#include "verilated.h"


class VCfu__Syms;

class alignas(VL_CACHE_LINE_BYTES) VCfu___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(cmd_valid,0,0);
        VL_OUT8(cmd_ready,0,0);
        VL_OUT8(rsp_valid,0,0);
        VL_IN8(rsp_ready,0,0);
        VL_IN8(reset,0,0);
        CData/*2:0*/ Cfu__DOT__state;
        CData/*7:0*/ Cfu__DOT__width;
        CData/*7:0*/ Cfu__DOT__height;
        CData/*7:0*/ Cfu__DOT__cin;
        CData/*7:0*/ Cfu__DOT__cout;
        CData/*7:0*/ Cfu__DOT__input_zp;
        CData/*7:0*/ Cfu__DOT__output_zp;
        CData/*1:0*/ Cfu__DOT__route;
        CData/*7:0*/ Cfu__DOT__ox;
        CData/*7:0*/ Cfu__DOT__oy;
        CData/*7:0*/ Cfu__DOT__oc;
        CData/*7:0*/ Cfu__DOT__quant_value;
        CData/*7:0*/ Cfu__DOT__rounded;
        CData/*0:0*/ Cfu__DOT__accept;
        CData/*0:0*/ Cfu__DOT__valid_pool;
        CData/*0:0*/ Cfu__DOT__pool_done;
        CData/*0:0*/ Cfu__DOT__pool_armed;
        CData/*7:0*/ Cfu__DOT__pool_w;
        CData/*7:0*/ Cfu__DOT__pool_h;
        CData/*7:0*/ Cfu__DOT__pool_c;
        CData/*0:0*/ Cfu__DOT__arm;
        CData/*0:0*/ Cfu__DOT__fused_valid;
        CData/*7:0*/ Cfu__DOT__pool_data;
        CData/*0:0*/ Cfu__DOT____Vcellinp__pool__in_valid;
        CData/*0:0*/ Cfu__DOT____VdfgRegularize_h00d1458a_0_3;
        CData/*0:0*/ Cfu__DOT__pool__DOT__active;
        CData/*7:0*/ Cfu__DOT__pool__DOT__w;
        CData/*7:0*/ Cfu__DOT__pool__DOT__h;
        CData/*7:0*/ Cfu__DOT__pool__DOT__c;
        CData/*7:0*/ Cfu__DOT__pool__DOT__col;
        CData/*7:0*/ Cfu__DOT__pool__DOT__row;
        CData/*7:0*/ Cfu__DOT__pool__DOT__chan;
        CData/*7:0*/ Cfu__DOT__pool__DOT__left;
        CData/*7:0*/ Cfu__DOT__pool__DOT__pair_max;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __VactContinue;
        VL_IN16(cmd_payload_function_id,9,0);
        SData/*15:0*/ Cfu__DOT__out_index;
        SData/*15:0*/ Cfu__DOT__captured;
        SData/*15:0*/ Cfu__DOT__kernel_index;
        SData/*15:0*/ Cfu__DOT__pool_count;
        VL_IN(cmd_payload_inputs_0,31,0);
        VL_IN(cmd_payload_inputs_1,31,0);
        VL_OUT(rsp_payload_outputs_0,31,0);
        IData/*31:0*/ Cfu__DOT__acc;
        IData/*31:0*/ Cfu__DOT__plane;
        IData/*31:0*/ Cfu__DOT__total;
        IData/*31:0*/ Cfu__DOT__pool_received;
        IData/*31:0*/ Cfu__DOT__t;
        IData/*31:0*/ Cfu__DOT__ic;
        IData/*31:0*/ Cfu__DOT__ky;
        IData/*31:0*/ Cfu__DOT__kx;
        IData/*31:0*/ Cfu__DOT__iy;
        IData/*31:0*/ Cfu__DOT__ix;
        IData/*31:0*/ Cfu__DOT__addr;
        IData/*16:0*/ Cfu__DOT__mac4__DOT__p0;
    };
    struct {
        IData/*16:0*/ Cfu__DOT__mac4__DOT__p1;
        IData/*16:0*/ Cfu__DOT__mac4__DOT__p2;
        IData/*16:0*/ Cfu__DOT__mac4__DOT__p3;
        IData/*31:0*/ __VactIterCount;
        QData/*63:0*/ Cfu__DOT__product;
        VlUnpacked<CData/*7:0*/, 2048> Cfu__DOT__inputs;
        VlUnpacked<CData/*7:0*/, 4096> Cfu__DOT__weights;
        VlUnpacked<IData/*31:0*/, 32> Cfu__DOT__multipliers;
        VlUnpacked<CData/*7:0*/, 8192> Cfu__DOT__conv_results;
        VlUnpacked<SData/*8:0*/, 4> Cfu__DOT__lx;
        VlUnpacked<CData/*7:0*/, 4> Cfu__DOT__lw;
        VlUnpacked<CData/*7:0*/, 16> Cfu__DOT__pool__DOT__upper;
        VlUnpacked<CData/*7:0*/, 4096> Cfu__DOT__pool__DOT__results;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    VCfu__Syms* const vlSymsp;

    // CONSTRUCTORS
    VCfu___024root(VCfu__Syms* symsp, const char* v__name);
    ~VCfu___024root();
    VL_UNCOPYABLE(VCfu___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
