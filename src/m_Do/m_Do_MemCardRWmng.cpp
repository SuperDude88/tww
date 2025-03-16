//
// Generated by dtk
// Translation Unit: m_Do_MemCardRWmng.cpp
//

#include "m_Do/m_Do_MemCardRWmng.h"
#include "m_Do/m_Do_MemCard.h"
#include "m_Do/m_Do_dvd_thread.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "dolphin/card.h"
#include "dolphin/os/OS.h"

#include <string.h>
#include <printf.h>

static u8 sTmpBuf[0x2000] ALIGN_DECL(32);
static u8 sTmpBuf2[0x2000] ALIGN_DECL(32);
static u32 sSaveCount;

/* 80019940-80019CE8       .text mDoMemCdRWm_Store__FP12CARDFileInfoPvUl */
s32 mDoMemCdRWm_Store(CARDFileInfo* card, void* data, u32 size) {
    s32 ret;
    mDoMemCdRWm_BuildHeader((mDoMemCdRWm_HeaderData*)sTmpBuf);
    ret = CARDWrite(card, sTmpBuf, 0x2000, 0x0000);
    if (ret != CARD_ERROR_READY) return ret;

    if (!mDoMemCdRWm_CheckCardStat(card)) {
        memset(sTmpBuf, 0, 0x2000);
        ret = CARDWrite(card, sTmpBuf, 0x2000, 0x2000);
        if (ret != CARD_ERROR_READY) return ret;
        ret = CARDWrite(card, sTmpBuf, 0x2000, 0x4000);
        if (ret != CARD_ERROR_READY) return ret;
        sSaveCount = 0;
    }

    memset(sTmpBuf, 0, 0x2000);
    card_savedata* save = (card_savedata*)sTmpBuf;
    save->dataVersion = 0;
    memcpy(save->gamedata, data, size);
#if VERSION != VERSION_PAL
    save->saveCount = ++sSaveCount;
#else
    save->saveCount = dComIfGs_getPalLanguage();
#endif
    s32 csum = mDoMemCdRWm_CalcCheckSum(save, 0x1FFC);
    save->csum = csum;

    ret = CARDWrite(card, sTmpBuf, 0x2000, 0x2000);
    if (ret != CARD_ERROR_READY) return ret;
    ret = CARDRead(card, sTmpBuf, 0x2000, 0x2000);
    if (ret != CARD_ERROR_READY) return ret;
    if (mDoMemCdRWm_CalcCheckSum(sTmpBuf, 0x1FFC) != csum) return ret;

    ret = CARDWrite(card, sTmpBuf, 0x2000, 0x4000);
    if (ret != CARD_ERROR_READY) return ret;
    ret = CARDRead(card, sTmpBuf, 0x2000, 0x4000);
    if (ret != CARD_ERROR_READY) return ret;
    if (mDoMemCdRWm_CalcCheckSum(sTmpBuf, 0x1FFC) != csum) return ret;

    s32 i;
    u32 slot;
    if (mDoMemCd_getPictWriteDataPtr() != NULL) {
        if (mDoMemCd_getCopyToPos() < 3) {
            slot = mDoMemCd_getCopyToPos() * 3 + 3;
            u8* picData = mDoMemCd_getPictWriteDataPtr();
            for (i = 0; i < 3; i++, picData += 0x2000) {
                ret = CARDWrite(card, picData, 0x2000, (slot + i) * 0x2000);
                if (ret != CARD_ERROR_READY) return ret;
                ret = CARDRead(card, sTmpBuf, 0x2000, (slot + i) * 0x2000);
                if (ret != CARD_ERROR_READY) return ret;
                if (!mDoMemCdRWm_TestCheckSumPictData(picData)) return ret;
            }
        }
    } else {
        slot = dComIfGs_getDataNum() * 3 + 3;
        for (i = 0; i < 3; i++) {
            if (dComIfGp_isPictureFlag(i)) {
                memset(sTmpBuf, 0, 0x2000);
                JKRAramToMainRam(dComIfGp_getPictureBoxData(i), sTmpBuf, 0x2000);
                ret = CARDWrite(card, sTmpBuf, 0x2000, (slot + i) * 0x2000);
                if (ret != CARD_ERROR_READY) return ret;
                ret = CARDRead(card, sTmpBuf, 0x2000, (slot + i) * 0x2000);
                if (ret != CARD_ERROR_READY) return ret;
            }
        }
   }

    mDoMemCdRWm_SetCardStat(card);
    return ret;
}

