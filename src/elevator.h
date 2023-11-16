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
    if (CrcLib::ReadDigitalChannel(ELEVATOR_UP)) {
        CrcLib::SetPwmOutput(ELEVATOR_MOTOR, PWM_RANGE.min);
    }
    if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN)){
        CrcLib::SetPwmOutput(ELEVATOR_MOTOR, PWM_RANGE.max);
    }
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
