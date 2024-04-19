//
// Generated by dtk
// Translation Unit: d_event_manager.cpp
//

#include "d/d_event_manager.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

/* 800737DC-800737F4       .text init__18dEvent_exception_cFv */
void dEvent_exception_c::init() {
    mEventInfoIdx = -1;
    field_0x4 = -1;
    mState = 0;
}

/* 800737F4-80073900       .text setStartDemo__18dEvent_exception_cFi */
int dEvent_exception_c::setStartDemo(int eventInfoIdx) {
    dStage_EventInfo_c* stageEventInfo = dComIfGp_getStageEventInfo();
    if (eventInfoIdx == 0xFF) {
        mEventInfoIdx = 206;
        return 0xFF;
    } else if (eventInfoIdx >= 200) {
        mEventInfoIdx = eventInfoIdx;
        return eventInfoIdx;
    } else {
        if (stageEventInfo == NULL) {
            return 0xFF;
        } else if (eventInfoIdx == -1 || stageEventInfo->num < eventInfoIdx) {
            return 0xFF;
        } else {
            u8 switchNo = stageEventInfo->events[eventInfoIdx].field_0x13;
            if (switchNo != 0xFF) {
                if (dComIfGs_isSwitch(switchNo, dComIfGp_roomControl_getStayNo())) {
                    mEventInfoIdx = 206;
                    return 0xFF;
                }
                dComIfGs_onSwitch(switchNo, dComIfGp_roomControl_getStayNo());
            }
            mEventInfoIdx = eventInfoIdx;
        }
    }
    return eventInfoIdx;
}

/* 80073900-80073A48       .text getEventName__18dEvent_exception_cFv */
const char* dEvent_exception_c::getEventName() {
    static const char* soecial_table[] = {
        "NORMAL_COMEBACK",
        "MAGMA_COMEBACK",
        "TORNADO_COMEBACK",
        "TIMEWARP_COMEBACK",
        "SHIP_COMEBACK",
        "DEFAULT_START",
        "SHUTTER_START",
        "SHUTTER_START_STOP",
        "BS_SHUTTER_START",
        "KNOB_START",
        "KNOB_START_B",
        "FMASTER_START",
        "FALL_START",
    };

    dStage_EventInfo_c* stageEventInfo = dComIfGp_getStageEventInfo();
    stage_stag_info_class* stage_info = dComIfGp_getStageStagInfo();
    if (mEventInfoIdx == -1)
        return NULL;

    if (mEventInfoIdx == 207) {
        JUT_ASSERT(0x9b, stage_info);
        if (dStage_stagInfo_GetSTType(stage_info) == dStageType_BOSS_e)
            return "BS_SHUTTER_START";
    }

    s32 idx = mEventInfoIdx;
    if (idx > 0xc8 && idx < 0xd6) {
        return soecial_table[idx - 0xc9];
    } else {
        if (stageEventInfo == NULL)
            return NULL;
        if (stageEventInfo->num < idx)
            return NULL;
        return stageEventInfo->events[idx].mName;
    }

    return NULL;
}

/* 80073A48-80073A4C       .text debugBfProc__16dEvent_manager_cFv */
void dEvent_manager_c::debugBfProc() {
}

enum {
    dEvtSub_FLOAT_e,
    dEvtSub_XYZ_e,
    dEvtSub_UNK2_e,
    dEvtSub_INT_e,
    dEvtSub_STR_e,
};

/* 80073A4C-80073BC0       .text getSubstance__16dEvent_manager_cFP11dEvDtData_ci */
void* dEvent_manager_c::getSubstance(dEvDtData_c* data, int type) {
    if (data->getIndex() < 0 || data->getNumber() <= 0) {
        JUT_ASSERT(0x169, 0);
        return NULL;
    }

    if (type != -1 && type != data->getType()) {
        JUT_ASSERT(0x16e, 0);
    }

    s32 index;
    switch (data->getType()) {
    case dEvtSub_FLOAT_e:
    case dEvtSub_XYZ_e:
    case dEvtSub_UNK2_e:
        index = data->getIndex();
        return mList.getFDataP(index);
    case dEvtSub_INT_e:
        index = data->getIndex();
        return mList.getIDataP(index);
    case dEvtSub_STR_e:
        index = data->getIndex();
        return mList.getSDataP(index);
    default:
        JUT_ASSERT(0x182, 0);
        return NULL;
    }
}

