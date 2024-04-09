#pragma once

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"

// TODO: Find correct pickup speed
namespace Pickup {
enum PickupState : int8_t {
    PU_UP = 127,
    PU_DOWN = -128,
    PU_OFF = 0
};

etl::debounce<20> foward_debounce;
etl::debounce<20> bakward_debounce;

int8_t pickup_state = PU_OFF;

void CustomSetup() { CrcLib::InitializePwmOutput(PICKUP_MOTOR, true); }

void die() { CrcLib::SetPwmOutput(PICKUP_MOTOR, 0); }

void CustomUpdate(bool ticked)
{
    CrcLib::Update();

    foward_debounce.add(CrcLib::ReadDigitalChannel(PICKUP_UP_BUTTON));
    bakward_debounce.add(CrcLib::ReadDigitalChannel(PICKUP_DOWN_BUTTON));

    if (foward_debounce.is_set()) {
        pickup_state = (pickup_state == PU_UP ? PU_OFF : PU_UP); // toggle
    } else if (bakward_debounce.is_set()) {
        pickup_state = (pickup_state == PU_DOWN ? PU_OFF : PU_DOWN); // toggle
    }

    CrcLib::SetPwmOutput(PICKUP_MOTOR, pickup_state);
}
}
