//
// Generated by dtk
// Translation Unit: d_timer.cpp
//

#include "d/d_timer.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_audio.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

u32 ShipRaceSeTable[] = {
    0x7530, JA_SE_SGAME_TIMER_30,
    0x4E20, JA_SE_SGAME_TIMER_30,
    0x2710, JA_SE_SGAME_TIMER_10,
    0x2328, JA_SE_SGAME_TIMER_10,
    0x1F40, JA_SE_SGAME_TIMER_10,
    0x1B58, JA_SE_SGAME_TIMER_10,
    0x1770, JA_SE_SGAME_TIMER_10,
    0x1388, JA_SE_SGAME_TIMER_10,
    0x0FA0, JA_SE_SGAME_TIMER_10,
    0x0BB8, JA_SE_SGAME_TIMER_10,
    0x07D0, JA_SE_SGAME_TIMER_10,
    0x03E8, JA_SE_SGAME_TIMER_10,
    0xFFFFFFFF, 0x0000,
};

u32 VolcanoSeTable[] = {
    0xEA60, JA_SE_MINIGAME_TIMER_30,
    0x7530, JA_SE_MINIGAME_TIMER_30,
    0x2710, JA_SE_MINIGAME_TIMER_10,
    0x2328, JA_SE_MINIGAME_TIMER_10,
    0x1F40, JA_SE_MINIGAME_TIMER_10,
    0x1B58, JA_SE_MINIGAME_TIMER_10,
    0x1770, JA_SE_MINIGAME_TIMER_10,
    0x1388, JA_SE_MINIGAME_TIMER_10,
    0x0FA0, JA_SE_MINIGAME_TIMER_10,
    0x0BB8, JA_SE_MINIGAME_TIMER_10,
    0x07D0, JA_SE_MINIGAME_TIMER_10,
    0x03E8, JA_SE_MINIGAME_TIMER_10,
    0xFFFFFFFF, 0x0000,
};

/* 8023B860-8023BCD8       .text _create__8dTimer_cFv */
cPhs_State dTimer_c::_create() {
    cPhs_State rt = dComIfG_resLoad(&mPhs, "Timer");
    fopMsg_prm_timer* prm;
    if (rt == cPhs_COMPLEATE_e) {
        prm = (fopMsg_prm_timer*)fopMsgM_GetAppend(this);
        if (prm == NULL)
            return cPhs_ERROR_e;

        dRes_info_c* resInfo = dComIfG_getObjectResInfo("Timer");
        JUT_ASSERT(0x44, resInfo != NULL);

        if (prm->mIconType == 0) {
            mpSolidHeap = mDoExt_createSolidHeapFromGameToCurrent(0x34C0, 0x20);
        } else {
            mpSolidHeap = mDoExt_createSolidHeapFromGameToCurrent(0x4260, 0x20);
        }

        if (mpSolidHeap != NULL) {
            mpScrnDraw = new dDlst_TimerScrnDraw_c();
            mpScrnDraw->setScreen("ship_race0.blo", resInfo->getArchive());
            if (prm->mIconType != 0) {
                iconTex = mpSolidHeap->alloc(0xC00, 0x20);
                JUT_ASSERT(0x5a, iconTex != NULL);
                mpScrnDraw->setIconType(iconTex, prm->mIconType);
            }

            mDoExt_restoreCurrentHeap();
            mDoExt_adjustSolidHeap(mpSolidHeap);
        } else {
            return cPhs_ERROR_e;
        }
    } else {
        return rt;
    }

    mpScrnDraw->setRupeePos(prm->mRupeePos.x, prm->mRupeePos.y);
    mpScrnDraw->setTimerPos(prm->mTimerPos.x, prm->mTimerPos.y);
    mpScrnDraw->setShowType(prm->mShowType);
    mTimerMode = prm->mTimerMode;
    if (mTimerMode == 7) {
        mLimitTime = OSMillisecondsToTicks((OSTime)dComIfG_getTimerLimitTimeMs());
        OSTime curTime = OSGetTime();
        mTime = mStartTime = curTime;
        mStartTime -= OSMillisecondsToTicks((OSTime)dComIfG_getTimerNowTimeMs());
        mState = 0;
        mTimerMode = dComIfG_getTimerMode();
        dComIfG_setTimerNowTimeMs(getTimeMs());
        dComIfG_setTimerLimitTimeMs(getLimitTimeMs());
        dComIfG_setTimerMode(mTimerMode);
        dComIfG_setTimerPtr(this);
        if (dComIfG_getTimerMode() == 3)
            mpScrnDraw->setShowType(1);
        stock_start(10);
    } else {
        mLimitTime = OSSecondsToTicks((OSTime)prm->mLimitTimeMs);
        mStartTime = 0;
        mTime = 0;
        mState = 0;
        dComIfG_setTimerNowTimeMs(getTimeMs());
        dComIfG_setTimerLimitTimeMs(getLimitTimeMs());
        dComIfG_setTimerMode(mTimerMode);
        dComIfG_setTimerPtr(this);
    }

    field_0x120 = 0;
    field_0x128 = 0;
    field_0x130 = 0;
    field_0x138 = 0;
    field_0x162 = 0;
    field_0x163 = 0;
    field_0x158 = 120;
    field_0x15c = 0;

    u32* seTable = NULL;
    mSeTableIndex = 0;
    mSeTimeLeft = 0;
    switch (mTimerMode) {
    case 2: seTable = ShipRaceSeTable; break;
    case 3: seTable = VolcanoSeTable; break;
    }
    if (seTable != NULL) {
        while (mSeTimeLeft >= 0) {
            mSeTimeLeft = seTable[mSeTableIndex * 2 + 0];
            if (getRestTimeMs() > mSeTimeLeft)
                break;
            mSeTableIndex++;
        }
    }

    return cPhs_COMPLEATE_e;
}

