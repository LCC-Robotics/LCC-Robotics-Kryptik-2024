#include <CrcLib.h> // v1.5.0 (with cheeky fix)

// CrcLib Reference:
// https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview

#include "pickup.h"
#include "drivetrain.h"
#include "flywheel.h"
#include "multiplier.h"
#include "sorter.h"
#include "tunes.h"

void setup()
{
    CrcLib::Initialize();

    drivetrain_setup();
    multi_setup();
    sorter_setup();
    pickup_setup();
    flywheel_setup();

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    drivetrain_die();
    multi_die();
    pickup_die();
    flywheel_die();
    sorter_die();
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid() || CrcLib::ReadDigitalChannel(DIE_BUTTON)) {
        return die();
    }

    drivetrain_update();
    multi_update();
    flywheel_update();
    sorter_update();
    pickup_update();
    tunes_update();
}
