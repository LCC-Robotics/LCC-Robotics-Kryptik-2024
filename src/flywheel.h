#pragma once

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"
#include "helpers.h"

namespace Flywheel {
// TODO: Find optimal values for flywheel
// TODO: Implement feeding system
enum FlywheelState : int8_t {
    FW_OFF = 0,
    FW_CLOSE = 90,
    FW_FAR = 120
};

etl::debounce<20> close_button_debounce;
etl::debounce<20> far_button_debounce;

void CustomSetup()
{
    CrcLib::InitializePwmOutput(FW_MOTOR_TOP, false);
    CrcLib::InitializePwmOutput(FW_MOTOR_BOT, true);

    CrcLib::SetDigitalPinMode(FW_FEEDING_MOTOR, OUTPUT);
}

void die()
{
    CrcLib::Update();

    CrcLib::SetPwmOutput(FW_MOTOR_TOP, 0);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, 0);
}

void CustomUpdate(bool ticked)
{
    CrcLib::Update();

    int8_t flywheel_state = helpers::convert_analog(CrcLib::ReadAnalogChannel(FW_MANUAL_CHANNEL));

    close_button_debounce.add(CrcLib::ReadDigitalChannel(FW_CLOSE_BUTTON));
    far_button_debounce.add(CrcLib::ReadDigitalChannel(FW_FAR_BUTTON));

    if (close_button_debounce.has_changed() && close_button_debounce.is_set()) {
        flywheel_state = (flywheel_state == FW_CLOSE ? FW_OFF : FW_CLOSE); // toggle
    } else if (far_button_debounce.has_changed() && far_button_debounce.is_set()) {
        flywheel_state = (flywheel_state == FW_FAR ? FW_OFF : FW_FAR); // toggle
    }

    CrcLib::SetPwmOutput(FW_MOTOR_TOP, flywheel_state);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, flywheel_state);

    CrcLib::SetDigitalOutput(FW_FEEDING_MOTOR, HIGH);
}
}
