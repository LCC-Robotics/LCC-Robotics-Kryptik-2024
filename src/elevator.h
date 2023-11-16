#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include <CrcLib.h>

#include "const.h"
#include "helpers/utils.h"

void elevator_setup()
{
    CrcLib::InitializePwmOutput(ELEVATOR_MOTOR, false);
}

void elevator_die()
{
    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, 0);
}

void elevator_update()
{
    int8_t elevator_val = 0;

    if (CrcLib::ReadDigitalChannel(ELEVATOR_UP))
        elevator_val = PWM_RANGE.max;
    if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN))
        elevator_val = PWM_RANGE.max;

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL)) {
        elevator_val /= PRECISION_DIVISION_FACTOR;
    }

    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