/* 8023BCD8-8023BF88       .text _execute__8dTimer_cFv */
BOOL dTimer_c::_execute() {
    if (field_0x162 != 1) {
        field_0x150 = getRestTimeMs();
        if (mState == 0 || mState == 1 || mState == 3) {
            mStartTime = 0;
            mTime = 0;
            if (mState == 1 || mState == 3) {
                if (--field_0x160 <= 0) {
                    if (mState == 3)
                        stock_start();
                    else
                        start();
                }
            }
        } else if (mState == 2) {
            mTime = OSGetTime();
            dComIfG_setTimerNowTimeMs(getTimeMs());
            dComIfG_setTimerLimitTimeMs(getLimitTimeMs());
            if (getRestTimeMs() <= 0) {
                mTime = mLimitTime + mStartTime;
                field_0x138 = 0;
                dComIfG_setTimerNowTimeMs(getTimeMs());
                if (mTimerMode == 3)
                    end(30);
            }
        } else {
            mTime = field_0x120;
        }
    }

    if (mState == 0 || mState == 2) {
        if (mTimerMode == 3 || mTimerMode == 2) {
            if (dMenu_flag() || dComIfGp_event_getMode() == dEvtMode_TALK_e)
                stop(1);
            else
                restart(1);
        }
    } else if (mState == 6) {
        if (mpScrnDraw->closeAnime())
            fopMsgM_Delete(this);
    } else if (mState != 5 && mState == 4) {
        if (field_0x158 <= 0) {
            if (mTimerMode == 3) {
                deleteRequest();
                mpScrnDraw->field_0x234 = 0;
            } else {
                mpScrnDraw->field_0x234 = 0;
                mState = 5;
            }
        } else {
            field_0x158--;
        }
    }

    if (field_0x15c > 5)
        mpScrnDraw->anime();
    else
        field_0x15c++;

    mpScrnDraw->setTimer(getRestTimeMs());
    mpScrnDraw->setRupee(dComIfGp_getMiniGameRupee());
    SetSE();
    return TRUE;
}

/* 8023BF88-8023BFE4       .text _draw__8dTimer_cFv */
BOOL dTimer_c::_draw() {
    if (dMenu_flag())
        return TRUE;
    dComIfGd_set2DOpa(mpScrnDraw);
    return TRUE;
}

/* 8023BFE4-8023C0B8       .text _delete__8dTimer_cFv */
BOOL dTimer_c::_delete() {
    if (mpSolidHeap != NULL)
        mDoExt_destroySolidHeap(mpSolidHeap);

    if (mTimerMode == 3 && mState != 6 && mState != 5 && mState != 4) {
        dComIfG_setTimerNowTimeMs(getTimeMs());
        dComIfG_setTimerLimitTimeMs(getLimitTimeMs());
        dComIfG_setTimerMode(mTimerMode);
    } else {
        dComIfG_setTimerNowTimeMs(0);
        dComIfG_setTimerLimitTimeMs(0);
        dComIfG_setTimerMode(-1);
    }

    dComIfG_setTimerPtr(NULL);
    dComIfG_resDelete(&mPhs, "Timer");
    return TRUE;
}

