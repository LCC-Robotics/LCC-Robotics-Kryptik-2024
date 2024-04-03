#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_

#include <CrcLib.h>
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "const.h"
#include "pid.h"

enum MultEState : int8_t {
    MULTE_OFF = 0,
    MULTE_UP = 90,
    MULTE_DOWN = -90,
};

enum PlacerState : int8_t {
    PLA_OFF = 0,
    PLA_RETRACT = -90,
    PLA_DEPLOY = 90,
};

Encoder elevator_encoder { MULTI_ELEV_ENCO_A, MULTI_ELEV_ENCO_B };
PID elevator_pid { 1.0, 0.0, 0.0, 100, 0.05 };

void multi_setup()
{
    CrcLib::InitializePwmOutput(MULTI_ELEV_MOTOR, false);
    CrcLib::InitializePwmOutput(MULTI_PLACER_MOTOR, false);
    CrcLib::InitializePwmOutput(MULTI_GUIDE_MOTOR, false);
}

void multi_die()
{
    CrcLib::SetPwmOutput(MULTI_ELEV_MOTOR, 0);
    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, 0);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, 0);
}

// TODO: Find the correct values for ball placer motors

void multi_update()
{
    int8_t multe_val = MULTE_OFF;

    if (CrcLib::ReadDigitalChannel(MULTI_ELEV_UP_BUTTON)) {
        multe_val = MULTE_UP;
    } else if (CrcLib::ReadDigitalChannel(MULTI_ELEV_DOWN_BUTTON)) {
        multe_val = MULTE_DOWN;
    } 

    CrcLib::SetPwmOutput(MULTI_ELEV_MOTOR, multe_val);

    int8_t placer_val = PLA_OFF;

    if (CrcLib::ReadDigitalChannel(MULTI_DEPLOY_BUTTON)){
        placer_val = PLA_DEPLOY;
    } else if (CrcLib::ReadDigitalChannel(MULTI_RETRACT_BUTTON)) {
        placer_val = PLA_RETRACT;
    } 
    
    CrcLib::SetPwmOutput(MULTI_PLACER_MOTOR, placer_val);
    CrcLib::SetPwmOutput(MULTI_GUIDE_MOTOR, placer_val);
}

void ball_placer (){


}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEVATOR_H_