/* 80019CE8-80019F4C       .text mDoMemCdRWm_Restore__FP12CARDFileInfoPvUl */
s32 mDoMemCdRWm_Restore(CARDFileInfo* card, void* dst, u32 size) {
    s32 ret;
    BOOL needsWrite = FALSE;
    BOOL invalid;
    card_savedata* save;
    card_savedata* save2;
    BOOL csum0a;
    BOOL csum1a;
    BOOL csum2a;
    BOOL csum0b;
    BOOL csum1b;
    BOOL csum2b;
    u64 serialNo;

    save = (card_savedata*)sTmpBuf;
    save2 = (card_savedata*)sTmpBuf2;
    ret = CARDRead(card, save, 0x2000, 0x2000);
    if (ret != CARD_ERROR_READY) return ret;
    csum0a = mDoMemCdRWm_TestCheckSumGameData(&save->gamedata[0]);
    csum1a = mDoMemCdRWm_TestCheckSumGameData(&save->gamedata[1]);
    csum2a = mDoMemCdRWm_TestCheckSumGameData(&save->gamedata[2]);
    ret = CARDRead(card, save2, 0x2000, 0x4000);
    if (ret != CARD_ERROR_READY) return ret;
    csum0b = mDoMemCdRWm_TestCheckSumGameData(&save2->gamedata[0]);
    csum1b = mDoMemCdRWm_TestCheckSumGameData(&save2->gamedata[1]);
    csum2b = mDoMemCdRWm_TestCheckSumGameData(&save2->gamedata[2]);
    if (!csum0a && csum0b) {
        memcpy(&save->gamedata[0], &save2->gamedata[0], sizeof(card_gamedata));
        needsWrite = TRUE;
    }
    if (!csum1a && csum2b) { // TODO: is this a bug? typo for `!csum1a && csum1b`?
        memcpy(&save->gamedata[1], &save2->gamedata[1], sizeof(card_gamedata));
        needsWrite = TRUE;
    }
    if (!csum2a && csum2b) {
        memcpy(&save->gamedata[2], &save2->gamedata[2], sizeof(card_gamedata));
        needsWrite = TRUE;
    }

    invalid = FALSE;
    if (!csum0a && !csum0b && !csum1a && !csum1b && !csum2a && !csum2b) {
        invalid = TRUE;
    }
    if (!mDoMemCdRWm_CheckCardStat(card))
        return CARD_ERROR_FATAL_ERROR;

    if (needsWrite) {
        ret = CARDWrite(card, save, 0x2000, 0x2000);
        if (ret != CARD_ERROR_READY) return ret;
        ret = CARDWrite(card, save, 0x2000, 0x4000);
        if (ret != CARD_ERROR_READY) return ret;
    }

    memcpy(dst, save->gamedata, size);
#if VERSION != VERSION_PAL
    sSaveCount = save->saveCount;
#else
    if (save->saveCount > 4) {
        g_mDoMemCd_control.field_0x165B = 0;
    } else {
        // TODO: does save->saveCount have the language index in it on PAL?
        g_mDoMemCd_control.field_0x165B = save->saveCount;
    }
#endif
    mDoMemCd_setDataVersion(save->dataVersion);
    if (!invalid && mDoMemCd_getPictDataPtr() != NULL) {
        ret = CARDRead(card, mDoMemCd_getPictDataPtr(), 0x12000, 0x6000);
        if (ret != CARD_ERROR_READY) return ret;
    }

    CARDGetSerialNo(mDoMemCd_getNowSlot(), &serialNo);
    mDoMemCd_setCardSerialNo(serialNo);

    return CARD_ERROR_READY;
}

#if VERSION == VERSION_PAL
s32 mDoMemCdRWm_Restore2(CARDFileInfo* card) {
    s32 ret;
    card_savedata* save;
    save = (card_savedata*)sTmpBuf;
    ret = CARDRead(card, save, 0x2000, 0x2000);
    if (ret != CARD_ERROR_READY) {
        ret = CARDRead(card, save, 0x2000, 0x4000);
        if (ret != CARD_ERROR_READY) return ret;
    }
    
    if (save->saveCount > 4) {
        g_mDoMemCd_control.field_0x165B = 0;
    } else {
        // TODO: does save->saveCount have the language index in it on PAL?
        g_mDoMemCd_control.field_0x165B = save->saveCount;
    }
    
    return CARD_ERROR_READY;
}
#endif