/* 8023C0B8-8023C110       .text RestTimeCheck__8dTimer_cFi */
BOOL dTimer_c::RestTimeCheck(int time) {
    bool ret = false;
    if (getRestTimeMs() <= time && time > field_0x150)
        ret = true;
    return ret;
}

/* 8023C110-8023C124       .text deleteCheck__8dTimer_cFv */
BOOL dTimer_c::deleteCheck() {
    return mState == 5;
}

/* 8023C124-8023C268       .text SetSE__8dTimer_cFv */
void dTimer_c::SetSE() {
    if (field_0x162 == 0 && mTimerMode != 4 && (getRestTimeMs() / 1000) < (field_0x150 / 1000))
        mDoAud_seStart(JA_SE_MINIGAME_TIMER_EACH);
    
    if (RestTimeCheck(mSeTimeLeft)) {
        u32* seTable;
        switch (mTimerMode) {
        case 2: seTable = ShipRaceSeTable; break;
        case 3: seTable = VolcanoSeTable; break;
        default: return;
        }
        if (seTable[mSeTableIndex * 2 + 1] != 0xFFFFFFFF) {
            mDoAud_seStart(seTable[mSeTableIndex * 2 + 1]);
            mSeTableIndex++;
            mSeTimeLeft = seTable[mSeTableIndex * 2 + 0];
        }
    }
}

/* 8023C268-8023C2CC       .text start__8dTimer_cFv */
bool dTimer_c::start() {
    if (mState == 0 || mState == 1) {
        mState = 2;
        mTime = mStartTime = OSGetTime();
        return true;
    } else {
        return false;
    }
}

/* 8023C2CC-8023C2F4       .text start__8dTimer_cFs */
bool dTimer_c::start(s16 param_1) {
    if (mState == 0) {
        field_0x160 = param_1;
        mState = 1;
        return true;
    } else {
        return false;
    }
}

/* 8023C2F4-8023C3A8       .text stock_start__8dTimer_cFv */
bool dTimer_c::stock_start() {
    if (mState == 3) {
        mState = 2;
        OSTime time = OSGetTime();
        mStartTime = time;
        mTime = time;
        mStartTime -= OSMillisecondsToTicks((OSTime)dComIfG_getTimerNowTimeMs());
        return true;
    } else {
        return false;
    }
}

/* 8023C3A8-8023C3D0       .text stock_start__8dTimer_cFs */
bool dTimer_c::stock_start(s16 param_1) {
    if (mState == 0) {
        field_0x160 = param_1;
        mState = 3;
        return true;
    } else {
        return false;
    }
}

/* 8023C3D0-8023C454       .text stop__8dTimer_cFUc */
bool dTimer_c::stop(u8 param_1) {
    if (field_0x162 == 1 || field_0x163 != 0)
        return false;

    if (mState != 2)
        return false;

    field_0x130 = OSGetTime();
    field_0x162 = 1;
    field_0x163 = param_1;
    return true;
}

/* 8023C454-8023C500       .text restart__8dTimer_cFUc */
bool dTimer_c::restart(u8 param_1) {
    if (field_0x162 != 1 || field_0x163 != param_1)
        return false;

    if (mState != 2)
        return false;

    mTime = OSGetTime();
    field_0x138 += mTime - field_0x130;
    field_0x162 = 0;
    field_0x163 = 0;
    return true;
}

/* 8023C500-8023C56C       .text end__8dTimer_cFi */
bool dTimer_c::end(int param_1) {
    if (mState != 2)
        return false;
        
    field_0x120 = OSGetTime();
    mState = 4;
    if (param_1 != -1)
        field_0x158 = param_1;
    return true;
}

/* 8023C56C-8023C57C       .text deleteRequest__8dTimer_cFv */
bool dTimer_c::deleteRequest() {
    mState = 6;
    return true;
}

/* 8023C57C-8023C5E0       .text getTimeMs__8dTimer_cFv */
s32 dTimer_c::getTimeMs() {
    return OSTicksToMilliseconds(mTime - mStartTime - field_0x138);
}