/* 80073BC0-80073C94       .text setData__16dEvent_manager_cFPCc */
void dEvent_manager_c::setData(const char* data) {
    if (data == NULL)
        return;

    mList.setHeaderP((event_binary_data_header*)data);
    if (mList.getEventNum() > 0)
        mList.setEventP((dEvDtEvent_c*)(data + mList.getEventTop()));
    if (mList.getStaffNum() > 0)
        mList.setStaffP((dEvDtStaff_c*)(data + mList.getStaffTop()));
    if (mList.getCutNum() > 0)
        mList.setCutP((dEvDtCut_c*)(data + mList.getCutTop()));
    if (mList.getDataNum() > 0)
        mList.setDataP((dEvDtData_c*)(data + mList.getDataTop()));
    if (mList.getFDataNum() > 0)
        mList.setFDataP((f32*)(data + mList.getFDataTop()));
    if (mList.getIDataNum() > 0)
        mList.setIDataP((int*)(data + mList.getIDataTop()));
    if (mList.getSDataNum() > 0)
        mList.setSDataP((char*)(data + mList.getSDataTop()));
}

/* 80073C94-80073D10       .text create__16dEvent_manager_cFv */
BOOL dEvent_manager_c::create() {
    mList.init();
    mCameraPlay = 0;
    mException.init();
    mFlag.init();
    setData((const char*)dComIfG_getStageRes("Stage", "event_list.dat"));
    return TRUE;
}

/* 80073D10-80073D54       .text remove__16dEvent_manager_cFv */
void dEvent_manager_c::remove() {
    mList.init();
    mCameraPlay = 0;
    mException.init();
    mFlag.init();
}

/* 80073D54-80073E00       .text findObjectCallBack__FP10fopAc_ac_cPv */
static void* findObjectCallBack(fopAc_ac_c* actor, void* work) {
    dEv_seach_prm* prm = (dEv_seach_prm*)work;
    if (prm == NULL)
        return NULL;

    dStage_objectNameInf* inf = dStage_searchName(prm->mName);
    if (inf == NULL)
        return NULL;

    if (inf->mProcName == fopAcM_GetProfName(actor) && inf->mSubtype == actor->subtype && (prm->mMask == 0 || (prm->mValue == (prm->mMask & fopAcM_GetParam(actor)))))
        return actor;

    return NULL;
}

/* 80073E00-80073F14       .text extraOnObjectCallBack__FP10fopAc_ac_cPv */
static void* extraOnObjectCallBack(fopAc_ac_c* actor, void* work) {
    dEv_seach_prm* prm = (dEv_seach_prm*)work;
    if (prm == NULL)
        return NULL;

    const char* name = prm->mName;
    if (strcmp(name, "ALL") == 0) {
        fopAcM_OnStatus(actor, fopAcStts_UNK800_e);
        if (prm->mCastInFlag & 1)
            fopAcM_OnStatus(actor, fopAcStts_FORCEMOVE_e);
        return NULL;
    } else {
        dStage_objectNameInf* inf = dStage_searchName(name);
        if (inf == NULL)
            return NULL;
        if (inf->mProcName == fopAcM_GetProfName(actor) && inf->mSubtype == actor->subtype && (prm->mMask == 0 || (prm->mValue == (prm->mMask & fopAcM_GetParam(actor))))) {
            fopAcM_OnStatus(actor, fopAcStts_UNK800_e);
            if (prm->mCastInFlag & 1)
                fopAcM_OnStatus(actor, fopAcStts_FORCEMOVE_e);
        }
        return NULL;
    }
}

