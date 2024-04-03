#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_PICKUP_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_PICKUP_H_

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"

// TODO: Find correct pickup speed
enum ElevatorState : int8_t {
    PU_UP = 127,
    PU_DOWN = -128,
    PU_OFF = 0
};

void pickup_setup()
{
    CrcLib::InitializePwmOutput(PICKUP_MOTOR, false);
}

void pickup_die()
{
    CrcLib::SetPwmOutput(PICKUP_MOTOR, 0);
}

void pickup_update()
{
    int8_t pickup_state = PU_OFF;

    if (CrcLib::ReadDigitalChannel(PICKUP_UP_BUTTON)) {
        pickup_state = PU_UP;
    } else if (CrcLib::ReadDigitalChannel(PICKUP_DOWN_BUTTON)) {
        pickup_state = PU_DOWN;
    }

    CrcLib::SetPwmOutput(PICKUP_MOTOR, pickup_state);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_pickup_H_
