#ifndef GXMISC_H
#define GXMISC_H

#include "dolphin/gx/GXEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXSetMisc(GXMiscToken token, u32 val);
void GXFlush(void);
void __GXAbort(void);
void GXAbortFrame(void);
void GXSetDrawDone(void);
void GXDrawDone(void);
void GXPixModeSync(void);
void GXPokeAlphaMode(GXCompare comp, u8 threshold);
void GXPokeAlphaRead(GXAlphaReadMode mode);
void GXPokeAlphaUpdate(GXBool enable_update);
void GXPokeBlendMode(GXBlendMode mode, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXPokeColorUpdate(GXBool enable_update);
void GXPokeDstAlpha(GXBool enable, u8 alpha);
void GXPokeDither(GXBool enable);
void GXPokeZMode(GXBool enable_compare, GXCompare comp, GXBool update_enable);
void GXPeekARGB(u16 x, u16 y, u32* color);
void GXPeekZ(u16 x, u16 y, u32* z);

typedef void (*GXDrawSyncCallback)(u16 token);
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback);
void GXSetDrawSync(GXBool enable);

typedef void (*GXDrawDoneCallback)(void);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback);
void __GXPEInit(void);

#ifdef __cplusplus
};
#endif

#endif /* GXMISC_H */