/* 80073F14-80073FD4       .text extraOffObjectCallBack__FP10fopAc_ac_cPv */
static void* extraOffObjectCallBack(fopAc_ac_c* actor, void* work) {
    const char* name = (const char*)work;
    if (strcmp(name, "ALL") == 0) {
        fopAcM_OffStatus(actor, fopAcStts_UNK800_e);
        fopAcM_OffStatus(actor, fopAcStts_FORCEMOVE_e);
        return NULL;
    } else {
        dStage_objectNameInf* inf = dStage_searchName(name);
        if (inf == NULL)
            return NULL;
        if (inf->mProcName == fopAcM_GetProfName(actor) && inf->mSubtype == actor->subtype) {
            fopAcM_OffStatus(actor, fopAcStts_UNK800_e);
        }
        return NULL;
    }
}

/* 80073FD4-80073FF0       .text allOffObjectCallBack__FP10fopAc_ac_cPv */
static void* allOffObjectCallBack(fopAc_ac_c* actor, void*) {
    fopAcM_OffStatus(actor, fopAcStts_UNK800_e | fopAcStts_UNK1000_e | fopAcStts_FORCEMOVE_e);
    return NULL;
}

/* 80073FF0-80074108       .text startProc__16dEvent_manager_cFP12dEvDtEvent_c */
void dEvent_manager_c::startProc(dEvDtEvent_c* event) {
    dEv_seach_prm prm(NULL, 0, 0);
    for (s32 i = 0; i < event->getNStaff(); i++) {
        int staffIdx = event->getStaff(i);
        dEvDtStaff_c* staff = mList.getStaffP(staffIdx);
        if (staff->getType() == dEvDtStaff_c::NORMAL_e) {
            fopAc_ac_c* actor = specialCast(staff->getName(), 1);
            if (actor == NULL) {
                setPrmStaff(&prm, staffIdx);
                actor = fopAcM_Search((fopAcIt_JudgeFunc)findObjectCallBack, &prm);
            }
            if (actor != NULL) {
                fopAcM_OnStatus(actor, fopAcStts_FORCEMOVE_e);
            }
        }
        if (staff->getType() == dEvDtStaff_c::ALL_e) {
            setPrmStaff(&prm, staffIdx);
            fopAcM_Search((fopAcIt_JudgeFunc)extraOnObjectCallBack, &prm);
        }
        staff->init();
    }

    event->mEventState = dEvDtEvent_c::PLAY_e;
    mFlag.init();
}

/* 80074108-80074114       .text closeProc__16dEvent_manager_cFP12dEvDtEvent_c */
void dEvent_manager_c::closeProc(dEvDtEvent_c* event) {
    event->mEventState = dEvDtEvent_c::CLOSE_e;
}

/* 80074114-800741D4       .text endProc__16dEvent_manager_cFsi */
void dEvent_manager_c::endProc(s16 eventIdx, int act) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL) {
        JUT_ASSERT(0x2ec, 0);
        return;
    }

    if (act)
        closeProc(event);

    if (event->mEventState == dEvDtEvent_c::CLOSE_e) {
        const char* all = "ALL";
        fopAcIt_Judge((fopAcIt_JudgeFunc)allOffObjectCallBack, (void*)all);
        mCameraPlay = 0;
        event->mEventState = dEvDtEvent_c::NONE_e;
    }
}

/* 800741D4-80074324       .text mainProc__16dEvent_manager_cFv */
void dEvent_manager_c::mainProc() {
    if (mList.mHeaderP != NULL) {
        dEvDtEvent_c* event;
        s32 i;

        for (i = 0; i < mList.mHeaderP->eventNum; i++) {
            event = &mList.mEventP[i];
            if (event->mEventState == dEvDtEvent_c::PLAY_e && event->finish_check())
                closeProc(event);
        }

        for (i = 0; i < mList.mHeaderP->eventNum; i++) {
            event = &mList.mEventP[i];
            if (event->mEventState == dEvDtEvent_c::ORDER_e)
                startProc(event);
        }

        for (i = 0; i < mList.mHeaderP->eventNum; i++) {
            event = &mList.mEventP[i];
            if (event->mEventState == dEvDtEvent_c::PLAY_e)
                mList.advanceCut(event);
        }

        for (i = 0; i < mList.mHeaderP->eventNum; i++) {
            event = &mList.mEventP[i];
            if (event->mEventState == dEvDtEvent_c::PLAY_e)
                event->specialStaffProc(mList.mStaffP);
        }
    }
}

