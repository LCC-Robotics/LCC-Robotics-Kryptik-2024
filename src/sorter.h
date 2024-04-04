#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_SORTER_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_SORTER_H_

#include <CrcLib.h>

#include "const.h"

// TODO: Sorter
namespace Sorter {
void setup()
{
    CrcLib::InitializePwmOutput(SORT_DOOR_MOTOR, false);
    CrcLib::InitializePwmOutput(SORT_DIVERT_MOTOR, false);
}

void die()
{
    CrcLib::SetPwmOutput(SORT_DOOR_MOTOR, 0);
    CrcLib::SetPwmOutput(SORT_DIVERT_MOTOR, 0);
}

void update(bool ticked)
{
}
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_SORTER_H_
