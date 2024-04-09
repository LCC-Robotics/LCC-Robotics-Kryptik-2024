#pragma once

#include <CrcLib.h>

#include "const.h"

// TODO: Sorter
namespace Sorter {

// TODO: Find values for door 
enum DoorState {
    OPEN = 127,
    CLOSED = -128,
    DOOR_OFF = 0
};

enum DivertState { //these values are good
    MULTI = 100,
    FLY = -128,
};

CrcLib::Timer jank_timer;

void CustomSetup()
{
    CrcLib::InitializePwmOutput(SORT_DOOR_MOTOR, false);
    CrcLib::InitializePwmOutput(SORT_DIVERT_MOTOR, false);

    jank_timer.Start(50);
}

void die()
{
    CrcLib::Update();
    
    CrcLib::SetPwmOutput(SORT_DOOR_MOTOR, 0);
}

void CustomUpdate(bool ticked)
{
    CrcLib::Update();
    
    int8_t divert_val = FLY;
    int8_t door_val = DOOR_OFF;

    if (CrcLib::ReadDigitalChannel(SORT_DIVERT_BUTTON)){
        divert_val = MULTI;
    }


    if (CrcLib::ReadDigitalChannel(SORT_DOOR_BUTTON)){
       jank_timer.Next();
        
        if (!jank_timer.IsFinished()){
            door_val = OPEN; }
        else {
            door_val = DOOR_OFF; }
    }
    else if (!CrcLib::ReadDigitalChannel(SORT_DOOR_BUTTON)) {
        jank_timer.Next();

        if (!jank_timer.IsFinished() ){
            door_val = CLOSED;
        }
        else {
            door_val = DOOR_OFF;
        }
    }

    CrcLib::SetPwmOutput(SORT_DIVERT_MOTOR, divert_val);
    CrcLib::SetPwmOutput(SORT_DOOR_MOTOR, door_val);

    Serial.write(door_val);
}
}