/* 80074324-80074370       .text runProc__16dEvent_manager_cFv */
void dEvent_manager_c::runProc() {
    exceptionProc();
    debugBfProc();
    dComIfGp_event_check();
    mainProc();
}

/* 80074370-800743AC       .text getEventData__16dEvent_manager_cFs */
dEvDtEvent_c* dEvent_manager_c::getEventData(s16 eventIdx) {
    if (mList.mHeaderP == NULL || eventIdx < 0 || eventIdx >= mList.mHeaderP->eventNum)
        return NULL;
    return &mList.mEventP[eventIdx];
}

/* 800743AC-800744AC       .text getEventIdx__16dEvent_manager_cFPCcUc */
s16 dEvent_manager_c::getEventIdx(const char* eventName, u8 eventInfoIdx) {
    dStage_EventInfo_c* stageEventInfo = dComIfGp_getStageEventInfo();
    if (mList.mHeaderP == NULL)
        return -1;

    if (stageEventInfo != NULL && eventInfoIdx != 0xFF && stageEventInfo->num > eventInfoIdx)
        return getEventIdx(stageEventInfo->events[eventInfoIdx].mName, 0xFF);

    if (eventName == NULL)
        return -1;

    for (s32 i = 0; i < mList.mHeaderP->eventNum; i++) {
        if (strcmp(eventName, mList.mEventP[i].getName()) == 0)
            return i;
    }

    return -1;
}

/* 800744AC-800744E8       .text order__16dEvent_manager_cFs */
BOOL dEvent_manager_c::order(s16 eventIdx) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL)
        return FALSE;

    event->mEventState = dEvDtEvent_c::ORDER_e;
    return TRUE;
}

/* 800744E8-80074528       .text startCheck__16dEvent_manager_cFs */
BOOL dEvent_manager_c::startCheck(s16 eventIdx) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL)
        return FALSE;

    return (event->mEventState == dEvDtEvent_c::PLAY_e) ? TRUE : FALSE;
}

/* 80074528-80074564       .text startCheckOld__16dEvent_manager_cFPCc */
BOOL dEvent_manager_c::startCheckOld(const char* eventName) {
    return startCheck(getEventIdx(eventName, 0xFF));
}

/* 80074564-800745A4       .text endCheck__16dEvent_manager_cFs */
BOOL dEvent_manager_c::endCheck(s16 eventIdx) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL)
        return FALSE;

    return (event->mEventState == dEvDtEvent_c::CLOSE_e) ? TRUE : FALSE;
}

/* 800745A4-800745E0       .text endCheckOld__16dEvent_manager_cFPCc */
BOOL dEvent_manager_c::endCheckOld(const char* eventName) {
    return endCheck(getEventIdx(eventName, 0xFF));
}

/* 800745E0-80074718       .text getMyStaffId__16dEvent_manager_cFPCcP10fopAc_ac_ci */
int dEvent_manager_c::getMyStaffId(const char* name, fopAc_ac_c* actor, int tagId) {
    if (dComIfGp_event_getMode() == dEvtMode_NONE_e)
        return -1;

    if (mList.getHeaderP() == NULL)
        return -1;

    if (actor && !fopAcM_CheckStatus(actor, fopAcStts_FORCEMOVE_e))
        return -1;

    for (s32 i = 0; i < mList.getEventNum(); i++) {
        dEvDtEvent_c* event = mList.getEventP(i);
        if (event->mEventState == dEvDtEvent_c::PLAY_e || event->mEventState == dEvDtEvent_c::CLOSE_e || event->mEventState == dEvDtEvent_c::UNK3_e) {
            s32 nStaff = event->getNStaff();
            for (s32 j = 0; j < nStaff; j++) {
                int staffIdx = event->getStaff(j);
                dEvDtStaff_c* staff = mList.getStaffP(staffIdx);
                if (staff->mStaffType != dEvDtStaff_c::ALL_e && strcmp(name, staff->getName()) == 0 && tagId == staff->getTagID())
                    return staffIdx;
            }
        }
    }

    return -1;
}

