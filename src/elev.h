#pragma once

#include <CrcLib.h>

#include "const.h"
#include "helpers.h"

namespace Elevator {

void CustomSetup()
{
    CrcLib::InitializePwmOutput(ELEV_MOTOR, false);
}

void die() { CrcLib::SetPwmOutput(ELEV_MOTOR, 0); }

void CustomUpdate()
{
    CrcLib::Update();

    int8_t elev = helpers::convert_analog(CrcLib::ReadAnalogChannel(ELEV_UP_CHANNEL));

    if (!elev) {
        elev = -helpers::convert_analog(CrcLib::ReadAnalogChannel(ELEV_DOWN_CHANNEL));
    }
    if (!elev) {
        elev = 6;
    }

    CrcLib::SetPwmOutput(ELEV_MOTOR, elev); // write value to motor
}
}
