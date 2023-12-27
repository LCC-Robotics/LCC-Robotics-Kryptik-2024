#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_

#include <CrcLib.h>
#include <utils.h>

namespace {
using Timer = CrcLib::Timer;
using utils::almost_equal;
}

class PID {
public:
    explicit PID(const float kp = 1.0, const float kd = 0.0, const float ki = 0.0,
        const uint32_t poll_interval = 100, const double epsilon = DBL_EPSILON)
        : _poll_interval { poll_interval }
        , _epsilon { epsilon }
        , _kp { kp }
        , _kd { kd }
        , _ki { ki }
        , _timer {}
    {
    }

    void Override(double set_val)
    {
        _current_pos = (double)set_val;
        _target_pos = (double)set_val;

        _last_error = 0.0;
        _error = 0.0;
        _derror = 0.0;
        _ierror = 0.0;
    }

    void SetTarget(double target)
    {
        _target_pos = target;
    }

    double Update(double current_pos)
    {
        if (_current_pos != current_pos) {
            _current_pos = (double)current_pos;
            _timer.Start(_poll_interval);
        }

        if (_timer.IsFinished() && !almost_equal(_target_pos, _current_pos, _epsilon)) {
            _error = _target_pos - _current_pos;
            _derror = (_error - _last_error) / (double)_poll_interval;
            _ierror += _error * (double)_poll_interval;

            // PID Function
            _output = _kp * _error + _kd * _derror + _ki * _ierror;
            _last_error = _error;

            _timer.Next();
        }

        return _output;
    }

private:
    const uint32_t _poll_interval;
    const double _epsilon;

    const double _kp;
    const double _kd;
    const double _ki;

    Timer _timer;

    double _last_error = 0;
    double _error = 0;
    double _derror = 0;
    double _ierror = 0;

    double _target_pos = 0;
    double _current_pos = 0;
    double _output = 0;
};

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