/* 80074718-8007473C       .text getIsAddvance__16dEvent_manager_cFi */
BOOL dEvent_manager_c::getIsAddvance(int staffIdx) {
    if (staffIdx == -1)
        return FALSE;

    return mList.getStaffP(staffIdx)->mAdvance;
}

/* 8007473C-80074824       .text dEvmng_strcmp__FPCcPc */
int dEvmng_strcmp(const char* s1, char* s2) {
    u32 len1 = strlen(s1);
    u32 len2 = strlen(s2);

    if (len1 >= 100 || len2 >= 100) {
        JUT_ASSERT(0x44a, 0);
        return -1;
    }

    if (len1 > len2)
        return 1;

    for (int i = 0; i < len1; i++) {
        if (s1[i] != s2[i])
            return 1;
    }

    return 0;
}

/* 80074824-80074964       .text getMyActIdx__16dEvent_manager_cFiPCPCciii */
int dEvent_manager_c::getMyActIdx(int staffIdx, const char* const* action, int actionNum, BOOL force, int nameType) {
    if (staffIdx == -1)
        return -1;

    dEvDtStaff_c* staff = mList.getStaffP(staffIdx);
    if (staff->mbHasAction && !force)
        return staff->mCurActionIdx;

    s32 i;
    char* name = getMyNowCutName(staffIdx);
    if (name == NULL)
        return -1;

    staff->mbHasAction = true;
    for (i = 0; i < actionNum; i++) {
        JUT_ASSERT(0x46a, action[i]);

        if (nameType != 0) {
            if (dEvmng_strcmp(action[i], name) == 0) {
                staff->mCurActionIdx = i;
                return i;
            }
        } else {
            if (strcmp(action[i], name) == 0) {
                staff->mCurActionIdx = i;
                return i;
            }
        }
    }

    staff->mCurActionIdx = -1;
    return -1;
}

/* 80074964-800749A0       .text getMyActName__16dEvent_manager_cFi */
char* dEvent_manager_c::getMyActName(int staffIdx) {
    if (staffIdx == -1)
        return NULL;

    char* cutName = getMyNowCutName(staffIdx);
    if (cutName == NULL)
        return NULL;

    return cutName;
}

/* 800749A0-800749D0       .text getMyNowCutName__16dEvent_manager_cFi */
char* dEvent_manager_c::getMyNowCutName(int staffIdx) {
    if (staffIdx == -1)
        return NULL;

    return mList.getCutStaffCurrentCutP(staffIdx)->getName();
}

/* 800749D0-80074AA0       .text getMyDataP__16dEvent_manager_cFiPCci */
dEvDtData_c* dEvent_manager_c::getMyDataP(int staffIdx, const char* name, int mode) {
    if (staffIdx == -1)
        return NULL;

    dEvDtCut_c* cut;
    if (mode != 0)
        cut = mList.getCutStaffStartCutP(staffIdx);
    else
        cut = mList.getCutStaffCurrentCutP(staffIdx);

    s32 dataIdx = cut->getDataTop();
    while (dataIdx != -1) {
        dEvDtData_c* data = mList.getDataP(dataIdx);
        if (strcmp(name, data->getName()) == 0)
            return data;
        dataIdx = data->getNext();
    }

    return NULL;
}

