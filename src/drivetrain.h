#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_

#include <CrcLib.h>

#include "const.h"

void drivetrain_setup()
{
    CrcLib::InitializePwmOutput(FL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BL_DRIVE_MOTOR, false);
    CrcLib::InitializePwmOutput(BR_DRIVE_MOTOR, true);
    CrcLib::InitializePwmOutput(FR_DRIVE_MOTOR, true);
}

void drivetrain_die()
{
    CrcLib::SetPwmOutput(FL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BL_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(BR_DRIVE_MOTOR, 0);
    CrcLib::SetPwmOutput(FR_DRIVE_MOTOR, 0);
}

void drivetrain_update()
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

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_DRIVETRAIN_H_
