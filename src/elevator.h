#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include "utils.h"
#include <CrcLib.h>
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "const.h"
#include "pid.h"

Encoder elevator_encoder { ELEVATOR_ENCO_A, ELEVATOR_ENCO_B };
PID elevator_pid { 1.0, 0.0, 0.0, 100, 0.05 };

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
        elevator_val = INT8_MAX;
    if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN))
        elevator_val = INT8_MIN;

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL))
        elevator_val = utils::percent(elevator_val, PRECISION_PERCENT);

    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