/* 8023C5E0-8023C628       .text getLimitTimeMs__8dTimer_cFv */
s32 dTimer_c::getLimitTimeMs() {
    return OSTicksToMilliseconds(mLimitTime);
}

/* 8023C628-8023C69C       .text getRestTimeMs__8dTimer_cFv */
s32 dTimer_c::getRestTimeMs() {
    OSTime time = mTime - mStartTime - field_0x138;
    time = mLimitTime - time;
    return OSTicksToMilliseconds(time);
}

/* 8023C69C-8023CA24       .text setScreen__21dDlst_TimerScrnDraw_cFPCcP10JKRArchive */
void dDlst_TimerScrnDraw_c::setScreen(const char* file, JKRArchive* arc) {
    scrn = new J2DScreen();
    scrn->set(file, arc);
    mIconPicture = NULL;
    fopMsgM_setPaneData(&mClockIcon, scrn->search('tim0'));
    fopMsgM_setPaneData(&mClockBG, scrn->search('cn00'));
    fopMsgM_setPaneData(&mTimerNumber0, scrn->search('tt01'));
    fopMsgM_setPaneData(&mTimerNumberBG, scrn->search('tn01'));
    fopMsgM_setPaneData(&mTimerBG, scrn->search('tn00'));
    fopMsgM_setPaneData(&mTimerBGShadow, scrn->search('tk00'));
    fopMsgM_setPaneData(&mRupee, scrn->search('\x00rup'));
    fopMsgM_setPaneData(&mRupeeXShadow, scrn->search('ruxk'));
    fopMsgM_setPaneData(&mRupeeShadow, scrn->search('rupk'));

    mTimerNumber[0] = scrn->search('tt02');
    mTimerNumber[1] = scrn->search('tt03');
    mTimerNumber[2] = scrn->search('tt04');
    mTimerNumber[3] = scrn->search('tt05');
    mTimerNumber[4] = scrn->search('tt06');

    mRupeeNumber[0] = scrn->search('\x00ru1');
    mRupeeNumber[1] = scrn->search('\x00ru2');
    mRupeeNumber[2] = scrn->search('\x00ru3');

    mRupeeNumberShadow[0] = scrn->search('ruk1');
    mRupeeNumberShadow[1] = scrn->search('ruk2');
    mRupeeNumberShadow[2] = scrn->search('ruk3');

    setShowType(3);
}

/* 8023CA24-8023CA78       .text changeNumberTexture__21dDlst_TimerScrnDraw_cFP7J2DPanei */
void dDlst_TimerScrnDraw_c::changeNumberTexture(J2DPane* pane, int no) {
    if (no < 0 || no >= 10)
        no = 0;

    ((J2DPicture*)pane)->changeTexture(getNumber(no), 0);
}

/* 8023CA78-8023CA8C       .text getNumber__21dDlst_TimerScrnDraw_cFi */
const char* dDlst_TimerScrnDraw_c::getNumber(int no) {
    static const char* number[] = {
        "rupy_num_00.bti",
        "rupy_num_01.bti",
        "rupy_num_02.bti",
        "rupy_num_03.bti",
        "rupy_num_04.bti",
        "rupy_num_05.bti",
        "rupy_num_06.bti",
        "rupy_num_07.bti",
        "rupy_num_08.bti",
        "rupy_num_09.bti",
    };

    return number[no];
}

/* 8023CA8C-8023CCD8       .text setTimer__21dDlst_TimerScrnDraw_cFi */
void dDlst_TimerScrnDraw_c::setTimer(int i_time) {
    int sec, min, ms;
    sec = (i_time / 1000);
    ms = i_time - sec * 1000;
    min = sec / 60;
    sec = sec - min * 60;

    changeNumberTexture(mTimerNumber0.pane, min / 10);
    changeNumberTexture(mTimerNumber[0], min % 10);
    changeNumberTexture(mTimerNumber[1], sec / 10);
    changeNumberTexture(mTimerNumber[2], sec % 10);
    changeNumberTexture(mTimerNumber[3], ms / 100);
    changeNumberTexture(mTimerNumber[4], (ms % 100) / 10);

    if (dComIfGp_event_getMode() == dEvtMode_TALK_e) {
        if (mClockIcon.mUserArea < 5) {
            mClockIcon.mUserArea++;
            f32 alpha = acc(5, 5 - mClockIcon.mUserArea, 0);
            fopMsgM_setNowAlpha(&mClockIcon, alpha);
            fopMsgM_setNowAlpha(&mClockBG, alpha);
            fopMsgM_setNowAlpha(&mTimerNumber0, alpha);
            fopMsgM_setNowAlpha(&mTimerNumberBG, alpha);
            fopMsgM_setNowAlpha(&mTimerBG, alpha);
            fopMsgM_setNowAlpha(&mTimerBGShadow, alpha);
        }
    } else {
        if (mClockIcon.mUserArea > 0) {
            mClockIcon.mUserArea--;
            f32 alpha = acc(5, 5 - mClockIcon.mUserArea, 0);
            fopMsgM_setNowAlpha(&mClockIcon, alpha);
            fopMsgM_setNowAlpha(&mClockBG, alpha);
            fopMsgM_setNowAlpha(&mTimerNumber0, alpha);
            fopMsgM_setNowAlpha(&mTimerNumberBG, alpha);
            fopMsgM_setNowAlpha(&mTimerBG, alpha);
            fopMsgM_setNowAlpha(&mTimerBGShadow, alpha);
        }
    }
}

