#pragma once

#include <CrcLib.h>
#define ENCODER_OPTIMIZE_INTERRUPTS // optimize encoder overhead
#include <Encoder.h>

#include <etl/array.h>
#include <etl/debounce.h>

#include "const.h"
#include "pid.h"
#include "utils.h"

namespace Elevator {
enum class ElevMode {
    AUTO,
    MANUAL
};

// TODO: find correct encoder values for heights, test custom script?

constexpr etl::array<long, 3> POSITIONS {
    0, // home
    20, // short multi
    40 // tall multi
};

constexpr long PRECISION = 30;

// ================
// HELPERS
// ================

constexpr int find_next_level(long pos)
{
    for (int i = 0; i != POSITIONS.size(); i++) { // start from bottom
        if (POSITIONS[i] - pos > 0)
            return i;
    }

    return POSITIONS.back();
}

constexpr int find_prev_level(long pos)
{
    for (int i = POSITIONS.size() - 1; i != 0; i++) { // start from top
        if (pos - POSITIONS[i] > 0)
            return i;
    }

    return POSITIONS.front();
}

// ================
// ROUTINES
// ================

void setup() { CrcLib::InitializePwmOutput(ELEV_MOTOR, false); }

void die() { CrcLib::SetPwmOutput(ELEV_MOTOR, 0); }

void update(bool ticked)
{
    // TODO: find good pid values

    static Encoder encoder { ELEV_ENCO_A, ELEV_ENCO_B };
    static PID<long, PRECISION> pid { 1.0, 0.0, 0.0 };

    static etl::debounce<20> next_button_debounce;
    static etl::debounce<20> prev_button_debounce;

    static ElevMode mode = ElevMode::AUTO;
    static int level_index = 0;

    // ==========

    long pos = encoder.read();

    // MANUAL MODE
    auto mult_val = utils::pm_thresh<int8_t>(
        CrcLib::ReadAnalogChannel(ELEV_MANUAL_CHANNEL), 20); // pm_thresh adds threshold for positive and negative direction

    if (mult_val != 0) { // update state to manual
        mode = ElevMode::MANUAL;
    }

    // =============

    // AUTO MODE
    if (ticked) { // update debounced buttons for auto mode
        next_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_NEXT_BUTTON));
        prev_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_PREV_BUTTON));
    }

    if (next_button_debounce.is_set()) { // next level
        if (mode == ElevMode::MANUAL) { // find
            mode = ElevMode::AUTO;

            level_index = find_next_level(pos);
            pid.Override(POSITIONS[level_index]); // sets errors to zero, reset
        } else {
            level_index++;
        }

        if (level_index >= POSITIONS.size()) {
            level_index = POSITIONS.size() - 1;
        } // snap back if go over

        pid.SetTarget(POSITIONS[level_index]);

    } else if (prev_button_debounce.is_set()) { // prev level
        if (mode == ElevMode::MANUAL) { // find
            mode = ElevMode::AUTO;

            level_index = find_prev_level(pos);
            pid.Override(POSITIONS[level_index]); // sets errors to zero, reset
        } else {
            level_index--;
        }

        if (level_index < 0) {
            level_index = 0;
        } // snap back if go below

        pid.SetTarget(POSITIONS[level_index]);
    }

    if (mode == ElevMode::AUTO) { // read pid
        long raw_output = pid.Update(pos);
        mult_val = (int8_t)(utils::limit_range<long>(raw_output, INT8_MIN, INT8_MAX)); // takes raw output from pid and limits range
    }

    // =============

    CrcLib::SetPwmOutput(ELEV_MOTOR, mult_val); // write value to motor
}
}
