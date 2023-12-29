#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_

#include <CrcLib.h>

#include "const.h"
#include "helpers.h"

void gripper_setup()
{
    CrcLib::InitializePwmOutput(GRIPPER_MOTOR_L, false);
    CrcLib::InitializePwmOutput(GRIPPER_MOTOR_R, true);
}

void gripper_die()
{
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_L, 0);
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_R, 0);
}
void gripper_update()
{
    auto set_pos = helpers::convert_analog(CrcLib::ReadAnalogChannel(GRIPPER_CONTROL));

    CrcLib::SetPwmOutput(GRIPPER_MOTOR_L, set_pos);
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_R, set_pos);
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_
