//
// Generated by dtk
// Translation Unit: J3DUMotion.cpp
//

#include "JSystem/J3DU/J3DUMotion.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "dolphin/types.h"

// this puts the correct functions here when they are weak
// however, the data from J3DMtxCalcBasic::init starts appearing in other TUs
static void dummy(J3DMtxCalcBasic* calc1, J3DMtxCalcSoftimage* calc2) {
    Vec vec;
    Mtx mtx;
    calc1->init(vec, mtx);
    calc2->init(vec, mtx);
    delete calc2;
}
