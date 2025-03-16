//
// Generated by dtk
// Translation Unit: d_bg_w_hf.cpp
//

#include "d/d_bg_w_hf.h"
#include "SSystem/SComponent/c_bg_s.h"
#include "dolphin/types.h"

#define CHECK_MINMAX_1(line, min, max)                                                             \
    JUT_ASSERT(line,                                                                               \
        min->x !=  (1000000000.0f) && min->y !=  (1000000000.0f) && min->z !=  (1000000000.0f) &&  \
        max->x != -(1000000000.0f) && max->y != -(1000000000.0f) && max->z != -(1000000000.0f)     \
    );

#define CHECK_MINMAX_2(line, min, max)                                                             \
    JUT_ASSERT(line,                                                                               \
        (cM3d_IsZero(max->x - min->x) || min->x <= max->x) &&                                      \
        (cM3d_IsZero(max->y - min->y) || min->y <= max->y) &&                                      \
        (cM3d_IsZero(max->z - min->z) || min->z <= max->z)                                         \
    );

/* 800A9A48-800A9AE0       .text Set__6dBgWHfFP6cBgD_tPUsfiiUl */
bool dBgWHf::Set(cBgD_t* bgd, u16* r5, f32 f1, int r6, int r7, u32 flag) {
    m_gridx = r6;
    m_gridz = r7;
    mC8 = r5;
    mC4 = f1;
    if (cBgW::Set(bgd, MOVE_BG_e | NO_CALC_VTX_e | NO_VTX_TBL_e | GLOBAL_e, NULL)) {
        return true;
    }
    SetFlag(flag);
    if (ChkNoCrrPos()) {
        return false;
    }
    SetBackVtx(new Vec[pm_bgd->m_v_num]);
    if (GetBackVtx() == NULL) {
        return true;
    }
    return false;
}

/* 800A9AE0-800A9CD0       .text CalcPlane__6dBgWHfFv */
void dBgWHf::CalcPlane() {
    if (pm_vtx_tbl == NULL)
        return;
    
    cBgD_Tri_t* tri_tbl = pm_bgd->m_t_tbl;
    
    JUT_ASSERT(84, m_gridx * m_gridz * 2 == pm_bgd->m_t_num);
    
    int r30 = 0;
    BOOL isEven = TRUE;
    for (int z = 0; z < m_gridz * 2; z++) {
        cXyz normal;
        if (isEven) {
            for (int x = 0; x < m_gridx; r30++, x++) {
                u16 triIdx = mC8[r30];
                cBgD_Vtx_t* vtx0 = &pm_vtx_tbl[tri_tbl[triIdx].vtx0];
                cBgD_Vtx_t* vtx1 = &pm_vtx_tbl[tri_tbl[triIdx].vtx1];
                cBgD_Vtx_t* vtx2 = &pm_vtx_tbl[tri_tbl[triIdx].vtx2];
                normal.x = vtx1->y - vtx0->y;
                normal.y = mC4;
                normal.z = vtx1->y - vtx2->y;
                pm_tri[triIdx].m_plane.SetupNP0(normal, *vtx0);
            }
            isEven = FALSE;
        } else {
            for (int x = 0; x < m_gridx; r30++, x++) {
                u16 triIdx = mC8[r30];
                Vec* vtx0 = &pm_vtx_tbl[tri_tbl[triIdx].vtx0];
                Vec* vtx1 = &pm_vtx_tbl[tri_tbl[triIdx].vtx1];
                Vec* vtx2 = &pm_vtx_tbl[tri_tbl[triIdx].vtx2];
                normal.x = vtx0->y - vtx1->y;
                normal.y = mC4;
                normal.z = vtx2->y - vtx1->y;
                pm_tri[triIdx].m_plane.SetupNP0(normal, *vtx0);
            }
            isEven = TRUE;
        }
    }
}