/* 80019F4C-8001A0A8       .text mDoMemCdRWm_BuildHeader__FP22mDoMemCdRWm_HeaderData */
void mDoMemCdRWm_BuildHeader(mDoMemCdRWm_HeaderData* header) {
#if VERSION == VERSION_JPN
    snprintf(header->comment, sizeof(header->comment), "ゼルダの伝説～風のタクト～");
#else
    snprintf(header->comment, sizeof(header->comment), "Zelda: The Wind Waker");
#endif
    OSTime time = OSGetTime();
    OSCalendarTime cal;
    OSTicksToCalendarTime(time, &cal);
#if VERSION == VERSION_JPN
    snprintf(header->info, sizeof(header->info), "%d月%d日のセーブデータです", cal.month + 1, cal.day_of_month);
#elif VERSION == VERSION_USA
    snprintf(header->info, sizeof(header->info), "%d/%d Save Data", cal.month + 1, cal.day_of_month);
#else
    switch (dComIfGs_getPalLanguage()) {
    case 0:
        snprintf(header->info, sizeof(header->info), "%d/%d Save Data", cal.month + 1, cal.day_of_month);
        break;
    case 1:
        snprintf(header->info, sizeof(header->info), "%d/%d Spielstand", cal.day_of_month, cal.month + 1);
        break;
    case 2:
        // Extended ASCII 0xE9 is: é ("Données de jeu")
        snprintf(header->info, sizeof(header->info), "Donn%ces de jeu %d/%d", 0xE9, cal.day_of_month, cal.month + 1);
        break;
    case 3:
        snprintf(header->info, sizeof(header->info), "Datos guardados el %d/%d", cal.day_of_month, cal.month + 1);
        break;
    case 4:
        snprintf(header->info, sizeof(header->info), "Dati salvati: %d/%d", cal.day_of_month, cal.month + 1);
        break;
    }
#endif
    mDoDvdThd_mountArchive_c* cmd = mDoDvdThd_mountArchive_c::create("/res/CardIcon/cardicon.arc", 0, NULL);
    while (!cmd->sync()) ;
    JKRArchive* arc = cmd->getArchive();
    ResTIMG* banner = (ResTIMG*)arc->getResource("ipl_banner.bti");
    ResTIMG* icon = (ResTIMG*)arc->getResource("ipl_icon1.bti");
    memcpy(header->banner, ((char*)banner) + banner->imageOffset, 0xc00 + banner->numColors * 2);
    memcpy(header->icon, ((char*)icon) + icon->imageOffset, 0x400 + icon->numColors * 2);
    arc->unmount();
    delete cmd;
}

/* 8001A0A8-8001A1EC       .text mDoMemCdRWm_SetCardStat__FP12CARDFileInfo */
void mDoMemCdRWm_SetCardStat(CARDFileInfo* card) {
    CARDStat stat;
    CARDGetStatus(mDoMemCd_getNowSlot(), card->fileNo, &stat);
    stat.iconAddr = 0;
    stat.commentAddr = offsetof(mDoMemCdRWm_HeaderData, comment);
    CARDSetBannerFormat(&stat, 1);
    CARDSetIconAnim(&stat, 0);
    CARDSetIconFormat(&stat, 0, 1);
    CARDSetIconFormat(&stat, 1, 0);
    CARDSetIconFormat(&stat, 2, 0);
    CARDSetIconFormat(&stat, 3, 0);
    CARDSetIconFormat(&stat, 4, 0);
    CARDSetIconFormat(&stat, 5, 0);
    CARDSetIconFormat(&stat, 6, 0);
    CARDSetIconFormat(&stat, 7, 0);
    CARDSetIconSpeed(&stat, 0, 3);
    CARDSetIconSpeed(&stat, 1, 0);
    CARDSetIconSpeed(&stat, 2, 0);
    CARDSetIconSpeed(&stat, 3, 0);
    CARDSetIconSpeed(&stat, 4, 0);
    CARDSetIconSpeed(&stat, 5, 0);
    CARDSetIconSpeed(&stat, 6, 0);
    CARDSetIconSpeed(&stat, 7, 0);
    CARDSetStatus(mDoMemCd_getNowSlot(), card->fileNo, &stat);;
}

