//
// Generated by dtk
// Translation Unit: d_a_acorn_leaf.cpp
//

#include "d/actor/d_a_acorn_leaf.h"
#include "d/d_procname.h"

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000010C-00000258       .text CreateHeap__9daAleaf_cFv */
void daAleaf_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000258-00000314       .text CreateInit__9daAleaf_cFv */
void daAleaf_c::CreateInit() {
    /* Nonmatching */
}

/* 00000314-00000384       .text create_acorn__9daAleaf_cFv */
void daAleaf_c::create_acorn() {
    /* Nonmatching */
}

/* 00000384-00000460       .text create_acorn_sub__9daAleaf_cFb */
void daAleaf_c::create_acorn_sub(bool) {
    /* Nonmatching */
}

/* 0000049C-000005EC       .text _create__9daAleaf_cFv */
cPhs_State daAleaf_c::_create() {
    /* Nonmatching */
}

/* 00000848-000008D0       .text set_mtx__9daAleaf_cFv */
void daAleaf_c::set_mtx() {
    /* Nonmatching */
}

/* 000008D0-00000C44       .text _execute__9daAleaf_cFv */
bool daAleaf_c::_execute() {
    /* Nonmatching */
}

/* 00000C44-00000CD4       .text _draw__9daAleaf_cFv */
bool daAleaf_c::_draw() {
    /* Nonmatching */
}

/* 00000CD4-00000CF4       .text daAleaf_Create__FPv */
static cPhs_State daAleaf_Create(void*) {
    /* Nonmatching */
}

/* 00000CF4-00000D24       .text daAleaf_Delete__FPv */
static BOOL daAleaf_Delete(void*) {
    /* Nonmatching */
}

/* 00000D24-00000D48       .text daAleaf_Draw__FPv */
static BOOL daAleaf_Draw(void*) {
    /* Nonmatching */
}

/* 00000D48-00000D6C       .text daAleaf_Execute__FPv */
static BOOL daAleaf_Execute(void*) {
    /* Nonmatching */
}

/* 00000D6C-00000D74       .text daAleaf_IsDelete__FPv */
static BOOL daAleaf_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daAleafMethodTable = {
    (process_method_func)daAleaf_Create,
    (process_method_func)daAleaf_Delete,
    (process_method_func)daAleaf_Execute,
    (process_method_func)daAleaf_IsDelete,
    (process_method_func)daAleaf_Draw,
};

actor_process_profile_definition g_profile_ACORN_LEAF = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ACORN_LEAF,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daAleaf_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0118,
    /* Actor SubMtd */ &daAleafMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
