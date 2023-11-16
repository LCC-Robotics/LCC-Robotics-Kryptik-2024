#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_

#include <CrcLib.h>

constexpr uint32_t PID_POLL_INTERVAL = 100; // ms

template <class T>
class PID {
    using Timer = CrcLib::Timer;

    static constexpr float CLOSE_ENOUGH = 0.05;

public:
    explicit PID(const float kp = 1.0, const float kd = 0.0, const float ki = 0.0,
        const uint32_t poll_interval = PID_POLL_INTERVAL)
        : _kp { kp }
        , _kd { kd }
        , _ki { ki }
        , _timer {}
        , _poll_interval{poll_interval}
    {
    }

    void Override(T set_val)
    {
        _set_val = (double)set_val;
        _output = (double)set_val;

        _last_error = 0.0;
        _error = 0.0;
        _derror = 0.0;
        _ierror = 0.0;
    }

    T Update(T set_val)
    {
        if (_set_val != set_val) {
            _set_val = (double)set_val;
            _timer.Start(_poll_interval);
        }

        double delta = _set_val - _output;
        if (fabs(delta) > CLOSE_ENOUGH && _timer.IsFinished()) {
            _error = delta;
            _derror = (_error - _last_error) / _poll_interval;
            _ierror += _error * _poll_interval;

            // PID Function
            _output = _kp * _error + _kd * _derror + _ki * _ierror;
            _last_error = _error;
        }

        return (T)_output;
    }

private:
    const double _kp;
    const double _kd;
    const double _ki;

    double _last_error = 0;
    double _error = 0;
    double _derror = 0;
    double _ierror = 0;

    const uint32_t _poll_interval;
    Timer _timer;

    double _set_val = 0;
    double _output = 0;
};

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
