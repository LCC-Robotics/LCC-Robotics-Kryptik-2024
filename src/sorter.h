#pragma once

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"

// TODO: Sorter
namespace Sorter {

 
enum DoorState {
    OPEN = 127,
    CLOSED = -128,
};

enum DivertState { //these values are to test
    MULTI = -120,
    FLY = 120,
};

etl::debounce<20> door_debounce;

CrcLib::Timer jank_timer;
CrcLib::Timer debounce_timer;

void CustomSetup()
{
    CrcLib::InitializePwmOutput(SORT_DOOR_MOTOR, false);
    CrcLib::InitializePwmOutput(SORT_DIVERT_MOTOR, false);

    jank_timer.Start(50);
    debounce_timer.Start(50);
}

void die()
{
    CrcLib::Update();
    
    CrcLib::SetPwmOutput(SORT_DOOR_MOTOR, 0);
}

void CustomUpdate()
{
    CrcLib::Update();
    
    int8_t divert_val = FLY;
    int8_t door_val = CLOSED;


    if (CrcLib::ReadDigitalChannel(SORT_DIVERT_BUTTON)){
        divert_val = MULTI;
    }

    if (CrcLib::ReadDigitalChannel(SORT_DOOR_BUTTON)){
        door_val = OPEN;
    }
   

    CrcLib::SetPwmOutput(SORT_DIVERT_MOTOR, divert_val);
    CrcLib::SetPwmOutput(SORT_DOOR_MOTOR, door_val);

}
}

