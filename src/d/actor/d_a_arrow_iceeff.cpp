//
// Generated by dtk
// Translation Unit: d_a_arrow_iceeff.cpp
//

#include "d/actor/d_a_arrow_iceeff.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_arrow.h"

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daArrow_Iceeff_c*>(i_this)->CreateHeap();
}

/* 0000010C-00000324       .text CreateHeap__16daArrow_Iceeff_cFv */
BOOL daArrow_Iceeff_c::CreateHeap() {
    if(field_0xA38 == 0) {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_GICER00));
        JUT_ASSERT(87, modelData != 0);
        for(int i = 0; i < 30; i++) {
            field_0x298[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
            if(field_0x298[i] == 0) {
                return false;
            }
        }
    }
    else {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_GICER01));
        JUT_ASSERT(98, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if(mpModel == 0) {
            return false;
        }
        
        J3DAnmTransform* bck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Link", LINK_BCK_GICER01));
        JUT_ASSERT(107, bck != 0);
        if(!mBck.init(modelData, bck, true, 0, 1.0f, 0, -1, false)) {
            return false;
        }
    }

    return true;
}

/* 00000324-000005E4       .text CreateInit__16daArrow_Iceeff_cFv */
void daArrow_Iceeff_c::CreateInit() {
    if(field_0xA38 == 0) {
        for(int i = 0; i < 30; i++) {
            fopAcM_SetMtx(this, field_0x298[i]->getBaseTRMtx());

            field_0x8B4[i].setall(cM_rndF(4.5f) + 6.2999997f);

            f32 temp = 180.0f * i / 30.0f;
            s16 angle = cM_rndF(65536.0f);
            mDoMtx_stack_c::ZrotS(cM_rndF(65536.0f));
            mDoMtx_stack_c::XrotM(cM_rndF(65536.0f));
            mDoMtx_stack_c::YrotM(cM_rndF(65536.0f));
            mDoMtx_stack_c::transM(temp * cM_ssin(angle), temp * cM_scos(angle), 0.0f);
            mDoMtx_stack_c::ZrotM(current.angle.z);
            mDoMtx_stack_c::XrotM(current.angle.x);
            mDoMtx_stack_c::YrotM(current.angle.y);
            cMtx_copy(mDoMtx_stack_c::get(), field_0x314[i]);
        }
    }
    else {
        current.angle.y = cM_rndF(65536.0f);
    }

    fopAcM_setCullSizeBox(this, -100.0f, -100.0f, -100.0f, 100.0f, 100.0f, 100.0f);
    mCullSizeFar = 1.0f;
    set_mtx();
    field_0xA30 = 0;
    field_0xA34 = 0.0f;
    if(field_0xA38 == 0) {
        field_0xA1C = daPy_getPlayerLinkActorClass()->mpGicer00Btk;
    }
    else {
        field_0xA1C = daPy_getPlayerLinkActorClass()->mpGicer01Btk;
    }

    field_0xA1C->setFrame(field_0xA34);
    field_0xA3C = 1;
}

