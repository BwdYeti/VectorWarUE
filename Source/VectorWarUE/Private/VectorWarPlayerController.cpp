// Copyright 2020 BwdYeti.


#include "VectorWarPlayerController.h"
#include "VectorWar/vectorwar.h"

int32 AVectorWarPlayerController::GetVectorWarInput()
{
    static const struct {
        FKey     key;
        int32    input;
    } inputtable[] = {
       { EKeys::Up,       INPUT_THRUST },
       { EKeys::Down,     INPUT_BREAK },
       { EKeys::Left,     INPUT_ROTATE_LEFT },
       { EKeys::Right,    INPUT_ROTATE_RIGHT },
       { EKeys::D,        INPUT_FIRE },
       { EKeys::S,        INPUT_BOMB },
    };
    int32 i, inputs = 0;

    for (i = 0; i < sizeof(inputtable) / sizeof(inputtable[0]); i++) {
        if (IsInputKeyDown(inputtable[i].key)) {
            inputs |= inputtable[i].input;
        }
    }

    return inputs;
}

