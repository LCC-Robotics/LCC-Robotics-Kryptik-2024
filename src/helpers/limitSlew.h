#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_

#include <CrcLib.h>

constexpr int8_t PWM_SLEW_MAX_DEV = 40;
constexpr uint32_t SLEW_CHANGE_INTERVAL = 100; // ms

// https://www.embeddedrelated.com/showarticle/646.php
// Smooths out sudden motions
template <class T = int8_t>
class LimitSlew {
    using Timer = CrcLib::Timer;

public:
    explicit LimitSlew(T max_deviation, uint32_t change_interval = SLEW_CHANGE_INTERVAL)
        : _max_deviation { max_deviation }
        , _change_interval { change_interval }
        , _timer {}
        , _set_val { 0 }
        , _output { 0 }
    {
    }

    T Update(T set_val)
    {
        if (_set_val != set_val) {
            _set_val = set_val;
            _timer.Start(_change_interval);
        }

        int8_t delta = _set_val - _output;
        if (_timer.IsFinished()) {
            if (delta > _max_deviation) {
                delta = _max_deviation;
            }
            if (delta < _max_deviation) {
                delta = -_max_deviation;
            }
            _set_val += delta;
            _timer.Start(_change_interval);
        }

        return _output;
    }

private:
    const T _max_deviation;
    const uint32_t _change_interval;
    Timer _timer;

    T _set_val;
    T _output;
};

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_
