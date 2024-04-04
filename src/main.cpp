#include <CrcLib.h> // v1.5.0 (with cheeky fix)

// CrcLib Reference:
// https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview

#include "clock.h"
#include "drivetrain.h"
#include "elev.h"
#include "flywheel.h"
#include "multi.h"
#include "pickup.h"
#include "sorter.h"
#include "tunes.h"

constexpr long TICK_SPEED = 1;
CrcLib::Timer global_clock;

void setup()
{
    CrcLib::Initialize();
    global_clock.Start(TICK_SPEED);

    DriveTrain::setup();
    elev_setup();
    flywheel_setup();
    multi_setup();
    sorter_setup();
    pickup_setup();

#ifdef DEBUG // only start serial if in debug mode (serial can affect performance)
    Serial.begin(BAUD); // macro defined in platformio.ini
#endif
}

void die()
{
    DriveTrain::die();
    elev_die();
    flywheel_die();
    multi_die();
    pickup_die();
    sorter_die();
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

    DriveTrain::update(ticked);
    elev_update();
    flywheel_update();
    multi_update();
    sorter_update();
    pickup_update();
    tunes_update();
}
