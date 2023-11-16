#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>

#include "const.h"
#include "utils.h"

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
    const auto flywheel_speed = utils::threshold(
        utils::map<int8_t>(
            CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R),
            INT8_MIN, INT8_MAX, 0, INT8_MAX),
        PWM_THRESHOLD);

    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, flywheel_speed);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, flywheel_speed);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