/* 8023CCD8-8023CEF0       .text setRupee__21dDlst_TimerScrnDraw_cFs */
void dDlst_TimerScrnDraw_c::setRupee(s16 num) {
    if (num != mRupeeNum) {
        if (num < mRupeeNum) {
            mRupeeNum--;
        } else {
            mRupeeNum++;
        }

        if (mRupeeNum < 0)
            mRupeeNum = 0;

        int r001 = mRupeeNum % 10;
        int r010 = (mRupeeNum % 100) / 10;
        int r100 = mRupeeNum / 100;

        changeNumberTexture(mRupeeNumber[2], r001);
        changeNumberTexture(mRupeeNumber[1], r010);
        changeNumberTexture(mRupeeNumber[0], r100);

        changeNumberTexture(mRupeeNumberShadow[2], r001);
        changeNumberTexture(mRupeeNumberShadow[1], r010);
        changeNumberTexture(mRupeeNumberShadow[0], r100);
    }

    if (dComIfGp_event_getMode() == dEvtMode_TALK_e) {
        if (mRupee.mUserArea < 5) {
            mRupee.mUserArea++;
            f32 alpha = 1.0f - acc(5, mRupee.mUserArea, 0);
            fopMsgM_setNowAlpha(&mRupee, alpha);
            fopMsgM_setNowAlpha(&mRupeeXShadow, alpha);
            fopMsgM_setNowAlpha(&mRupeeShadow, alpha);
        }
    } else {
        if (mRupee.mUserArea > 0) {
            mRupee.mUserArea--;
            f32 alpha = 1.0f - acc(5, mRupee.mUserArea, 0);
            fopMsgM_setNowAlpha(&mRupee, alpha);
            fopMsgM_setNowAlpha(&mRupeeXShadow, alpha);
            fopMsgM_setNowAlpha(&mRupeeShadow, alpha);
        }
    }
}

/* 8023CEF0-8023CF48       .text dTm_parentPaneScale__FP18fopMsgM_pane_classP18fopMsgM_pane_classf */
void dTm_parentPaneScale(fopMsgM_pane_class* pane, fopMsgM_pane_class* parent, f32 scale) {
    pane->mPosCenter.x = parent->mPosCenter.x + scale * (pane->mPosCenterOrig.x - parent->mPosCenterOrig.x);
    pane->mPosCenter.y = parent->mPosCenter.y + scale * (pane->mPosCenterOrig.y - parent->mPosCenterOrig.y);
    fopMsgM_paneScaleXY(pane, scale);
}

/* 8023CF48-8023CF98       .text setPaneInitialPos__21dDlst_TimerScrnDraw_cFP18fopMsgM_pane_classff */
void dDlst_TimerScrnDraw_c::setPaneInitialPos(fopMsgM_pane_class* pane, f32 x, f32 y) {
    pane->mPosCenterOrig.x = x + pane->mSizeOrig.x / 2.0f;
    pane->mPosCenterOrig.y = y + pane->mSizeOrig.y / 2.0f;
    fopMsgM_paneTrans(pane, 0.0f, 0.0f);
}

