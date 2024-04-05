#pragma once

#include <CrcLib.h>

#include "const.h"

namespace DriveTrain {
void setup()
{
    CrcLib::InitializePwmOutput(FL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BR_DRIVE_MOTOR, true);
    CrcLib::InitializePwmOutput(FR_DRIVE_MOTOR, true);
}

void die()
{
    CrcLib::SetPwmOutput(FL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BR_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(FR_DRIVE_MOTOR, 0);
}

void update(bool ticked)
{
    int8_t forward_val = CrcLib::ReadAnalogChannel(FORWARD_CHANNEL);
    int8_t yaw_val = CrcLib::ReadAnalogChannel(YAW_CHANNEL);
    int8_t strafe_val = CrcLib::ReadAnalogChannel(STRAFE_CHANNEL);

    // Precision Control:
    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL_L)) {
        forward_val = (int8_t)(forward_val / 2);
        yaw_val = (int8_t)(yaw_val / 2);
    }

    if (CrcLib::ReadDigitalChannel(PRECISION_CONTROL_R)) {
        strafe_val = (int8_t)(strafe_val / 2);
    }

    // Drive:
    CrcLib::MoveHolonomic(
        forward_val, yaw_val, strafe_val,
        FL_DRIVE_MOTOR, BL_DRIVE_MOTOR,
        BR_DRIVE_MOTOR, FR_DRIVE_MOTOR);
}
}