/* 800A9CD0-800A9E70       .text ClassifyPlane__6dBgWHfFv */
void dBgWHf::ClassifyPlane() {
    if (pm_vtx_tbl == NULL) {
        return;
    }
    
    for (int b = 0; b < pm_bgd->m_b_num; b++) {
#if VERSION != VERSION_JPN
        JUT_ASSERT(140, 0 <= b && b < pm_bgd->m_b_num);
#endif
        
        int r6 = pm_bgd->m_b_tbl[b].startTri;
        int r29;
        if (b != pm_bgd->m_b_num - 1) {
            r29 = pm_bgd->m_b_tbl[b+1].startTri - 1;
        } else {
            r29 = pm_bgd->m_t_num - 1;
        }
        
        pm_blk[b].roof = -1;
        pm_blk[b].wall = -1;
        pm_blk[b].ground = -1;
        int sp8 = (u16)-1;
        
        for (int t = r6; t <= r29; t++) {
#if VERSION != VERSION_JPN
            JUT_ASSERT(159, 0 <= t && t < pm_bgd->m_t_num);
#endif
            BlckConnect(&pm_blk[b].ground, &sp8, t);
        }
    }
}

/* 800A9E70-800A9EDC       .text MoveHf__6dBgWHfFv */
void dBgWHf::MoveHf() {
    mFlag |= 0x01;
    if (ChkLock()) {
        return;
    }
    CalcPlane();
    ClassifyPlane();
    MakeNodeTreeHf();
}

/* 800A9EDC-800A9FA0       .text MakeBlckMinMaxHf__6dBgWHfFiPfPf */
void dBgWHf::MakeBlckMinMaxHf(int v_index, f32* r30, f32* r31) {
#if VERSION != VERSION_JPN
    JUT_ASSERT(198, 0 <= v_index && v_index < pm_bgd->m_v_num);
#endif
    Vec* vtx = &pm_vtx_tbl[v_index];
    if (*r30 > vtx->y) {
        *r30 = vtx->y;
    }
    if (*r31 < vtx->y) {
        *r31 = vtx->y;
    }
}

/* 800A9FA0-800AA164       .text MakeBlckBndHf__6dBgWHfFiPfPf */
void dBgWHf::MakeBlckBndHf(int blck_id, f32* r28, f32* r29) {
#if VERSION != VERSION_JPN
    JUT_ASSERT(221, blck_id >= 0 && blck_id < pm_bgd->m_b_num);
#endif
    
    int r7 = pm_bgd->m_b_tbl[blck_id].startTri;
    int r31;
    if (blck_id != pm_bgd->m_b_num - 1) {
        r31 = pm_bgd->m_b_tbl[blck_id+1].startTri - 1;
    } else {
        r31 = pm_bgd->m_t_num - 1;
    }
    
    *r28 = C_BG_MAX_HEIGHT;
    *r29 = C_BG_MIN_HEIGHT;
    
    for (int t = r7; t <= r31; t++) {
#if VERSION != VERSION_JPN
        JUT_ASSERT(238, 0 <= t && t < pm_bgd->m_t_num);
#endif
        MakeBlckMinMaxHf(pm_bgd->m_t_tbl[t].vtx0, r28, r29);
        MakeBlckMinMaxHf(pm_bgd->m_t_tbl[t].vtx1, r28, r29);
        MakeBlckMinMaxHf(pm_bgd->m_t_tbl[t].vtx2, r28, r29);
    }
    
    *r28 -= 1.0f;
    *r29 += 1.0f;
}