/* 8023CF98-8023D0CC       .text setTimerPos__21dDlst_TimerScrnDraw_cFff */
void dDlst_TimerScrnDraw_c::setTimerPos(f32 x, f32 y) {
    setPaneInitialPos(&mClockIcon, x, y);
    setPaneInitialPos(&mClockBG, x + mClockBG.mPosTopLeftOrig.x - mClockIcon.mPosTopLeftOrig.x, y + mClockBG.mPosTopLeftOrig.y - mClockIcon.mPosTopLeftOrig.y);
    setPaneInitialPos(&mTimerNumber0, x + mTimerNumber0.mPosTopLeftOrig.x - mClockIcon.mPosTopLeftOrig.x, y + mTimerNumber0.mPosTopLeftOrig.y - mClockIcon.mPosTopLeftOrig.y);
    setPaneInitialPos(&mTimerNumberBG, x + mTimerNumberBG.mPosTopLeftOrig.x - mClockIcon.mPosTopLeftOrig.x, y + mTimerNumberBG.mPosTopLeftOrig.y - mClockIcon.mPosTopLeftOrig.y);
    setPaneInitialPos(&mTimerBG, x + mTimerBG.mPosTopLeftOrig.x - mClockIcon.mPosTopLeftOrig.x, y + mTimerBG.mPosTopLeftOrig.y - mClockIcon.mPosTopLeftOrig.y);
    setPaneInitialPos(&mTimerBGShadow, x + mTimerBGShadow.mPosTopLeftOrig.x - mClockIcon.mPosTopLeftOrig.x, y + mTimerBGShadow.mPosTopLeftOrig.y - mClockIcon.mPosTopLeftOrig.y);
}

/* 8023D0CC-8023D128       .text setRupeePos__21dDlst_TimerScrnDraw_cFff */
void dDlst_TimerScrnDraw_c::setRupeePos(f32 x, f32 y) {
    setPaneInitialPos(&mRupee, x, y);
    setPaneInitialPos(&mRupeeShadow, x, y);
}

/* 8023D128-8023D1F8       .text setShowType__21dDlst_TimerScrnDraw_cFUc */
void dDlst_TimerScrnDraw_c::setShowType(u8 type) {
    if (type & 1) {
        mClockIcon.pane->show();
        mClockBG.pane->show();
        mTimerNumber0.pane->show();
        mTimerNumberBG.pane->show();
        mTimerBG.pane->show();
        mTimerBGShadow.pane->show();
    } else {
        mClockIcon.pane->hide();
        mClockBG.pane->hide();
        mTimerNumber0.pane->hide();
        mTimerNumberBG.pane->hide();
        mTimerBG.pane->hide();
        mTimerBGShadow.pane->hide();
    }

    if (type & 2) {
        mRupee.pane->show();
        mRupeeShadow.pane->show();
        if (mIconPicture != NULL)
            mIconPicture->show();
    } else {
        mRupee.pane->hide();
        mRupeeShadow.pane->hide();
        if (mIconPicture != NULL)
            mIconPicture->hide();
    }
}

/* 8023D1F8-8023D318       .text setIconType__21dDlst_TimerScrnDraw_cFPvUc */
void dDlst_TimerScrnDraw_c::setIconType(void* tex, u8 type) {
    u32 itemNo;
    switch (type) {
    case 0:
    case 1:
    case 2:
    case 3:
        itemNo = dComIfGs_getSelectEquip(0);
        break;
    case 4:
        itemNo = dItem_FATHER_LETTER_e;
        break;
    }

    JKRArchive* arc = dComIfGp_getItemIconArchive();
    const char* iconTex = dItem_data::getTexture(itemNo);
    JKRArchive::readTypeResource(tex, 0xC00, 'TIMG', iconTex, arc);
    mIconPicture = new J2DPicture((ResTIMG*)tex);
    ((J2DPicture*)mRupee.pane)->setWhite(JUtility::TColor(0));
    ((J2DPicture*)mRupeeShadow.pane)->setWhite(JUtility::TColor(0));
    mIconPicture->setAlpha(0);
}