/* 000005E4-0000073C       .text set_mtx__16daArrow_Iceeff_cFv */
void daArrow_Iceeff_c::set_mtx() {
    if(field_0xA38 == 0) {
        for(int i = 0; i < 30; i++) {
            field_0x298[i]->setBaseScale(field_0x8B4[i]);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::ZXYrotM(current.angle.x, current.angle.y, 0);
            mDoMtx_stack_c::concat(field_0x314[i]);
            field_0x298[i]->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
    else {
        mScale.setall(1.0f);
        mpModel->setBaseScale(mScale);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

s32 daArrow_Iceeff_c::_create() {
    fopAcM_SetupActor(this, daArrow_Iceeff_c);

    void* arrow = fopAcM_SearchByID(mParentPcId);
    if(arrow == 0) {
        return cPhs_ERROR_e;
    }
    else {
        if(fopAcM_GetParam(arrow) == 4) {
            field_0xA38 = 1;
        }
        else {
            field_0xA38 = 0;
        }

        if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xD5E0)) {
            return cPhs_ERROR_e;
        }
        
        CreateInit();
        return cPhs_COMPLEATE_e;
    }
}

/* 0000073C-00000854       .text daArrow_Iceeff_Create__FPv */
static s32 daArrow_Iceeff_Create(void* i_this) {
    return static_cast<daArrow_Iceeff_c*>(i_this)->_create();
}

bool daArrow_Iceeff_c::_delete() {
    return true;
}

/* 00000938-00000940       .text daArrow_Iceeff_Delete__FPv */
static BOOL daArrow_Iceeff_Delete(void* i_this) {
    return static_cast<daArrow_Iceeff_c*>(i_this)->_delete();
}

bool daArrow_Iceeff_c::_draw() {
    s32 temp = field_0xA30;
    if(30 < temp) {
        temp = 30;
    }
    
    field_0xA1C->setFrame(field_0xA34);
    dComIfGd_setListP1();

    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &mTevStr);
    if(field_0xA38 == 0) {
        for(int i = 0; i < temp; i++) {
            g_env_light.setLightTevColorType(field_0x298[i], &mTevStr);

            if(field_0xA3C == 1) {
                mDoExt_modelUpdateDL(field_0x298[i]);
            }
        }
    }
    else {
        g_env_light.setLightTevColorType(mpModel, &mTevStr);
        J3DModelData* mdl_data = mpModel->getModelData();
        mBck.entry(mdl_data, mBck.getFrame());
        if(field_0xA3C == 1) {
            mDoExt_modelUpdateDL(mpModel);
        }

        mBck.remove(mpModel->getModelData());
    }

    dComIfGd_setList();

    return true;
}

/* 00000940-00000A98       .text daArrow_Iceeff_Draw__FPv */
static BOOL daArrow_Iceeff_Draw(void* i_this) {
    return static_cast<daArrow_Iceeff_c*>(i_this)->_draw();
}

/* 00000A98-00000ABC       .text daArrow_Iceeff_Execute__FPv */
static BOOL daArrow_Iceeff_Execute(void* i_this) {
    return static_cast<daArrow_Iceeff_c*>(i_this)->_execute();
}

/* 00000ABC-00001050       .text _execute__16daArrow_Iceeff_cFv */
bool daArrow_Iceeff_c::_execute() {
    static cXyz ripple_scale(1.0f, 1.0f, 1.0f);

    daArrow_c* arrow = static_cast<daArrow_c*>(fopAcM_SearchByID(mParentPcId));
    if(field_0xA38 == 0) {
        if(arrow == 0) {
            dComIfGp_particle_setP1(0x55, &current.pos, &current.angle, 0);
            fopAcM_delete(this);

            return true;
        }

        current.pos = arrow->field_0x6a8;
        current.angle = arrow->shape_angle;
        if(field_0xA30 == 0) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_MINI_ICE, 0);
        }
        
        if(field_0xA30 >= 30) {
            field_0xA34 += 1.0f;
            if(field_0xA34 >= field_0xA1C->getFrameMax()) {
                field_0xA34 = field_0xA1C->getFrameMax();
            }
        }

        if(field_0xA30 < 0x3C) {
            field_0xA30++;
        }
        else {
            dComIfGp_particle_setP1(0x55, &current.pos, &current.angle, 0);
            fopAcM_seStartCurrent(this, JA_SE_OBJ_MINI_ICE_BREAK, 0);
            fopAcM_delete(arrow);
            fopAcM_delete(this);
        }
    }
    else {
        mBck.play();
        f32 waterY;
        fopAcM_getWaterY(&current.pos, &waterY);
        current.pos.y = waterY;
        if(field_0xA30 == 0) {
            csXyz angle;
            angle.set(-0x4000, 0, 0);

            JPABaseEmitter* ptcl = dComIfGp_particle_setP1(0x29E, &current.pos, &angle, 0);
            if(ptcl) {
                JGeometry::TVec3<f32> scale(0.5f, 0.5f, 0.5f);
                ptcl->setGlobalScale(scale);
                ptcl->setRate(50.0f);
                ptcl->setGlobalAlpha(0x80);
            }

            fopAcM_seStartCurrent(this, JA_SE_OBJ_MINI_ICE, 0);
        }

        field_0xA34 += 1.0f;
        if(field_0xA34 >= field_0xA1C->getFrameMax()) {
            field_0xA34 = field_0xA1C->getFrameMax();
        }

        if(field_0xA30 < 300) {
            field_0xA30++;
        }
        else {
            fopAcM_delete(this);
        }

        if(field_0xA30 == 0x23) {
            JPABaseEmitter* ptcl = dComIfGp_particle_setSingleRipple(0x3D, &current.pos, 0, &ripple_scale);
            if(ptcl) {
                JGeometry::TVec3<f32> scale(0.67f, 0.67f, 1.0f);
                ptcl->setGlobalParticleScale(scale);
            }
        }
        else if(field_0xA30 == 0x28) {
            JPABaseEmitter* ptcl = dComIfGp_particle_setP1(0x55, &current.pos, 0, 0);
            if(ptcl) {
                ptcl->setAwayFromCenterSpeed(25.0f);
                ptcl->setAwayFromAxisSpeed(5.0f);
                ptcl->setDirectionalSpeed(5.0f);
                JGeometry::TVec3<f32> scale1(0.5f, 1.0f, 0.5f);
                ptcl->setEmitterScale(scale1);
                JGeometry::TVec3<f32> scale2(0.33f, 0.33f, 1.0f);
                ptcl->setGlobalParticleScale(scale2);
            }
            
            dComIfGp_particle_setSingleRipple(0x3F, &current.pos, 0, &ripple_scale);
            fopAcM_seStartCurrent(this, JA_SE_OBJ_MINI_ICE_BREAK, 0);

            field_0xA3C = 0;
        }
    }

    set_mtx();

    return true;
}

/* 00001050-00001058       .text daArrow_Iceeff_IsDelete__FPv */
static BOOL daArrow_Iceeff_IsDelete(void*) {
    return true;
}

static actor_method_class daArrow_IceeffMethodTable = {
    (process_method_func)daArrow_Iceeff_Create,
    (process_method_func)daArrow_Iceeff_Delete,
    (process_method_func)daArrow_Iceeff_Execute,
    (process_method_func)daArrow_Iceeff_IsDelete,
    (process_method_func)daArrow_Iceeff_Draw,
};

actor_process_profile_definition g_profile_ARROW_ICEEFF = {
    fpcLy_CURRENT_e,
    9,
    fpcPi_CURRENT_e,
    PROC_ARROW_ICEEFF,
    &g_fpcLf_Method.mBase,
    sizeof(daArrow_Iceeff_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01C0,
    &daArrow_IceeffMethodTable,
    fopAcStts_UNK40000_e | fopAcStts_UNK4000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
