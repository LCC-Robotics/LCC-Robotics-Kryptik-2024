#pragma once

#include <CrcLib.h>
#include <Servo.h>
#include <etl/debounce.h>

#include "const.h"

namespace Flywheel {
// TODO: Find optimal values for flywheel
// TODO: Implement feeding system
enum FlywheelState : int8_t {
    FW_OFF = 0,
    FW_CLOSE = 90,
    FW_FAR = 120
};

Servo flywheel_feed; 

etl::debounce<20> close_button_debounce;
etl::debounce<20> far_button_debounce;

void CustomSetup()
{
    CrcLib::InitializePwmOutput(FW_MOTOR_TOP, false);
    CrcLib::InitializePwmOutput(FW_MOTOR_BOT, false);

    flywheel_feed.attach(FW_FEEDING_MOTOR);
}

void die()
{
    CrcLib::Update();

    CrcLib::SetPwmOutput(FW_MOTOR_TOP, 0);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, 0);
}

void CustomUpdate()
{
    CrcLib::Update();

    int8_t flywheel_state = FW_OFF;

    if (CrcLib::ReadDigitalChannel(FW_FAR_BUTTON)){
        flywheel_state = FW_FAR;
    }
    else if (CrcLib::ReadDigitalChannel(FW_CLOSE_BUTTON)){
        flywheel_state = FW_CLOSE;
    }

    CrcLib::SetPwmOutput(FW_MOTOR_TOP, flywheel_state);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, flywheel_state);

    flywheel_feed.write(flywheel_state);
}
}