/* 8023D318-8023D644       .text anime__21dDlst_TimerScrnDraw_cFv */
void dDlst_TimerScrnDraw_c::anime() {
    static const s16 animeFrame[] = { 7, 15, 22 };

    if (field_0x235 == 0) {
        if (field_0x234 < animeFrame[2]) {
            field_0x234++;
        } else {
            field_0x235 = 1;
        }

        if (field_0x234 <= animeFrame[1]) {
            f32 temp_f31 = acc(animeFrame[1], field_0x234, 0);
            f32 temp_f1 = (1.0f - temp_f31) * -50.0f;

            fopMsgM_paneTrans(&mClockIcon, temp_f1, 0.0f);
            fopMsgM_paneTrans(&mClockBG, temp_f1, 0.0f);
            fopMsgM_paneTrans(&mTimerNumberBG, temp_f1, 0.0f);
            fopMsgM_paneTrans(&mTimerBG, temp_f1, 0.0f);
            fopMsgM_paneTrans(&mTimerBGShadow, temp_f1, 0.0f);
            fopMsgM_setNowAlpha(&mClockIcon, temp_f31);
            fopMsgM_setNowAlpha(&mClockBG, temp_f31);
            fopMsgM_setNowAlpha(&mTimerNumber0, temp_f31);
            fopMsgM_setNowAlpha(&mTimerNumberBG, temp_f31);
            fopMsgM_setNowAlpha(&mTimerBG, temp_f31);
            fopMsgM_setNowAlpha(&mTimerBGShadow, temp_f31);
            fopMsgM_paneScaleXY(&mClockIcon, g_menuHIO.field_0x94);
            dTm_parentPaneScale(&mClockBG, &mClockIcon, g_menuHIO.field_0x94);
            dTm_parentPaneScale(&mTimerNumber0, &mClockIcon, g_menuHIO.field_0x94);
            dTm_parentPaneScale(&mTimerNumberBG, &mClockIcon, g_menuHIO.field_0x94);
            dTm_parentPaneScale(&mTimerBG, &mClockIcon, g_menuHIO.field_0x94);
            dTm_parentPaneScale(&mTimerBGShadow, &mClockIcon, g_menuHIO.field_0x94);
        }

        if (field_0x234 > animeFrame[0] && field_0x234 <= animeFrame[2]) {
            f32 temp_f31 = acc(animeFrame[1], field_0x234 - animeFrame[0], 0);
            f32 temp_f1 = (1.0f - temp_f31) * -50.0f;

            fopMsgM_paneTrans(&mRupee, temp_f1 + g_menuHIO.field_0x9a, g_menuHIO.field_0x9c);
            fopMsgM_setNowAlpha(&mRupee, temp_f31);
            fopMsgM_setNowAlpha(&mRupeeXShadow, temp_f31);
            fopMsgM_setNowAlpha(&mRupeeShadow, temp_f31);
            fopMsgM_paneScaleXY(&mRupee, g_menuHIO.field_0xa0);
            dTm_parentPaneScale(&mRupeeShadow, &mRupee, g_menuHIO.field_0xa0);
        }
    }
}

/* 8023D644-8023D848       .text closeAnime__21dDlst_TimerScrnDraw_cFv */
BOOL dDlst_TimerScrnDraw_c::closeAnime() {
    BOOL ret = FALSE;
    field_0x234++;
    if (field_0x234 <= 7) {
        f32 temp = acc(7, field_0x234, 0);
        f32 alpha = acc(7, 7 - field_0x234, 0);
        f32 x = temp * -50.0f;
        fopMsgM_paneTrans(&mClockIcon, x, 0.0f);
        fopMsgM_paneTrans(&mClockBG, x, 0.0f);
        fopMsgM_paneTrans(&mTimerNumberBG, x, 0.0f);
        fopMsgM_paneTrans(&mTimerBG, x, 0.0f);
        fopMsgM_paneTrans(&mTimerBGShadow, x, 0.0f);
        fopMsgM_setNowAlpha(&mClockIcon, alpha);
        fopMsgM_setNowAlpha(&mClockBG, alpha);
        fopMsgM_setNowAlpha(&mTimerNumber0, alpha);
        fopMsgM_setNowAlpha(&mTimerNumberBG, alpha);
        fopMsgM_setNowAlpha(&mTimerBG, alpha);
        fopMsgM_setNowAlpha(&mTimerBGShadow, alpha);
        fopMsgM_paneTrans(&mRupee, x + g_menuHIO.field_0x9a, g_menuHIO.field_0x9c);
        fopMsgM_setNowAlpha(&mRupee, alpha);
        fopMsgM_setNowAlpha(&mRupeeXShadow, alpha);
        fopMsgM_setNowAlpha(&mRupeeShadow, alpha);
    }

    if (field_0x234 >= 7)
        ret = TRUE;

    return ret;
}

