#pragma once

#include <CrcLib.h>

#include <QuickPID.h>
#define ENCODER_OPTIMIZE_INTERRUPTS // optimize encoder overhead
#include <Encoder.h>

#include <etl/array.h>
#include <etl/debounce.h>

#include "const.h"
#include "utils.h"

namespace Elevator {

// TODO: find correct encoder values for heights, test custom script?

enum ElevMode : uint8_t { // based on QuickPID::Control
    Manual = 0,
    Auto = 1
};

constexpr etl::array<float, 3> PRESET_LEVELS {
    0.0, // home
    20.0, // short multi
    40.0 // tall multi
};

// ================
// HELPERS
// ================

constexpr int find_next_level(float pos)
{
    for (int i = 0; i != PRESET_LEVELS.size(); i++) { // start from bottom
        if (PRESET_LEVELS[i] - pos > 0)
            return i;
    }
    return PRESET_LEVELS.back();
}

constexpr int find_prev_level(float pos)
{
    for (int i = PRESET_LEVELS.size() - 1; i != 0; i--) { // start from top
        if (pos - PRESET_LEVELS[i] > 0)
            return i;
    }
    return PRESET_LEVELS.front();
}

// ================
// ROUTINES
// ================

// TODO: Find values for PID (possibly using sTune?)

float input, output, setpoint;
QuickPID pid { &input, &output, &setpoint,
    1.0, 0.0, 0.0,
    QuickPID::Action::direct };

Encoder encoder { ELEV_ENCO_A, ELEV_ENCO_B };

etl::debounce<20> next_button_debounce;
etl::debounce<20> prev_button_debounce;

int level_index = 0;

void setup()
{
    CrcLib::InitializePwmOutput(ELEV_MOTOR, false);
    pid.SetMode(ElevMode::Auto);
    pid.SetOutputLimits(INT8_MIN, INT8_MAX);
}

void die() { CrcLib::SetPwmOutput(ELEV_MOTOR, 0); }

void update(bool ticked)
{
    if (ticked) { // update debounced buttons each tick
        next_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_NEXT_BUTTON));
        prev_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_PREV_BUTTON));
    }

    // ============

    input = (float)(encoder.read());

    // manual
    auto manual_channel = utils::pm_thresh<int8_t>(
        CrcLib::ReadAnalogChannel(ELEV_MANUAL_CHANNEL), 20); // pm_thresh adds threshold for positive and negative direction

    if (manual_channel != 0) { // update state to manual
        pid.SetMode(ElevMode::Manual);
        output = manual_channel;
    }

    // auto
    if (next_button_debounce.is_set()) { // NEXT LEVEL
        if (pid.GetMode() == ElevMode::Manual) {
            pid.SetMode(ElevMode::Auto);
            level_index = find_next_level(input); // find next closest level
        } else {
            level_index++;
        }

        if (level_index >= PRESET_LEVELS.size()) {
            level_index = PRESET_LEVELS.size() - 1; // snap down if go over max
        } 

        setpoint = PRESET_LEVELS[level_index];

    } else if (prev_button_debounce.is_set()) { // PREV LEVEL
        if (pid.GetMode() == ElevMode::Manual) {
            pid.SetMode(ElevMode::Auto);
            level_index = find_prev_level(input);
        } else {
            level_index--;
        }

        if (level_index < 0) {
            level_index = 0; // snap up if go below min
        } 

        setpoint = PRESET_LEVELS[level_index];
    }

    pid.Compute(); //! compute values

    CrcLib::SetPwmOutput(ELEV_MOTOR, (int8_t)(output)); // write value to motor
}
}