/* 80074AA0-80074AF8       .text getMySubstanceP__16dEvent_manager_cFiPCci */
void* dEvent_manager_c::getMySubstanceP(int staffIdx, const char* name, int type) {
    dEvDtData_c* data = getMyDataP(staffIdx, name, 0);
    if (data == NULL)
        return 0;
    return getSubstance(data, type);
}

/* 80074AF8-80074B30       .text getMySubstanceNum__16dEvent_manager_cFiPCc */
s32 dEvent_manager_c::getMySubstanceNum(int staffIdx, const char* name) {
    dEvDtData_c* data = getMyDataP(staffIdx, name, 0);
    if (data == NULL)
        return 0;
    return data->mSubstanceSize;
}

/* 80074B30-80074B7C       .text cutEnd__16dEvent_manager_cFi */
void dEvent_manager_c::cutEnd(int staffIdx) {
    if (staffIdx == -1)
        return;

    dEvDtCut_c* cut = mList.getCutStaffCurrentCutP(staffIdx);
    getFlags().flagSet(cut->getFlagId());
}

/* 80074B7C-80074BB0       .text getEventPrio__16dEvent_manager_cFs */
u32 dEvent_manager_c::getEventPrio(s16 eventIdx) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL)
        return 0;
    return event->getPriority();
}

/* 80074BB0-80074BE4       .text getEventEndSound__16dEvent_manager_cFs */
u8 dEvent_manager_c::getEventEndSound(s16 eventIdx) {
    dEvDtEvent_c* event = getEventData(eventIdx);
    if (event == NULL)
        return 0;
    return event->getEndSound();
}

/* 80074BE4-80074D78       .text exceptionProc__16dEvent_manager_cFv */
void dEvent_manager_c::exceptionProc() {
    const char* eventName = mException.getEventName();
    s16 eventIdx = getEventIdx(eventName, 0xFF);

    if (eventIdx == -1) {
        mException.mEventInfoIdx = -1;
        return;
    }

    u8 mapToolID;
    if (200 <= mException.mEventInfoIdx) {
        mapToolID = 0xFF;
    } else {
        mapToolID = mException.mEventInfoIdx;
    }

    switch (mException.mState) {
    case 0:
        mException.mState = 1;
        fopAcM_orderOtherEventId(NULL, eventIdx, mapToolID);
        break;
    case 1:
        if (startCheck(eventIdx)) {
            mException.mState = 2;
            if (strcmp(eventName, "MEETSHISHIOH") == 0)
                dComIfGs_onEventBit(0x0F80);
            if (strcmp(eventName, "look_tetra") == 0)
                dComIfGs_onEventBit(0x0280);
        } else {
            fopAcM_orderOtherEvent(NULL, (char*)eventName);
        }
        break;
    case 2:
        if (endCheck(eventIdx)) {
            dComIfGp_event_reset();
            mException.mState = 0;
            mException.mEventInfoIdx = -1;
        }
        break;
    }
}

static void dummy1() {
    OSReport("EVENT_DEBUG_OFF");
}


/* 80074D78-80074DB4       .text issueStaff__16dEvent_manager_cFPCc */
void dEvent_manager_c::issueStaff(const char* name) {
    dEv_seach_prm prm(name, 0, 0);
    fopAcIt_Judge((fopAcIt_JudgeFunc)extraOnObjectCallBack, &prm);
}

/* 80074DB4-80074DDC       .text cancelStaff__16dEvent_manager_cFPCc */
void dEvent_manager_c::cancelStaff(const char* name) {
    fopAcIt_Judge((fopAcIt_JudgeFunc)extraOffObjectCallBack, (void*)name);
}

/* 80074DDC-80074DF8       .text setGoal__16dEvent_manager_cFP4cXyz */
void dEvent_manager_c::setGoal(cXyz* goal) {
    mGoal.set(*goal);
}

/* 80074DF8-80074E00       .text getGoal__16dEvent_manager_cFv */
cXyz* dEvent_manager_c::getGoal() {
    return &mGoal;
}

struct find_shutter_param {
    s16 profName;
    fopAc_ac_c* actor;
};