/* 8001A1EC-8001A2F0       .text mDoMemCdRWm_CheckCardStat__FP12CARDFileInfo */
BOOL mDoMemCdRWm_CheckCardStat(CARDFileInfo* card) {
    CARDStat stat;
    CARDGetStatus(mDoMemCd_getNowSlot(), card->fileNo, &stat);
    if (!(stat.iconAddr == 0 &&
        stat.commentAddr == 0x1C00 &&
        CARDGetBannerFormat(&stat) == 1 &&
        CARDGetIconAnim(&stat) == 0 &&
        CARDGetIconFormat(&stat, 0) == 1 &&
        CARDGetIconFormat(&stat, 1) == 0 &&
        CARDGetIconFormat(&stat, 2) == 0 &&
        CARDGetIconFormat(&stat, 3) == 0 &&
        CARDGetIconFormat(&stat, 4) == 0 &&
        CARDGetIconFormat(&stat, 5) == 0 &&
        CARDGetIconFormat(&stat, 6) == 0 &&
        CARDGetIconFormat(&stat, 7) == 0 &&
        CARDGetIconSpeed(&stat, 0) == 3 &&
        CARDGetIconSpeed(&stat, 1) == 0 &&
        CARDGetIconSpeed(&stat, 2) == 0 &&
        CARDGetIconSpeed(&stat, 3) == 0 &&
        CARDGetIconSpeed(&stat, 4) == 0 &&
        CARDGetIconSpeed(&stat, 5) == 0 &&
        CARDGetIconSpeed(&stat, 6) == 0 &&
        CARDGetIconSpeed(&stat, 7) == 0))
        return false;
    return true;
}

/* 8001A2F0-8001A330       .text mDoMemCdRWm_CalcCheckSum__FPvUl */
u32 mDoMemCdRWm_CalcCheckSum(void* p_, u32 size) {
    u16 c0, c1;

    c0 = c1 = 0;
    u16* p = (u16*)p_;
    for (int i = 0; i < size >> 1; i++, p++) {
        c0 += *p;
        c1 += ~*p;
    }
    return (c0 << 16) | c1;
}

/* 8001A330-8001A358       .text mDoMemCdRWm_CalcCheckSumPictData__FPvUl */
u16 mDoMemCdRWm_CalcCheckSumPictData(void* p, u32 size) {
    u16 csum = 0;
    for (int i = 0; i < size; i++) {
        u8 v = ((u8*)p)[i];
        csum += v;
    }
    return csum;
}

/* 8001A358-8001A39C       .text mDoMemCdRWm_TestCheckSumPictData__FPv */
BOOL mDoMemCdRWm_TestCheckSumPictData(void* p) {
    card_pictdata* save = (card_pictdata*)p;
    u32 csum = mDoMemCdRWm_CalcCheckSumPictData(save->data, sizeof(save->data));
    return csum == save->csum;
}

/* 8001A39C-8001A3D0       .text mDoMemCdRWm_SetCheckSumPictData__FPUc */
void mDoMemCdRWm_SetCheckSumPictData(u8* p) {
    card_pictdata* save = (card_pictdata*)p;
    save->csum = mDoMemCdRWm_CalcCheckSumPictData(save->data, sizeof(save->data));
}

/* 8001A3D0-8001A408       .text mDoMemCdRWm_CalcCheckSumGameData__FPvUl */
u64 mDoMemCdRWm_CalcCheckSumGameData(void* p, u32 size) {
    u32 c0, c1;
    c0 = c1 = 0;
    for (int i = 0; i < size; i++) {
        u8 v = ((u8*)p)[i];
        c0 += v;
        c1 += ~v;
    }
    return ((u64)c0 << 32) | c1;
}

/* 8001A408-8001A454       .text mDoMemCdRWm_TestCheckSumGameData__FPv */
BOOL mDoMemCdRWm_TestCheckSumGameData(void *p) {
    card_gamedata* save = (card_gamedata*)p;
    u64 csum = mDoMemCdRWm_CalcCheckSumGameData(save->data, sizeof(save->data));
    return csum == save->csum;
}

/* 8001A454-8001A498       .text mDoMemCdRWm_SetCheckSumGameData__FPUcUc */
void mDoMemCdRWm_SetCheckSumGameData(u8* p, u8 slot) {
    card_gamedata* save = &((card_gamedata*)p)[slot];
    save->csum = mDoMemCdRWm_CalcCheckSumGameData(save->data, sizeof(save->data));
}
