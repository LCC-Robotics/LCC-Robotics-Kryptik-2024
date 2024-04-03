#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"
#include "helpers.h"

// TODO: Find optimal values for flywheel
// TODO: Implement feeding system
enum FlywheelState : int8_t {
    FW_OFF = 0,
    FW_CLOSE = 90,
    FW_FAR = 120
};

etl::debounce<20> close_button_debounce;
etl::debounce<20> far_button_debounce;
CrcLib::Timer fw_timer;

void flywheel_setup()
{
    CrcLib::InitializePwmOutput(FW_MOTOR_TOP, false);
    CrcLib::InitializePwmOutput(FW_MOTOR_BOT, true);

    fw_timer.Start(TICK_TIME);
}

void flywheel_die()
{
    CrcLib::SetPwmOutput(FW_MOTOR_TOP, 0);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, 0);
}

void flywheel_update()
{
    int8_t flywheel_state = helpers::convert_analog(CrcLib::ReadAnalogChannel(FW_MANUAL_CHANNEL));

    if (CrcLib::ReadDigitalChannel(FW_FAR_BUTTON)) {
        flywheel_state = FW_FAR;
    } else if (CrcLib::ReadDigitalChannel(FW_CLOSE_BUTTON)) {
        flywheel_state = FW_CLOSE;
    }

    CrcLib::SetPwmOutput(FW_MOTOR_TOP, flywheel_state);
    CrcLib::SetPwmOutput(FW_MOTOR_BOT, flywheel_state);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