/* 80074E00-80074EB4       .text findShutterCallBack__FP10fopAc_ac_cPv */
static fopAc_ac_c* findShutterCallBack(fopAc_ac_c* actor, void* user) {
    find_shutter_param* param = (find_shutter_param*)user;
    if (param->profName != fopAcM_GetProfName(actor))
        return NULL;

    cXyz diff = actor->home.pos - param->actor->home.pos;
    if (diff.x < 10.0f && diff.x > -10.0f && diff.y < 10.0f && diff.y > -10.0f && diff.z < 10.0f && diff.z > -10.0f)
        return actor;

    return NULL;
}

/* 80074EB4-80074FE8       .text specialCast_Shutter__16dEvent_manager_cFsi */
fopAc_ac_c* dEvent_manager_c::specialCast_Shutter(s16 profName, int flag) {
    find_shutter_param param;
    param.profName = profName;
    param.actor = dComIfGp_getPlayer(0);

    if (dComIfGp_getPlayer(0) == NULL)
        JUT_ASSERT(0x623, 0);

    fopAc_ac_c* shutter = (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)findShutterCallBack, &param);
    if (shutter != NULL && flag) {
        cXyz goal = shutter->home.pos;
        s16 angle = param.actor->home.angle.y + 0x8000;
        goal.x += cM_ssin(angle) * 100.0f;
        goal.z += cM_scos(angle) * 100.0f;
        dComIfGp_evmng_setGoal(&goal);
        g_dComIfG_gameInfo.play.getEvent().setPt2(shutter);
    }

    return shutter;
}

/* 80074FE8-800750FC       .text specialCast__16dEvent_manager_cFPCci */
fopAc_ac_c* dEvent_manager_c::specialCast(const char* name, int flag) {
    fopAc_ac_c* actor = NULL;

    if (name == NULL)
        return NULL;

    if (strcmp(name, "SHUTTER_DOOR") == 0) {
        actor = specialCast_Shutter(PROC_DOOR10, flag);
        if (actor == NULL)
            actor = specialCast_Shutter(PROC_DOOR12, flag);
        if (actor == NULL)
            actor = specialCast_Shutter(PROC_KDDOOR, flag);
        if (actor == NULL)
            actor = specialCast_Shutter(PROC_KNOB00, flag);
        if (actor != NULL)
            dComIfGp_event_onEventFlag(0x10);
    }

    if (actor != NULL) {
        if (flag)
            fopAcM_OnStatus(actor, fopAcStts_UNK1000_e);
        else
            fopAcM_OffStatus(actor, fopAcStts_UNK1000_e);
    }

    return actor;
}

/* 800750FC-80075288       .text setPrmStaff__16dEvent_manager_cFPvi */
void dEvent_manager_c::setPrmStaff(void* work, int staffIdx) {
    dEv_seach_prm* prm = (dEv_seach_prm*)work;
    dEvDtStaff_c* staff_data = mList.getStaffP(staffIdx);
    JUT_ASSERT(0x66b, staff_data);
    JUT_ASSERT(0x66c, prm);
    prm->mName = staff_data->getName();

    dEvDtData_c* dev_prm_data = getMyDataP(staffIdx, "DEV_PRM_MASK", 1);
    if (dev_prm_data == NULL) {
        prm->mMask = 0;
        prm->mValue = 0;
    } else {
        int* i_data = (int*)getSubstance(dev_prm_data, dEvtSub_INT_e);
        JUT_ASSERT(0x678, i_data);
        prm->mMask = i_data[0];
        prm->mValue = i_data[1];
    }

    prm->mCastInFlag = 0;
    if (getMyDataP(staffIdx, "CAST_IN", 1) != NULL)
        prm->mCastInFlag |= 1;
}

