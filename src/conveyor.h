#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_CONVEYOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_CONVEYOR_H_

#include <CrcLib.h>
#include <etl/debounce.h>

#include "const.h"

// TODO: Find correct conveyor speed
enum ConveyorState: int8_t {
    CON_OFF = 0,
    CON_ON = 90
};

etl::debounce<20> conveyor_button_debounce;
CrcLib::Timer con_timer; 

int8_t conveyor_state = CON_OFF;

void conveyor_setup() {
    CrcLib::InitializePwmOutput(CONVEYOR_MOTOR, false);

    con_timer.Start(TICK_TIME);
}

void conveyor_die() {
    CrcLib::SetPwmOutput(CONVEYOR_MOTOR, 0);
}


void conveyor_update() {
    if (con_timer.IsFinished()) {
        conveyor_button_debounce.add(CrcLib::ReadDigitalChannel(CONVEYOR_TOGGLE));

        if (conveyor_button_debounce.is_set()) {
            conveyor_state = (conveyor_state == CON_OFF ? CON_ON : CON_OFF);
        }

        con_timer.Next();
    }

    CrcLib::SetPwmOutput(CONVEYOR_MOTOR, conveyor_state);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_CONVEYOR_H_
