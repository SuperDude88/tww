//
// Generated by dtk
// Translation Unit: d_a_tag_ghostship.cpp
//

#include "d/actor/d_a_tag_ghostship.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

// Needed for .data to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static daTag_Gship_HIO_c l_HIO;

/* 000000EC-0000010C .text __ct__17daTag_Gship_HIO_cFv */
daTag_Gship_HIO_c::daTag_Gship_HIO_c() {
    field_0x04 = -1;
    field_0x05 = 0;
}

/* 0000010C-00000110 .text modeClearWaitInit__13daTag_Gship_cFv */
void daTag_Gship_c::modeClearWaitInit() {
    return;
}

/* 00000110-000001C0 .text modeClearWait__13daTag_Gship_cFv */
void daTag_Gship_c::modeClearWait() {
    if(dComIfGp_evmng_endCheck("DEFAULT_TREASURE") || dComIfGp_evmng_endCheck("DEFAULT_TREASURE2") || dComIfGp_evmng_endCheck("DEFAULT_TREASURE_A") || l_HIO.field_0x05) {
        modeProc(CLEAR_WAIT, 1);
    }
}

/* 000001C0-00000214 .text modeClearEventInit__13daTag_Gship_cFv */
void daTag_Gship_c::modeClearEventInit() {
    dComIfGs_getEventReg(0x8803);
    dComIfGs_setEventReg(0x8803, 3);
}

/* 00000214-00000418 .text modeClearEvent__13daTag_Gship_cFv */
void daTag_Gship_c::modeClearEvent() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("PScnChg");
        if(strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "WARAIGOE") == 0) {
            if(dComIfGs_getEventReg(0x8803) == 3) {
                mDoAud_seStart(JA_SE_CV_G_SHIP_SCREAM);
            } else {
                mDoAud_seStart(JA_SE_CV_G_SHIP_LAUGH);
            }

            dComIfGp_evmng_cutEnd(staffIdx);
        }

        if(dComIfGp_evmng_endCheck("PSHIP_CLEAR")) {
            mDoAud_seStart(JA_SE_LK_WARP_TO_G_SHIP);
            s8 room = dComIfGs_getEventReg(0xC3FF);
            s8 spawn = dComIfGs_getEventReg(0x85FF);
            dKy_set_nexttime(120.0f);
            dComIfGp_setNextStage("sea", spawn, room, 0xFF, 0.0f, 5);
        }
    }
    else {
        fopAcM_orderOtherEvent(this, "PSHIP_CLEAR");
    }
}

/* 00000418-00000508 .text modeProc__13daTag_Gship_cFQ213daTag_Gship_c6Proc_ei */
void daTag_Gship_c::modeProc(daTag_Gship_c::Proc_e proc, int param_2) {
    typedef void(daTag_Gship_c::*ProcFunc)(void);
    struct ProcEntry {
        ProcFunc init;
        ProcFunc run;
        const char* name;
    };

    static const ProcEntry mode_proc[] = {
        {
            &daTag_Gship_c::modeClearWaitInit,
            &daTag_Gship_c::modeClearWait,
            "CLEAR_WAIT"
        },
        {
            &daTag_Gship_c::modeClearEventInit,
            &daTag_Gship_c::modeClearEvent,
            "CLEAR_EVENT"
        }
    };

    if(proc == CLEAR_WAIT) {
        mMode = param_2;
        (this->*mode_proc[mMode].init)();
    }
    else if(proc == CLEAR_EVENT) {
        (this->*mode_proc[mMode].run)();
    }
}

/* 00000508-00000534 .text _execute__13daTag_Gship_cFv */
bool daTag_Gship_c::_execute() {
    modeProc(CLEAR_EVENT, 2);
    return true;
}

/* 00000534-0000053C .text _draw__13daTag_Gship_cFv */
bool daTag_Gship_c::_draw() {
    return true;
}

/* 0000053C-00000594 .text getArg__13daTag_Gship_cFv */
void daTag_Gship_c::getArg() {
    u32 param = fopAcM_GetParam(this);

    field_0x294 = param;
    s32 bit = fopAcM_GetParamBit(param, 8, 8);
    if(bit == 0xFF) {
        field_0x298 = 1000.0f;
    }
    else {
        field_0x298 = bit * 100;
    }
}

/* 00000594-000005EC .text _create__13daTag_Gship_cFv */
s32 daTag_Gship_c::_create() {
    fopAcM_SetupActor(this, daTag_Gship_c);

    getArg();

    return cPhs_COMPLEATE_e;
}

/* 000005EC-000005F4 .text _delete__13daTag_Gship_cFv */
bool daTag_Gship_c::_delete() {
    return true;
}

/* 000005F4-00000614 .text daTag_GshipCreate__FPv */
static s32 daTag_GshipCreate(void* i_this) {
    return static_cast<daTag_Gship_c*>(i_this)->_create();
}

/* 00000614-00000638 .text daTag_GshipDelete__FPv */
static BOOL daTag_GshipDelete(void* i_this) {
    return static_cast<daTag_Gship_c*>(i_this)->_delete();
}

/* 00000638-0000065C .text daTag_GshipExecute__FPv */
static BOOL daTag_GshipExecute(void* i_this) {
    return static_cast<daTag_Gship_c*>(i_this)->_execute();
}

/* 0000065C-00000680 .text daTag_GshipDraw__FPv */
static BOOL daTag_GshipDraw(void* i_this) {
    return static_cast<daTag_Gship_c*>(i_this)->_draw();
}

/* 00000680-00000688 .text daTag_GshipIsDelete__FPv */
static BOOL daTag_GshipIsDelete(void*) {
    return true;
}


static actor_method_class daTag_GshipMethodTable = {
    (process_method_func)daTag_GshipCreate,
    (process_method_func)daTag_GshipDelete,
    (process_method_func)daTag_GshipExecute,
    (process_method_func)daTag_GshipIsDelete,
    (process_method_func)daTag_GshipDraw,
};

actor_process_profile_definition g_profile_TAG_GSHIP = {
    fpcLy_CURRENT_e,
    8,
    fpcPi_CURRENT_e,
    PROC_TAG_GSHIP,
    &g_fpcLf_Method.base,
    sizeof(daTag_Gship_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0066,
    &daTag_GshipMethodTable,
    fopAcStts_UNK40000_e | fopAcStts_UNK4000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_4_e,
};
