//
// Generated by dtk
// Translation Unit: c_m3d_g_sph.cpp
//

#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_m3d.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "float.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(fpclassify(x) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)

/* 8025238C-80252624       .text SetC__8cM3dGSphFRC4cXyz */
void cM3dGSph::SetC(const cXyz& p) {
    CHECK_FLOAT_CLASS(18, p.x);
    CHECK_FLOAT_CLASS(19, p.y);
    CHECK_FLOAT_CLASS(20, p.z);
    CHECK_VEC3_RANGE(23, p);
    mCenter = p;
}

/* 80252624-80252750       .text SetR__8cM3dGSphFf */
void cM3dGSph::SetR(float r) {
    CHECK_FLOAT_CLASS(32, r);
    CHECK_FLOAT_RANGE(33, r);
    mRadius = r;
}

/* 80252750-8025277C       .text cross__8cM3dGSphCFPC8cM3dGSphP4cXyz */
bool cM3dGSph::cross(const cM3dGSph* pOther, cXyz* pOut) const {
    return cM3d_Cross_SphSph(pOther, this, pOut);
}

/* 8025277C-802527AC       .text cross__8cM3dGSphCFPC8cM3dGCylP4cXyz */
bool cM3dGSph::cross(const cM3dGCyl* pOther, cXyz* pOut) const {
    f32 f;
    return cM3d_Cross_CylSph(pOther, this, pOut, &f);
}

/* 802527AC-802527D4       .text cross__8cM3dGSphCFPC8cM3dGSphPf */
bool cM3dGSph::cross(const cM3dGSph* pOther, f32* pOut) const {
    f32 f;
    return cM3d_Cross_SphSph(this, pOther, &f, pOut);
}
