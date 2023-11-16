#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>

#include "const.h"
#include "helpers/utils.h"

void flywheel_setup()
{
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_L, false);
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_R, true);
}

void flywheel_die()
{
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, 0);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, 0);
}

void flywheel_update()
{
    const int8_t flywheel_speed = threshold(CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R),
        PWM_LOWER_THRESHOLD,
        PWM_UPPER_THRESHOLD);

    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, flywheel_speed);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, flywheel_speed);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
