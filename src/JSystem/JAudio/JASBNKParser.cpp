//
// Generated by dtk
// Translation Unit: JASBNKParser.cpp
//

#include "JSystem/JAudio/JASBNKParser.h"
#include "JSystem/JAudio/JASBasicBank.h"
#include "JSystem/JAudio/JASBasicInst.h"
#include "JSystem/JAudio/JASCalc.h"
#include "JSystem/JAudio/JASDrumSet.h"
#include "JSystem/JAudio/JASInstRand.h"
#include "JSystem/JAudio/JASInstSense.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JUtility/JUTAssert.h"

u32 JASystem::BNKParser::sUsedHeapSize;

/* 802870F0-802879A0       .text createBasicBank__Q28JASystem9BNKParserFPv */
JASystem::TBasicBank* JASystem::BNKParser::createBasicBank(void* stream) {
    /* Nonmatching - regswap */
    JKRHeap* heap = TBank::getCurrentHeap();
    const u32 freeSize = heap->getFreeSize();
    THeader* header = (THeader*)stream;
    TBasicBank* bank = new (heap, 0) TBasicBank();
    if (bank == NULL) {
        return NULL;
    }
    bank->setInstCount(0x100);

    for (int i = 0; i < 0x80; i++) {
        TInst* instRaw = JSUConvertOffsetToPtr<TInst>(header, header->mInstOffsets[i]);
        if (instRaw != NULL) {
            TBasicInst* instp = new (heap, 0) TBasicInst();
            JUT_ASSERT(56, instp != NULL);
            instp->field_0x4 = instRaw->field_0x8;
            instp->field_0x8 = instRaw->field_0xC;

            instp->setOscCount(2);
            for (int oscIndex = 0, j = 0; j < 2; j++) {
                TOsc* oscRaw = JSUConvertOffsetToPtr<TOsc>(header, instRaw->mOscOffsets[j]);
                if (oscRaw != NULL) {
                    TOscillator::Osc_* osc = findOscPtr(bank, header, oscRaw);
                    if (osc == NULL) {
                        osc = new (heap, 0) TOscillator::Osc_();
                        JUT_ASSERT(72, osc != NULL);
                        osc->field_0x0 = oscRaw->field_0x0;
                        osc->field_0x4 = oscRaw->field_0x4;
                        s16* oscTable = JSUConvertOffsetToPtr<s16>(header, oscRaw->field_0x8);
                        if (oscTable != NULL) {
                            s32 tableLength = getOscTableEndPtr(oscTable) - oscTable;
                            osc->table = new (heap, 0) s16[tableLength];
                            JUT_ASSERT(82, osc->table != NULL);
                            Calc::bcopy(oscTable, osc->table, tableLength * sizeof(s16));
                        } else {
                            osc->table = NULL;
                        }
                        oscTable = JSUConvertOffsetToPtr<s16>(header, oscRaw->field_0xC);
                        if (oscTable != NULL) {
                            s32 tableLength = getOscTableEndPtr(oscTable) - oscTable;
                            osc->rel_table = new (heap, 0) s16[tableLength];
                            JUT_ASSERT(94, osc->rel_table != NULL);
                            Calc::bcopy(oscTable, osc->rel_table, tableLength * sizeof(s16));
                        } else {
                            osc->rel_table = NULL;
                        }
                        osc->field_0x10 = oscRaw->field_0x10;
                        osc->field_0x14 = oscRaw->field_0x14;
                    }
                    instp->setOsc(oscIndex, osc);
                    oscIndex++;
                }
            }

            instp->setEffectCount(4);
            for (int j = 0; j < 2; j++) {
                TRand* randRaw = JSUConvertOffsetToPtr<TRand>(header, instRaw->mRandOffsets[j]);
                if (randRaw != NULL) {
                    TInstRand* randp = new (heap, 0) TInstRand();
                    JUT_ASSERT(120, randp != NULL);
                    randp->setTarget(randRaw->field_0x0);
                    randp->field_0x8 = randRaw->field_0x4;
                    randp->field_0xc = randRaw->field_0x8;
                    instp->setEffect(j, randp);
                }
            }
            for (int j = 0; j < 2; j++) {
                TSense* senseRaw = JSUConvertOffsetToPtr<TSense>(header, instRaw->mSenseOffsets[j]);
                if (senseRaw != NULL) {
                    TInstSense* sensep = new (heap, 0) TInstSense();
                    JUT_ASSERT(133, sensep != NULL);
                    sensep->setTarget(senseRaw->field_0x0);
                    sensep->setParams(senseRaw->field_0x1, senseRaw->field_0x2, senseRaw->field_0x4, senseRaw->field_0x8);
                    instp->setEffect(j + 2, sensep);
                }
            }

            instp->setKeyRegionCount(instRaw->mKeyRegionCount);
            for (int j = 0; j < instRaw->mKeyRegionCount; j++) {
                TBasicInst::TKeymap* instKeymap = instp->getKeyRegion(j);
                TKeymap* keymapRaw = JSUConvertOffsetToPtr<TKeymap>(header, instRaw->mKeymapOffsets[j]);
                instKeymap->mBaseKey = keymapRaw->field_0x0;
                instKeymap->setVeloRegionCount(keymapRaw->field_0x4);
                for (int k = 0; k < keymapRaw->field_0x4; k++) {
                    TBasicInst::TVeloRegion* instVeloRegion = instKeymap->getVeloRegion(k);
                    TVmap* vmapRaw = JSUConvertOffsetToPtr<TVmap>(header, keymapRaw->mVmapOffsets[k]);
                    instVeloRegion->mBaseVel = vmapRaw->field_0x0;
                    instVeloRegion->field_0x04 = vmapRaw->field_0x4 & 0xFFFF;
                    instVeloRegion->field_0x08 = vmapRaw->field_0x8;
                    instVeloRegion->field_0x0c = vmapRaw->field_0xC;
                }
            }
            bank->setInst(i, instp);
        }
    }

    for (int i = 0; i < 12; i++) {
        TPerc* percRaw = JSUConvertOffsetToPtr<TPerc>(header, header->mPercOffsets[i]);
        if (percRaw != NULL) {
            TDrumSet* setp = new (heap, 0) TDrumSet();
            JUT_ASSERT(183, setp != NULL);
            for (int j = 0; j < 0x80; j++) {
                TPmap* pmapRaw = JSUConvertOffsetToPtr<TPmap>(header, percRaw->mPmapOffsets[j]);
                if (pmapRaw != NULL) {
                    TDrumSet::TPerc* drumSetPerc = setp->getPerc(j);
                    drumSetPerc->field_0x0 = pmapRaw->field_0x0;
                    drumSetPerc->field_0x4 = pmapRaw->field_0x4;
                    if (percRaw->mMagic == 'PER2') {
                        drumSetPerc->field_0x8 = percRaw->field_0x288[j] / 127.0f;
                        drumSetPerc->setRelease(percRaw->field_0x308[j]);
                    }
                    drumSetPerc->setEffectCount(2);
                    for (int effectIndex = 0, k = 0; k < 2; k++) {
                        TRand* randRaw = JSUConvertOffsetToPtr<TRand>(header, pmapRaw->mRandOffsets[k]);
                        if (randRaw != NULL) {
                            TInstRand* randp = new (heap, 0) TInstRand();
                            JUT_ASSERT(207, randp != NULL);
                            randp->setTarget(randRaw->field_0x0);
                            randp->field_0x8 = randRaw->field_0x4;
                            randp->field_0xc = randRaw->field_0x8;
                            drumSetPerc->setEffect(effectIndex, randp);
                            effectIndex++;
                        }
                    }
                    drumSetPerc->setVeloRegionCount(pmapRaw->mVeloRegionCount);
                    for (int k = 0; k < pmapRaw->mVeloRegionCount; k++) {
                        TBasicInst::TVeloRegion* instVeloRegion = drumSetPerc->getVeloRegion(k);
                        TVmap* vmapRaw = JSUConvertOffsetToPtr<TVmap>(header, pmapRaw->mVeloRegionOffsets[k]);
                        instVeloRegion->mBaseVel = vmapRaw->field_0x0;
                        instVeloRegion->field_0x04 = vmapRaw->field_0x4 & 0xFFFF;
                        instVeloRegion->field_0x08 = vmapRaw->field_0x8;
                        instVeloRegion->field_0x0c = vmapRaw->field_0xC;
                    }
                }
            }
            bank->setInst(i + 0xE4, setp);
        }
    }
    sUsedHeapSize += freeSize - heap->getFreeSize();
    return bank;
}

