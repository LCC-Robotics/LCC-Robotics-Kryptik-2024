#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_CONST_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_CONST_H_

#include <CrcLib.h>

using PIN = uint8_t;

// ============================
// PINS:
// ============================

// drivetrain
constexpr PIN FL_DRIVE_MOTOR = CRC_PWM_1;
constexpr PIN BL_DRIVE_MOTOR = CRC_PWM_2;
constexpr PIN BR_DRIVE_MOTOR = CRC_PWM_3;
constexpr PIN FR_DRIVE_MOTOR = CRC_PWM_4;

// flywheel
constexpr PIN FLYWHEEL_MOTOR_L = CRC_PWM_5;
constexpr PIN FLYWHEEL_MOTOR_R = CRC_PWM_6;

// elevator
constexpr PIN ELEVATOR_MOTOR = CRC_PWM_7;

// gripper 
constexpr PIN GRIPPER_MOTOR_L = CRC_PWM_8;
constexpr PIN GRIPPER_MOTOR_R = CRC_PWM_9;

// ============================
// INPUTS:
// ============================

// die
constexpr BUTTON DIE_BUTTON = BUTTON::LOGO;

// drivetrain
constexpr ANALOG FORWARD_CHANNEL = ANALOG::JOYSTICK1_Y;
constexpr ANALOG YAW_CHANNEL = ANALOG::JOYSTICK1_X;
constexpr ANALOG STRAFE_CHANNEL = ANALOG::JOYSTICK2_X;

constexpr BUTTON PRECISION_CONTROL = BUTTON::L1;

// flywheel
constexpr ANALOG FLYWHEEL_REV = ANALOG::GACHETTE_R;

// elevator
constexpr BUTTON ELEVATOR_UP = BUTTON::ARROW_UP;
constexpr BUTTON ELEVATOR_DOWN = BUTTON::ARROW_DOWN;

// gripper
constexpr ANALOG GRIPPER_CONTROL = ANALOG::GACHETTE_L;


// ============================
// CONST:
// ============================

constexpr uint8_t PRECISION_DIVISION_FACTOR = 2;

constexpr int8_t PWM_LOWER_THRESHOLD = -5;
constexpr int8_t PWM_UPPER_THRESHOLD = 5;

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_CONST_H_
