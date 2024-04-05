#pragma once

#include <CrcLib.h>

#include "const.h"

namespace Placer {
enum PlacerState : int8_t {
    PLA_OFF = 0,
    PLA_RETRACT = -90,
    PLA_DEPLOY = 90,
};

void setup()
{
    CrcLib::InitializePwmOutput(MULTI_PLACER_MOTOR, false);
    CrcLib::InitializePwmOutput(MULTI_GUIDE_MOTOR, false);
}

void die()
{
    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, 0);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, 0);
}

void update(bool ticked)
{
    int8_t placer_val = PLA_OFF;

    if (CrcLib::ReadDigitalChannel(MULTI_DEPLOY_BUTTON)) {
        placer_val = PLA_DEPLOY;
    } else if (CrcLib::ReadDigitalChannel(MULTI_RETRACT_BUTTON)) {
        placer_val = PLA_RETRACT;
    }

    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, placer_val);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, placer_val);
}
}

