#pragma once

#include <CrcLib.h>

#include "const.h"

// TODO: Find correct pickup speed
namespace Pickup {
enum PickupState : int8_t {
    PU_UP = 127,
    PU_DOWN = -128,
    PU_OFF = 0
};

void setup() { CrcLib::InitializePwmOutput(PICKUP_MOTOR, false); }

void die() { CrcLib::SetPwmOutput(PICKUP_MOTOR, 0); }

void update(bool ticked)
{
    int8_t pickup_state = PU_OFF;

    if (CrcLib::ReadDigitalChannel(PICKUP_UP_BUTTON)) {
        pickup_state = PU_UP;
    } else if (CrcLib::ReadDigitalChannel(PICKUP_DOWN_BUTTON)) {
        pickup_state = PU_DOWN;
    }

    CrcLib::SetPwmOutput(PICKUP_MOTOR, pickup_state);
}
}

