#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"

// TODO: Find optimal values for flywheel
enum FlywheelState : int8_t {
    FW_OFF = 0,
    FW_CLOSE = 90,
    FW_FAR = 120
};

etl::debounce<20> close_button_debounce;
etl::debounce<20> far_button_debounce;
CrcLib::Timer fw_timer;

int8_t flywheel_state = FW_OFF;

void flywheel_setup()
{
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_TOP, false);
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_BOT, true);

    fw_timer.Start(TICK_TIME);
}

void flywheel_die()
{
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_TOP, 0);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_BOT, 0);
}

void flywheel_update()
{
    if (fw_timer.IsFinished()) {
        close_button_debounce.add(CrcLib::ReadDigitalChannel(FLYWHEEL_CLOSE_BUTTON));
        far_button_debounce.add(CrcLib::ReadDigitalChannel(FLYWHEEL_FAR_BUTTON));

        if (close_button_debounce.is_set()) {
            flywheel_state = (flywheel_state == FW_CLOSE ? FW_OFF : FW_CLOSE); // toggle
        } else if (far_button_debounce.is_set()) {
            flywheel_state = (flywheel_state == FW_FAR ? FW_OFF : FW_FAR); // toggle
        }

        fw_timer.Next();
    }

    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_TOP, flywheel_state);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_BOT, flywheel_state);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
