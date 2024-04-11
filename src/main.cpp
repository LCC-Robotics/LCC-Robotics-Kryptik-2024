// CrcLib Reference:
// https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview
#include <CrcLib.h> // v1.5.0 (with cheeky fix)


#include "drivetrain.h"
#include "elev.h"
#include "flywheel.h"
#include "placer.h"
#include "pickup.h"
#include "sorter.h"
#include "tunes.h"

#include "const.h"

void setup()
{
    CrcLib::Initialize();

    DriveTrain::CustomSetup();
    Elevator::CustomSetup();
    Flywheel::CustomSetup();
    Placer::CustomSetup();
    Pickup::CustomSetup();
    Sorter::CustomSetup();
    

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    CrcLib::Update();
    
    DriveTrain::die();
    Elevator::die();
    Flywheel::die();
    Placer::die();
    Pickup::die();
    Sorter::die();
    
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid() || CrcLib::ReadDigitalChannel(DIE_BUTTON)) {
        return die();
    }

    DriveTrain::CustomUpdate();
    Elevator::CustomUpdate();
    Flywheel::CustomUpdate();
    Placer::CustomUpdate();
    Sorter::CustomUpdate();
    Pickup::CustomUpdate();
    Tunes::CustomUpdate();

}
