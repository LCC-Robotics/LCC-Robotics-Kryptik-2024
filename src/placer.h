#pragma once

#include <CrcLib.h>

#include "const.h"

namespace Placer {
enum PlacerState : int8_t {
    PLA_RETRACT = -110,
    PLA_DEPLOY = 20, // to
};

enum GuideState : int8_t {
    G_OFF = 0,
    G_DEPLOY = 115,
    G_RETRACT = -115,
};

etl::debounce<20> placer_debounce;

int8_t placer_val = PLA_RETRACT;

void CustomSetup()
{
    CrcLib::InitializePwmOutput(MULTI_PLACER_MOTOR, 500, 2500, false);
    CrcLib::InitializePwmOutput(MULTI_GUIDE_MOTOR, false);
}

void die()
{
    CrcLib::Update();

    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, 0);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, 0);
}

void CustomUpdate()
{
    CrcLib::Update();

    placer_debounce.add(CrcLib::ReadDigitalChannel(MULTI_BUTTON));

    if (placer_debounce.has_changed() && placer_debounce.is_set()) {
        placer_val = (placer_val == PLA_DEPLOY) ? PLA_RETRACT : PLA_DEPLOY;
    }

    // =======

    int8_t guide_val = G_OFF;

    if (CrcLib::ReadDigitalChannel(GUIDE_DEPLOY_BUTTON)) {
        guide_val = G_DEPLOY;
    } else if (CrcLib::ReadDigitalChannel(GUIDE_RETRACT_BUTTON)) {
        guide_val = G_RETRACT;
    }

    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, placer_val);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, guide_val);
}
}
