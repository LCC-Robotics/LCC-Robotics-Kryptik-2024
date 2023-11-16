#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_

#include <CrcLib.h>

// ========================
// PINS:

constexpr uint8_t FLYWHEEL_MOTOR_L = CRC_PWM_5;
constexpr uint8_t FLYWHEEL_MOTOR_R = CRC_PWM_6;

// ========================
// INPUTS:

constexpr ANALOG FLYWHEEL_REV = ANALOG::GACHETTE_R;


void flywheel_setup()
{
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_L);
    CrcLib::InitializePwmOutput(FLYWHEEL_MOTOR_R);
}

void flywheel_die()
{
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, 0);
    CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, 0);
}

void flywheel_update()
{
    const int8_t flywheel_speed = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);
    if (flywheel_speed > 0) {
        CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_L, flywheel_speed);
        CrcLib::SetPwmOutput(FLYWHEEL_MOTOR_R, flywheel_speed);
    }
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_FLYWHEEL_H_