/* 800AA164-800AA8AC       .text MakeNodeTreeRpHf__6dBgWHfFi */
void dBgWHf::MakeNodeTreeRpHf(int node_index) {
#if VERSION != VERSION_JPN
    JUT_ASSERT(258, 0 <= node_index && node_index < pm_bgd->m_tree_num);
#endif
    
    cBgD_Tree_t* r30 = &pm_bgd->m_tree_tbl[node_index];
    if (r30->mFlag & 0x01) {
        if (r30->mChild[0] != (u16)-1) {
            MakeBlckBndHf(r30->mChild[0], &m_nt_tbl[node_index].GetMinP()->y, &m_nt_tbl[node_index].GetMaxP()->y);
        }
    } else {
        m_nt_tbl[node_index].ClearForMinMaxY();
        if (r30->mChild[0] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[0]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[0]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[0]].GetMaxP()->y);
        }
        if (r30->mChild[1] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[1]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[1]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[1]].GetMaxP()->y);
        }
        if (r30->mChild[2] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[2]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[2]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[2]].GetMaxP()->y);
        }
        if (r30->mChild[3] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[3]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[3]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[3]].GetMaxP()->y);
        }
        if (r30->mChild[4] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[4]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[4]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[4]].GetMaxP()->y);
        }
        if (r30->mChild[5] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[5]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[5]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[5]].GetMaxP()->y);
        }
        if (r30->mChild[6] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[6]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[6]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[6]].GetMaxP()->y);
        }
        if (r30->mChild[7] != (u16)-1) {
            MakeNodeTreeRpHf(r30->mChild[7]);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[7]].GetMinP()->y);
            m_nt_tbl[node_index].SetMinMaxY(m_nt_tbl[r30->mChild[7]].GetMaxP()->y);
        }
    }
    
#if VERSION != VERSION_JPN
    CHECK_MINMAX_1(353, m_nt_tbl[node_index].GetMinP(), m_nt_tbl[node_index].GetMaxP());
    CHECK_MINMAX_2(365, m_nt_tbl[node_index].GetMinP(), m_nt_tbl[node_index].GetMaxP());
#endif
}

/* 800AA8AC-800AAA70       .text MakeNodeTreeGrpRpHf__6dBgWHfFi */
void dBgWHf::MakeNodeTreeGrpRpHf(int g) {
#if VERSION != VERSION_JPN
    JUT_ASSERT(377, 0 <= g && g < pm_bgd->m_g_num);
#endif
    
    if (pm_bgd->m_g_tbl[g].m_tree_idx != (u16)-1) {
        MakeNodeTreeRpHf(pm_bgd->m_g_tbl[g].m_tree_idx);
        pm_grp[g].aab.SetMinY(m_nt_tbl[pm_bgd->m_g_tbl[g].m_tree_idx].GetMinP()->y);
        pm_grp[g].aab.SetMaxY(m_nt_tbl[pm_bgd->m_g_tbl[g].m_tree_idx].GetMaxP()->y);
    }
    
    int grpIdx = pm_bgd->m_g_tbl[g].m_first_child;
    while (true) {
        if (grpIdx == (u16)-1)
            break;
        MakeNodeTreeGrpRpHf(grpIdx);
        pm_grp[g].aab.SetMinY(pm_grp[grpIdx].aab.GetMinP()->y);
        pm_grp[g].aab.SetMaxY(pm_grp[grpIdx].aab.GetMaxP()->y);
        grpIdx = pm_bgd->m_g_tbl[grpIdx].m_next_sibling;
    }
}

/* 800AAA70-800AAB78       .text MakeNodeTreeHf__6dBgWHfFv */
void dBgWHf::MakeNodeTreeHf() {
    if (pm_vtx_tbl == NULL) {
        for (int g = 0; g < pm_bgd->m_g_num; g++) {
            if (pm_bgd->m_g_tbl[g].m_parent == (u16)-1) {
                m_rootGrpIdx = g;
                break;
            }
        }
        return;
    }
    
    for (int g = 0; g < pm_bgd->m_g_num; g++) {
        pm_grp[g].aab.ClearForMinMaxY();
    }
    
    if (m_rootGrpIdx == (u16)-1) {
        for (int g = 0; g < pm_bgd->m_g_num; g++) {
            if (pm_bgd->m_g_tbl[g].m_parent == (u16)-1) {
                m_rootGrpIdx = g;
                MakeNodeTreeGrpRpHf(g);
                break;
            }
        }
    } else {
        MakeNodeTreeGrpRpHf(m_rootGrpIdx);
    }
}
