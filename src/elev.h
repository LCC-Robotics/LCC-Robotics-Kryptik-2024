#pragma once

#include <CrcLib.h>

#include "const.h"

namespace Elevator {

enum ElevatorState : int8_t {
    ELEV_UP = 100,
    ELEV_DOWN = -100,
    ELEV_OFF = 0,
};

void CustomSetup()
{   
    CrcLib::InitializePwmOutput(ELEV_MOTOR, false);
}


void die() { CrcLib::SetPwmOutput(ELEV_MOTOR, 0); }


void CustomUpdate(bool ticked)
{
    CrcLib::Update();
    
    if (ticked) { // update debounced buttons each tick
        int8_t elev_val = ELEV_OFF;

        if (CrcLib::ReadDigitalChannel(ELEV_UP_BUTTON)){
            elev_val = ELEV_UP;
        }
        else if (CrcLib::ReadDigitalChannel(ELEV_DOWN_BUTTON)){
            elev_val = ELEV_DOWN;
        }

    CrcLib::SetPwmOutput(ELEV_MOTOR, elev_val); // write value to motor
    }
}
}