/* 802879A0-80287AEC       .text findOscPtr__Q28JASystem9BNKParserFPQ28JASystem10TBasicBankPQ38JASystem9BNKParser7THeaderPQ38JASystem9BNKParser4TOsc */
JASystem::TOscillator::Osc_* JASystem::BNKParser::findOscPtr(JASystem::TBasicBank* bank, JASystem::BNKParser::THeader* header, JASystem::BNKParser::TOsc* oscPtr) {
    u32* instOffsets = header->mInstOffsets - 1;
    for (int i = 0; i < 128; i++) {
        TInst* instRaw = JSUConvertOffsetToPtr<TInst>(header, instOffsets[i + 1]);
        if (instRaw != NULL) {
            for (int j = 0; j < 2; j++) {
                TOsc* oscRaw = JSUConvertOffsetToPtr<TOsc>(header, instRaw->mOscOffsets[j]);
                if (oscRaw == oscPtr) {
                    JASystem::TInst* inst = bank->getInst(i);
                    if (inst != NULL) {
                        TInstParam param;
                        inst->getParam(60, 127, &param);
                        if (j < param.mOscCount) {
                            return param.mOscData[j];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* 80287AEC-80287B00       .text getOscTableEndPtr__Q28JASystem9BNKParserFPs */
s16* JASystem::BNKParser::getOscTableEndPtr(s16* param_1) {
    s16 v1;
    do {
        v1 = *param_1;
        param_1 += 3;
    } while (v1 <= 0xa);
    return param_1;
}
