#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>

#include "const.h"
#include "helpers.h"

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
    const auto flywheel_speed = helpers::convert_analog(CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R));

    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, flywheel_speed);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, flywheel_speed);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
