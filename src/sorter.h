#pragma once

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

