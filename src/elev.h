#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEV_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEV_H_

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

// TODO: find good pid values

Encoder encoder { ELEV_ENCO_A, ELEV_ENCO_B };
PID<long, PRECISION> pid { 1.0, 0.0, 0.0 };

etl::debounce<20> next_button_debounce;
etl::debounce<20> prev_button_debounce;

ElevMode elev_mode = ElevMode::AUTO;
int elev_auto_index = 0;

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
    long pos = encoder.read();

    if (ticked) {
        next_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_NEXT_BUTTON));
        prev_button_debounce.add(CrcLib::ReadDigitalChannel(ELEV_PREV_BUTTON));
    }

    // MANUAL MODE
    auto mult_val = utils::pm_thresh<int8_t>(
        CrcLib::ReadAnalogChannel(ELEV_MANUAL_CHANNEL), 20); // pm_thresh adds threshold for positive and negative direction

    if (mult_val != 0) {
        elev_mode = ElevMode::MANUAL;
    }

    // AUTO MODE

    if (next_button_debounce.is_set()) { // next level
        if (elev_mode == ElevMode::MANUAL) { // find
            elev_mode = ElevMode::AUTO;

            elev_auto_index = find_next_level(pos);
            pid.Override(POSITIONS[elev_auto_index]); // sets errors to zero, reset
        } else {
            elev_auto_index++;
        }

        if (elev_auto_index >= POSITIONS.size()) {
            elev_auto_index = POSITIONS.size() - 1;
        }

        pid.SetTarget(elev_auto_index);

    } else if (prev_button_debounce.is_set()) { // prev level
        if (elev_mode == ElevMode::MANUAL) { // find 
            elev_mode = ElevMode::AUTO;

            elev_auto_index = find_prev_level(pos);
            pid.Override(POSITIONS[elev_auto_index]); // sets errors to zero, reset
        } else {
            elev_auto_index--;
        }

        if (elev_auto_index < 0) {
            elev_auto_index = 0;
        }

        pid.SetTarget(elev_auto_index);
    }

    if (elev_mode == ElevMode::AUTO) { // read pid 
        mult_val = (int8_t)utils::limit_range<long>(
            pid.Update(pos), INT8_MIN, INT8_MAX); // takes raw output from pid and limits range
    }

    CrcLib::SetPwmOutput(ELEV_MOTOR, mult_val);
}
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_ELEV_H_
