#pragma once

#include <CrcLib.h>

#include "const.h"
#include "utils.h"

namespace DriveTrain {
void CustomSetup()
{
    CrcLib::InitializePwmOutput(FL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BR_DRIVE_MOTOR, true);
    CrcLib::InitializePwmOutput(FR_DRIVE_MOTOR, true);
}

void die()
{
    CrcLib::Update();
    
    CrcLib::SetPwmOutput(FL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BR_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(FR_DRIVE_MOTOR, 0);
}

void CustomUpdate(bool ticked)
{
    CrcLib::Update();
    
    auto forward_val = utils::pm_thresh<int8_t>(CrcLib::ReadAnalogChannel(FORWARD_CHANNEL), 4);
    auto yaw_val = utils::pm_thresh<int8_t>(CrcLib::ReadAnalogChannel(YAW_CHANNEL), 4);
    auto strafe_val = utils::pm_thresh<int8_t>(CrcLib::ReadAnalogChannel(STRAFE_CHANNEL), 4);

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
