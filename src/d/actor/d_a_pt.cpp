//
// Generated by dtk
// Translation Unit: d_a_pt.cpp
//

#include "d/actor/d_a_pt.h"
#include "d/d_procname.h"

/* 000000EC-00000110       .text __ct__10daPt_HIO_cFv */
daPt_HIO_c::daPt_HIO_c() {
    /* Nonmatching */
}

/* 00000110-00000238       .text anm_init__FP8pt_classifUcfi */
void anm_init(pt_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000238-00000360       .text daPt_Draw__FP8pt_class */
static BOOL daPt_Draw(pt_class*) {
    /* Nonmatching */
}

/* 0000039C-00000484       .text smoke_set__FP8pt_classSc */
void smoke_set(pt_class*, signed char) {
    /* Nonmatching */
}

/* 00000484-0000093C       .text damage_check__FP8pt_class */
void damage_check(pt_class*) {
    /* Nonmatching */
}

/* 0000093C-00000D74       .text get_z_ang__FP8pt_class */
void get_z_ang(pt_class*) {
    /* Nonmatching */
}

/* 000011AC-000018EC       .text next_pos_set__FP8pt_class */
void next_pos_set(pt_class*) {
    /* Nonmatching */
}

/* 000018EC-00001DC0       .text pt_move__FP8pt_class */
void pt_move(pt_class*) {
    /* Nonmatching */
}

/* 00001DC0-000020D4       .text view_check__FP8pt_class */
void view_check(pt_class*) {
    /* Nonmatching */
}

/* 000020D4-00002528       .text pt_attack__FP8pt_class */
void pt_attack(pt_class*) {
    /* Nonmatching */
}

/* 00002528-00002AC8       .text pt_wait__FP8pt_class */
void pt_wait(pt_class*) {
    /* Nonmatching */
}

/* 00002AC8-00002F30       .text pt_koke__FP8pt_class */
void pt_koke(pt_class*) {
    /* Nonmatching */
}

/* 00002F30-00003028       .text pt_ples__FP8pt_class */
void pt_ples(pt_class*) {
    /* Nonmatching */
}

/* 00003028-000031DC       .text pt_bat__FP8pt_class */
void pt_bat(pt_class*) {
    /* Nonmatching */
}

/* 000031DC-000036C0       .text water_check__FP8pt_class */
void water_check(pt_class*) {
    /* Nonmatching */
}

/* 00003B00-00003B4C       .text esa_s_sub__FPvPv */
void esa_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00003B4C-00003F5C       .text action__FP8pt_class */
void action(pt_class*) {
    /* Nonmatching */
}

/* 00003F5C-000043C8       .text daPt_Execute__FP8pt_class */
static BOOL daPt_Execute(pt_class*) {
    /* Nonmatching */
}

/* 000043C8-000043D0       .text daPt_IsDelete__FP8pt_class */
static BOOL daPt_IsDelete(pt_class*) {
    /* Nonmatching */
}

/* 000043D0-00004540       .text daPt_Delete__FP8pt_class */
static BOOL daPt_Delete(pt_class*) {
    /* Nonmatching */
}

/* 00004540-000047D4       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000481C-00004B1C       .text daPt_Create__FP10fopAc_ac_c */
static cPhs_State daPt_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daPt_Method = {
    (process_method_func)daPt_Create,
    (process_method_func)daPt_Delete,
    (process_method_func)daPt_Execute,
    (process_method_func)daPt_IsDelete,
    (process_method_func)daPt_Draw,
};

actor_process_profile_definition g_profile_PT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(pt_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00EC,
    /* Actor SubMtd */ &l_daPt_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
