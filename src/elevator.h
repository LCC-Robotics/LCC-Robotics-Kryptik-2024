#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include <CrcLib.h>

#include "const.h"
#include "helpers/limitSlew.h"

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
    static LimitSlew<int8_t> elevator_slew_limiter { PWM_MAX_DEVIATION };
    int8_t elevator_val = 0;

    if (CrcLib::ReadDigitalChannel(ELEVATOR_UP))
        elevator_val = INT8_MAX;
    if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN))
        elevator_val = INT8_MIN;

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL)) {
        elevator_val /= PRECISION_DIVISION_FACTOR;
    }

    elevator_val = elevator_slew_limiter.Update(elevator_val);

    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
