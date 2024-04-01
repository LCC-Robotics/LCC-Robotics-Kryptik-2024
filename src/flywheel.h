#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"
#include "helpers.h"

enum FlywheelState: int8_t {
    OFF = 0,
    CLOSE = 90,
    FAR = 120
};

etl::debounce<20> close_button_debounce; 
etl::debounce<20> far_button_debounce; 
CrcLib::Timer timer;

int8_t flywheel_state = OFF;


void flywheel_setup()
{
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_TOP, false);
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_BOT, true);
    
    timer.Start(TICK_TIME);
}

void flywheel_die()
{
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_TOP, 0);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_BOT, 0);
}

void flywheel_update()
{
    if (timer.IsFinished()) {
        close_button_debounce.add(CrcLib::ReadDigitalChannel(FLYWHEEL_CLOSE_BUTTON));
        far_button_debounce.add(CrcLib::ReadDigitalChannel(FLYWHEEL_FAR_BUTTON));
    }

    if (close_button_debounce.is_set()) {
        flywheel_state = (flywheel_state == CLOSE ? OFF : CLOSE); // toggle 
    }
    else if (far_button_debounce.is_set()) {
        flywheel_state = (flywheel_state == FAR ? OFF : FAR); // toggle 
    }

    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_TOP, flywheel_state);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_BOT, flywheel_state);

    timer.Next();
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
