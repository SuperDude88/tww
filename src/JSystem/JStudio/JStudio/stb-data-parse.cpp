//
// Generated by dtk
// Translation Unit: stb-data-parse.cpp
//

#include "JSystem/JStudio/JStudio/stb-data-parse.h"
#include "dolphin/types.h"

namespace JStudio {
namespace stb {
namespace data {

/* 80275A64-80275AB4       .text getData__Q47JStudio3stb4data16TParse_TSequenceCFPQ57JStudio3stb4data16TParse_TSequence5TData */
void TParse_TSequence::getData(TParse_TSequence::TData* pData) const {
    pData->content = NULL;
    pData->next = NULL;
    u32 head = get_head();
    u8 type = head >> 24;
    u32 param = head & 0xffffff;
    pData->type = type;
    pData->param = param;
    if (type != 0) {
        const void* next = (const void*)((int)getRaw() + 4);
        if (type <= 0x7f) {
            pData->next = next;
        } else {
            pData->content = next;
            pData->next = (const void*)((int)next + param);
        }
    }
}

/* 80275AB4-80275B2C       .text getData__Q47JStudio3stb4data17TParse_TParagraphCFPQ57JStudio3stb4data17TParse_TParagraph5TData */
void TParse_TParagraph::getData(TParse_TParagraph::TData* pData) const {
    const void* data = getRaw();
    u32 result;
    const void* next = parseVariableUInt_16_32_following(data, &result, &pData->type, NULL);
    pData->param = result;
    if (result == 0) {
        pData->content = NULL;
        pData->next = next;
    } else {
        pData->content = next;
        pData->next = (const void*)((int)next + align_roundUp(result, 4));
    }
}

/* 80275B2C-80275BAC       .text getData__Q47JStudio3stb4data22TParse_TParagraph_dataCFPQ57JStudio3stb4data22TParse_TParagraph_data5TData */
void TParse_TParagraph_data::getData(TParse_TParagraph_data::TData* pData) const {
    u8* set2;

	int dSize = pData->dataSize = 0;
	pData->_8                  = 0;
	pData->fileCount            = NULL;
	pData->_10                  = NULL;
	u8* filedata = (u8*)getRaw();
	if (filedata == NULL)
		return;
	u8 set       = *filedata;
	pData->status = set & ~0x8;
	if (!set)
		return;
    int is8;
	int set3 = 1;
	is8 = set & 8;
    // Probably fake match
	if (set2 = (filedata + 1), is8) {
		set3 = *set2++;
	}
	pData->_8       = set3;
	pData->fileCount = set2;

	if (!(set & 7))
		return;
	dSize          = (gauDataSize_TEParagraph_data)[set &= 7];
	pData->dataSize = dSize;
	pData->_10      = (u8*)set2 + (dSize * set3);
}

}  // namespace data
}  // namespace stb
}  // namespace JStudio