/* 8023D848-8023D8BC       .text hide__21dDlst_TimerScrnDraw_cFv */
bool dDlst_TimerScrnDraw_c::hide() {
    fopMsgM_setNowAlphaZero(&mClockIcon);
    fopMsgM_setNowAlphaZero(&mClockBG);
    fopMsgM_setNowAlphaZero(&mTimerNumber0);
    fopMsgM_setNowAlphaZero(&mTimerNumberBG);
    fopMsgM_setNowAlphaZero(&mTimerBG);
    fopMsgM_setNowAlphaZero(&mTimerBGShadow);
    fopMsgM_setNowAlphaZero(&mRupee);
    fopMsgM_setNowAlphaZero(&mRupeeXShadow);
    fopMsgM_setNowAlphaZero(&mRupeeShadow);
    return true;
}

/* 8023D8BC-8023D9A0       .text draw__21dDlst_TimerScrnDraw_cFv */
void dDlst_TimerScrnDraw_c::draw() {
    fopMsgM_setAlpha(&mClockIcon);
    fopMsgM_setAlpha(&mClockBG);
    fopMsgM_setAlpha(&mTimerNumber0);
    fopMsgM_setAlpha(&mTimerNumberBG);
    fopMsgM_setAlpha(&mTimerBG);
    fopMsgM_setAlpha(&mTimerBGShadow);
    fopMsgM_setAlpha(&mRupee);
    fopMsgM_setAlpha(&mRupeeXShadow);
    fopMsgM_setAlpha(&mRupeeShadow);
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    scrn->draw(0.0f, 0.0f, graf);
    if (mIconPicture != NULL) {
        mIconPicture->draw(mRupee.mPosTopLeft.x, mRupee.mPosTopLeft.y, mRupee.mSize.x, mRupee.mSize.y, false, false, false);
        mIconPicture->setAlpha(mRupee.mNowAlpha);
    }
}

/* 8023D9A0-8023D9C0       .text dTimer_Draw__FP8dTimer_c */
static BOOL dTimer_Draw(dTimer_c* i_this) {
    return i_this->_draw();
}

/* 8023D9C0-8023D9E0       .text dTimer_Execute__FP8dTimer_c */
static BOOL dTimer_Execute(dTimer_c* i_this) {
    return i_this->_execute();
}

/* 8023D9E0-8023D9E8       .text dTimer_IsDelete__FP8dTimer_c */
static BOOL dTimer_IsDelete(dTimer_c* i_this) {
    return TRUE;
}

/* 8023D9E8-8023DA08       .text dTimer_Delete__FP8dTimer_c */
static BOOL dTimer_Delete(dTimer_c* i_this) {
    return i_this->_delete();
}

/* 8023DA08-8023DA28       .text dTimer_Create__FP9msg_class */
static cPhs_State dTimer_Create(msg_class* i_this) {
    return ((dTimer_c*)i_this)->_create();
}

/* 8023DA28-8023DA88       .text dTimer_createTimer__FiUsUcUcffff */
fpc_ProcID dTimer_createTimer(int param_1, u16 param_2, u8 param_3, u8 param_4, f32 param_5, f32 param_6, f32 param_7, f32 param_8) {
    if (dComIfG_getTimerMode() == -1)
        return fop_Timer_create(PROC_TIMER, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, NULL);
    return fpcM_ERROR_PROCESS_ID_e;
}

/* 8023DA88-8023DAEC       .text dTimer_createStockTimer__Fv */
fpc_ProcID dTimer_createStockTimer() {
    if (dComIfG_getTimerMode() != -1)
        return fop_Timer_create(PROC_TIMER, 7, 0, 3, 0, 221.0f, 439.0f, 32.0f, 419.0f, NULL);
    return fpcM_ERROR_PROCESS_ID_e;
}

/* 8023DAEC-8023DB48       .text __dt__21dDlst_TimerScrnDraw_cFv */
dDlst_TimerScrnDraw_c::~dDlst_TimerScrnDraw_c() {
}

msg_method_class l_dTimer_Method = {
    (process_method_func)dTimer_Create,
    (process_method_func)dTimer_Delete,
    (process_method_func)dTimer_Execute,
    (process_method_func)dTimer_IsDelete,
    (process_method_func)dTimer_Draw,
};

msg_process_profile_definition g_profile_TIMER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 12,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TIMER,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dTimer_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Priority     */ 0x01D2,
    /* Msg SubMtd   */ &l_dTimer_Method,
};
