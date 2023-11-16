#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_

#include <CrcLib.h>

#include "const.h"

void gripper_setup()
{
    CrcLib::InitializePwmOutput(GRIPPER_MOTOR_L, false);
    CrcLib::InitializePwmOutput(GRIPPER_MOTOR_R, false);
}

void gripper_die()
{
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_L, 0);
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_R, 0);
}
void gripper_update()
{
    int8_t set_pos = CrcLib::ReadAnalogChannel(GRIPPER_CONTROL);
    
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_L, set_pos);
    CrcLib::SetPwmOutput(GRIPPER_MOTOR_R, (int8_t)(-set_pos));
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_GRIPPER_H_
