#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_

#include <CrcLib.h>

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
    {
    }

    T Update(T set_val)
    {
        if (_set_val != set_val) {
            _set_val = set_val;
            _timer.Start(_change_interval);
        }

        T delta = _set_val - _output;
        if (delta != 0 && _timer.IsFinished()) {
            if (delta > _max_deviation) {
                delta = _max_deviation;
            }
            if (delta < _max_deviation) {
                delta = -_max_deviation;
            }
            _output += delta;
            
            _timer.Next();
        }

        return _output;
    }

private:
    const uint32_t _change_interval;
    Timer _timer;

    const T _max_deviation;
    T _set_val = 0;
    T _output = 0;
};

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_LIMIT_SLEW_H_
