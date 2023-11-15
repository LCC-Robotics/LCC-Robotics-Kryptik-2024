#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_

#include <CrcLib.h> // v1.5.0 (with cheeky fix)

// ========================
// PINS:

constexpr uint8_t FL_DRIVE_PIN = CRC_PWM_1;
constexpr uint8_t BL_DRIVE_PIN = CRC_PWM_2;
constexpr uint8_t BR_DRIVE_PIN = CRC_PWM_3;
constexpr uint8_t FR_DRIVE_PIN = CRC_PWM_4;

// ========================
// INPUTS:

constexpr ANALOG FORWARD_CHANNEL = ANALOG::JOYSTICK1_Y;
constexpr ANALOG YAW_CHANNEL = ANALOG::JOYSTICK1_X;
constexpr ANALOG STRAFE_CHANNEL = ANALOG::JOYSTICK2_X;

constexpr BUTTON PRECISION_CONTROL = BUTTON::L1;

// ========================
// CONST:
constexpr uint8_t PRECISION_DIVISION_FACTOR = 2;

void drivetrain_die()
{
    CrcLib::SetPwmOutput(FL_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(BL_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(BR_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(FR_DRIVE_PIN, 0);
}

void drivetrain_setup()
{
    CrcLib::InitializePwmOutput(FL_DRIVE_PIN, false);
    CrcLib::InitializePwmOutput(BL_DRIVE_PIN, false);
    CrcLib::InitializePwmOutput(BR_DRIVE_PIN, true);
    CrcLib::InitializePwmOutput(FR_DRIVE_PIN, true);
}

void drivetrain_loop()
{
    // Precision Control:

    int8_t foward_val = CrcLib::ReadAnalogChannel(FORWARD_CHANNEL);
    int8_t yaw_val = CrcLib::ReadAnalogChannel(YAW_CHANNEL);
    int8_t strafe_val = CrcLib::ReadAnalogChannel(STRAFE_CHANNEL);

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL)) {
        foward_val /= PRECISION_DIVISION_FACTOR;
        yaw_val /= PRECISION_DIVISION_FACTOR;
        strafe_val /= PRECISION_DIVISION_FACTOR;
    }

    // Drive:

    CrcLib::MoveHolonomic(
        foward_val, yaw_val, strafe_val,
        FL_DRIVE_PIN, BL_DRIVE_PIN, BR_DRIVE_PIN, FR_DRIVE_PIN);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_
