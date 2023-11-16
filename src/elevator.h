#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include <CrcLib.h>

#include "helpers/utils.h"


// ========================
// PINS:

constexpr uint8_t ELEVATOR_MOTOR_PIN = CRC_PWM_7;

// ========================
// INPUTS:

constexpr BUTTON ELEVATOR_UP = BUTTON::ARROW_UP;
constexpr BUTTON ELEVATOR_DOWN = BUTTON::ARROW_DOWN;

// ========================
// CONST:

constexpr bool ELEVATOR_REVERSE = false;

void elevator_setup()
{
    CrcLib::InitializePwmOutput(ELEVATOR_MOTOR_PIN, ELEVATOR_REVERSE);
}

void elevator_die()
{
    CrcLib::SetPwmOutput(ELEVATOR_MOTOR_PIN, 0);
}

void elevator_update()
{
    if (CrcLib::ReadDigitalChannel(ELEVATOR_UP)) {
        CrcLib::SetPwmOutput(ELEVATOR_MOTOR_PIN, PWM_RANGE.min);
    }
    if (CrcLib::ReadDigitalChannel(ELEVATOR_DOWN)){
        CrcLib::SetPwmOutput(ELEVATOR_MOTOR_PIN, PWM_RANGE.max);
    }
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
