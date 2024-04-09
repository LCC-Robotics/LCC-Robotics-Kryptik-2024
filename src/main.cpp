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

constexpr long TICK_SPEED = 1;
CrcLib::Timer global_clock;

void setup()
{
    CrcLib::Initialize();
    global_clock.Start(TICK_SPEED);
    Serial.begin(9600);

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


    bool ticked = global_clock.IsFinished();
    if (ticked) {
        global_clock.Next();
    }
    

    DriveTrain::CustomUpdate(ticked);
    Elevator::CustomUpdate(ticked);
    Flywheel::CustomUpdate(ticked);
    Placer::CustomUpdate(ticked);
    Sorter::CustomUpdate(ticked);
    Pickup::CustomUpdate(ticked);
    Tunes::CustomUpdate(ticked);

}