/* 80075288-8007537C       .text getToolId__16dEvent_manager_cFUci */
u8 dEvent_manager_c::getToolId(u8 r4, int r31) {
    dStage_EventInfo_c* eventInfo = dComIfGp_getStageEventInfo();
    int r5 = r31;
    if (r4 == 0xFF) {
        return 0xFF;
    }
    if (eventInfo == NULL) {
        return 0xFF;
    }
    if (r4 >= eventInfo->num) {
        return 0xFF;
    }
    for (; r5 >= 0; r5--) {
        dStage_Event_dt_c* event = &eventInfo->events[r4];
        if (event->field_0x12 == 0xFF) {
            if (r5 == 0) {
                return r4;
            }
        } else if (r31 == event->field_0x12) {
            return r4;
        }
        r4 = event->field_0x0;
        if (r4 == 0xFF) {
            return 0xFF;
        }
    }
    return 0xFF;
}

/* 8007537C-80075394       .text __ct__13dEv_seach_prmFPCcUlUl */
dEv_seach_prm::dEv_seach_prm(const char* name, u32 mask, u32 value) {
    mName = name;
    mMask = mask;
    mValue = value;
    mCastInFlag = 0;
}

/* 80075394-800753A8       .text dEv_extra_createCB__FPv */
int dEv_extra_createCB(void* actor) {
    fopAcM_OnStatus((fopAc_ac_c*)actor, fopAcStts_UNK800_e);
    return 4;
}

/* 800753A8-80075450       .text dEv_talkman_get_action__Fi */
static int dEv_talkman_get_action(int param_0) {
    static char* action_table[] = {
        "WAIT",
        "TALK0",
        "TALK1",
    };
    int staffId = dComIfGp_evmng_getMyStaffId("TALKMAN");
    if (staffId == -1) {
        return -1;
    }
    int actIdx = dComIfGp_evmng_getMyActIdx(staffId, action_table, ARRAY_SIZE(action_table), FALSE, 0);
    if (actIdx == param_0) {
        dComIfGp_evmng_cutEnd(staffId);
    }
    return actIdx;
}

/* 80075450-8007548C       .text ChkPresentEnd__16dEvent_manager_cFv */
BOOL dEvent_manager_c::ChkPresentEnd() {
    return dEv_talkman_get_action(0) >= 1;
}

/* 8007548C-800754BC       .text CancelPresent__16dEvent_manager_cFv */
BOOL dEvent_manager_c::CancelPresent() {
    return dEv_talkman_get_action(1) == 1;
}

/* 800754BC-800754EC       .text checkStartDemo__16dEvent_manager_cFv */
BOOL dEvent_manager_c::checkStartDemo() {
    if (!dComIfGp_event_runCheck()) {
        return FALSE;
    }
    if (mException.mEventInfoIdx == -1) {
        return FALSE;
    }
    return TRUE;
}

static u8 daNpc_Tt_tact_table[] = {
    0x00,
    0x03,
    0x04,
    0x02,
    0x01,
};

// Fakematch: dEvmng_daNpc_Tt_Conv and dEvmng_daNpc_Tt_GetEvFlag are unused but need to appear in this TU for a match.
// Strangely, these two functions do not appear in the debug symbol maps, but do appear in the non-debug maps for both
// the demo and the full game.
#pragma force_active on

/* 800754EC-80075590       .text dEvmng_daNpc_Tt_Conv__FUc */
u8 dEvmng_daNpc_Tt_Conv(u8 param_0) {
    if (param_0 >= ARRAY_SIZE(daNpc_Tt_tact_table)) {
        JUT_ASSERT(1814, 0);
    }
    for (u8 i = 0; i < ARRAY_SIZE(daNpc_Tt_tact_table); i++) {
        if (daNpc_Tt_tact_table[i] == param_0) {
            return i;
        }
    }
    return 0;
}

/* 80075590-800755A4       .text dEvmng_daNpc_Tt_GetEvFlag__Fi */
u16 dEvmng_daNpc_Tt_GetEvFlag(int idx) {
    static u16 dance_table[] = {
        0xFD1F,
        0xFC1F,
        0xFB1F,
        0xFA1F,
        0xF91F,
    };
    return dance_table[idx];
}
