#ifndef D_A_OBJ_STAIR_H
#define D_A_OBJ_STAIR_H

#include "f_op/f_op_actor.h"

class daObj_Stair_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void set_mtx() {}

    void CreateHeap();
    s32 Create();
    void Execute(float(**)[3][4]);
    BOOL Draw();
    BOOL Delete();

public:
    /* Place member variables here */
};

class daobj_stairHIO_c {
public:
    daobj_stairHIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_STAIR_H */
