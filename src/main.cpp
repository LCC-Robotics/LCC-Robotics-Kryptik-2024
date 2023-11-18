#include <CrcLib.h> // v1.5.0 (with cheeky fix)

// CrcLib Reference:
// https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview

#include "drivetrain.h"
#include "elevator.h"
#include "flywheel.h"
#include "gripper.h"
#include "tunes.h"

void setup()
{
    CrcLib::Initialize();

    drivetrain_setup();
    elevator_setup();
    gripper_setup();
    flywheel_setup();

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    drivetrain_die();
    elevator_die();
    gripper_die();
    flywheel_die();
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid() || CrcLib::ReadDigitalChannel(DIE_BUTTON)) {
        return die();
    }

    drivetrain_update();
    elevator_update();
    gripper_update();
    flywheel_update();
    tunes_update();
}
