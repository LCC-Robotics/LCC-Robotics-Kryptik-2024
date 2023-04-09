#include <Arduino.h>
#include <CrcLib.h> // https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview
#include <Encoder.h>

using namespace Crc;

// ========================
// ANALOG INPUTS
// ========================

constexpr ANALOG FORWARD_CHANNEL = ANALOG::JOYSTICK1_Y;
constexpr ANALOG STRAFE_CHANNEL = ANALOG::JOYSTICK1_X;
constexpr ANALOG YAW_CHANNEL = ANALOG::JOYSTICK2_X;

// ========================
// DIGITAL INPUTS
// ========================

constexpr BUTTON DIE_BUTTON = BUTTON::LOGO;

// ========================
// PINS
// ========================

constexpr uint8_t FL_DRIVE_PIN = CRC_PWM_1;
constexpr uint8_t FR_DRIVE_PIN = CRC_PWM_2;
constexpr uint8_t BL_DRIVE_PIN = CRC_PWM_3;
constexpr uint8_t BR_DRIVE_PIN = CRC_PWM_4;

void setup()
{
    CrcLib::Initialize();
    CrcLib::InitializePwmOutput(FL_DRIVE_PIN, false);
    CrcLib::InitializePwmOutput(FR_DRIVE_PIN, false);
    CrcLib::InitializePwmOutput(BL_DRIVE_PIN, false);
    CrcLib::InitializePwmOutput(BR_DRIVE_PIN, false);

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    CrcLib::SetPwmOutput(FL_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(FR_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(BL_DRIVE_PIN, 0);
    CrcLib::SetPwmOutput(BR_DRIVE_PIN, 0);
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid() || CrcLib::ReadDigitalChannel(DIE_BUTTON)) {
        return die();
    }

    CrcLib::MoveHolonomic(
        FORWARD_CHANNEL, YAW_CHANNEL, STRAFE_CHANNEL,
        FL_DRIVE_PIN, FR_DRIVE_PIN, BL_DRIVE_PIN, BR_DRIVE_PIN);
}
