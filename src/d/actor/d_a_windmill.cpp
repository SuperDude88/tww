//
// Generated by dtk
// Translation Unit: d_a_windmill.cpp
//

#include "d/actor/d_a_windmill.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

const char* daWindMill_c::m_arcname[] = { "Hpu1", "Hpu2" };

/* 00000078-000000E8       .text _delete__12daWindMill_cFv */
bool daWindMill_c::_delete() {
    if (heap != NULL && mpBgW != NULL)
        dComIfG_Bgsp()->Release(mpBgW);
    dComIfG_resDelete(&mPhs, m_arcname[mType]);
    return TRUE;
}

/* 000000E8-00000108       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_ac) {
    return ((daWindMill_c*)i_ac)->CreateHeap();
}

/* 00000108-000002A0       .text CreateHeap__12daWindMill_cFv */
BOOL daWindMill_c::CreateHeap() {
    /* Nonmatching */
}

/* 000002A0-0000050C       .text CreateInit__12daWindMill_cFv */
void daWindMill_c::CreateInit() {
    /* Nonmatching */
}

/* 0000050C-00000608       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000608-00000670       .text search_wind__12daWindMill_cFv */
void daWindMill_c::search_wind() {
    fopAc_ac_c* windTag = fopAcM_SearchByName(PROC_WindTag);
    if (windTag != NULL)
        mWindTagId = fopAcM_GetID(windTag);
    else
        mWindTagId = fpcM_ERROR_PROCESS_ID_e;
}

/* 00000670-00000804       .text _create__12daWindMill_cFv */
cPhs_State daWindMill_c::_create() {
    /* Nonmatching */
}

/* 00000DC4-00000E4C       .text set_mtx__12daWindMill_cFv */
void daWindMill_c::set_mtx() {
    /* Nonmatching */
}

/* 00000E4C-00000ECC       .text _execute__12daWindMill_cFv */
bool daWindMill_c::_execute() {
    /* Nonmatching */
}

/* 00000ECC-00001048       .text hane_move__12daWindMill_cFv */
void daWindMill_c::hane_move() {
    /* Nonmatching */
}

/* 00001048-000014AC       .text set_at__12daWindMill_cFv */
void daWindMill_c::set_at() {
    /* Nonmatching */
}

/* 000014AC-000016DC       .text set_co__12daWindMill_cFv */
void daWindMill_c::set_co() {
    /* Nonmatching */
}

/* 000016DC-000017A4       .text _draw__12daWindMill_cFv */
bool daWindMill_c::_draw() {
    /* Nonmatching */
}

/* 000017A4-000017C4       .text daWindMill_Create__FPv */
static cPhs_State daWindMill_Create(void* i_ac) {
    return ((daWindMill_c*)i_ac)->_create();
}

/* 000017C4-000017E8       .text daWindMill_Delete__FPv */
static BOOL daWindMill_Delete(void* i_ac) {
    return ((daWindMill_c*)i_ac)->_delete();
}

/* 000017E8-0000180C       .text daWindMill_Draw__FPv */
static BOOL daWindMill_Draw(void* i_ac) {
    return ((daWindMill_c*)i_ac)->_draw();
}

/* 0000180C-00001830       .text daWindMill_Execute__FPv */
static BOOL daWindMill_Execute(void* i_ac) {
    return ((daWindMill_c*)i_ac)->_execute();
}

/* 00001830-00001838       .text daWindMill_IsDelete__FPv */
static BOOL daWindMill_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daWindMillMethodTable = {
    (process_method_func)daWindMill_Create,
    (process_method_func)daWindMill_Delete,
    (process_method_func)daWindMill_Execute,
    (process_method_func)daWindMill_IsDelete,
    (process_method_func)daWindMill_Draw,
};

actor_process_profile_definition g_profile_WINDMILL = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WINDMILL,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWindMill_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x011C,
    /* Actor SubMtd */ &daWindMillMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
