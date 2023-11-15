#include <Arduino.h>
#include <CrcLib.h> // v1.5.0 (with cheeky fix)
#include <Encoder.h>

// CrcLib Reference:
// https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview

#include "drivetrain.h"


// ========================
// DIGITAL INPUTS:

constexpr BUTTON DIE_BUTTON = BUTTON::LOGO;

// ========================

void setup()
{
    CrcLib::Initialize();

    drivetrain_setup();

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    drivetrain_die();
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid() || CrcLib::ReadDigitalChannel(DIE_BUTTON)) {
        return die();
    }

    drivetrain_loop();
}
