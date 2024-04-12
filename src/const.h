#pragma once

#include <CrcLib.h>

// ============================
// PINS:
// ============================

enum PINS : uint8_t {
    // DRIVETRAIN
    FL_DRIVE_MOTOR = CRC_PWM_1,
    BL_DRIVE_MOTOR = CRC_PWM_2,
    BR_DRIVE_MOTOR = CRC_PWM_3,
    FR_DRIVE_MOTOR = CRC_PWM_4,

    // FLYWHEEL
    FW_MOTOR_TOP = CRC_PWM_5,
    FW_MOTOR_BOT = CRC_PWM_6,

    FW_FEEDING_MOTOR = CRC_DIG_1,

    // PICKUP
    PICKUP_MOTOR = CRC_PWM_7,

    // MULTIPLIER
    ELEV_MOTOR = CRC_PWM_8,
    MULTI_PLACER_MOTOR = CRC_PWM_9,
    MULTI_GUIDE_MOTOR = CRC_PWM_10,

    ELEV_ENCO_A = CRC_ENCO_A,
    ELEV_ENCO_B = CRC_ENCO_B,

    // SORTING
    SORT_DOOR_MOTOR = CRC_PWM_11,
    SORT_DIVERT_MOTOR = CRC_PWM_12,
};

// ============================
// INPUTS:
// ============================

// tune
constexpr BUTTON VICTORY_BUTTON = BUTTON::START;

// die
constexpr BUTTON DIE_BUTTON = BUTTON::LOGO; //works

// drivelock
constexpr BUTTON PRECISION_CONTROL_L = BUTTON::HATL; //works
constexpr BUTTON PRECISION_CONTROL_R = BUTTON::HATR; //works

// PICKUP
constexpr BUTTON PICKUP_UP_BUTTON = BUTTON::COLORS_UP; //works
constexpr BUTTON PICKUP_DOWN_BUTTON = BUTTON::COLORS_RIGHT; //works

// MULTIPLIER
constexpr ANALOG ELEV_DOWN_CHANNEL = ANALOG::GACHETTE_L; //works
constexpr ANALOG ELEV_UP_CHANNEL = ANALOG::GACHETTE_R; //works

constexpr BUTTON MULTI_BUTTON = BUTTON::SELECT;

constexpr BUTTON GUIDE_DEPLOY_BUTTON = BUTTON::ARROW_UP;
constexpr BUTTON GUIDE_RETRACT_BUTTON = BUTTON::ARROW_DOWN;

// sorting
constexpr BUTTON SORT_DOOR_BUTTON = BUTTON::COLORS_LEFT;
constexpr BUTTON SORT_DIVERT_BUTTON = BUTTON::COLORS_DOWN; //works

// drivetrain
constexpr ANALOG FORWARD_CHANNEL = ANALOG::JOYSTICK1_Y; //works
constexpr ANALOG YAW_CHANNEL = ANALOG::JOYSTICK1_X; //works
constexpr ANALOG STRAFE_CHANNEL = ANALOG::JOYSTICK2_X; //works

// flywheel
constexpr BUTTON FW_FAR_BUTTON = BUTTON::L1; //works (find value)
constexpr BUTTON FW_CLOSE_BUTTON = BUTTON::R1; //works (find value)

