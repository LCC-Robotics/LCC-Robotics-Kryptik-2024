#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include <CrcLib.h>
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "const.h"
#include "pid.h"

enum ElevatorState : int8_t {
    ELEV_OFF = 0,
    ELEV_UP = 90,
    ELEV_DOWN = -90,
};

Encoder elevator_encoder { ELEVATOR_ENCO_A, ELEVATOR_ENCO_B };
PID elevator_pid { 1.0, 0.0, 0.0, 100, 0.05 };

void multi_setup()
{
    CrcLib::InitializePwmOutput(ELEVATOR_MOTOR, false);
}

void multi_die()
{
    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, 0);
}

// TODO: Implement ball placer

void multi_update()
{
    int8_t elevator_val = ELEV_OFF;

    if (CrcLib::ReadDigitalChannel(ELEVATOR_UP_BUTTON)) {
        elevator_val = ELEV_UP;
    } else if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN_BUTTON)) {
        elevator_val = ELEV_DOWN;
    }

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL)) {
        elevator_val = (int8_t)(elevator_val / 2);
    }

    CrcLib::SetPwmOutput(ELEVATOR_MOTOR, elevator_val);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
