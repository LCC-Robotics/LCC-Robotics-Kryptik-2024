#pragma once

#include <CrcLib.h>

#include "utils.h"


template <class T, T EPSILON>
class PID {
    using Timer = CrcLib::Timer;

public:
    explicit PID(float kp = 1.0, float kd = 0.0, float ki = 0.0)
        : last_poll(millis())
        , _kp { kp }
        , _kd { kd }
        , _ki { ki }
    {
    }

    void Override(T set_val)
    {
        _target_state = set_val;

        _last_error = 0.0;
        _error = 0.0;
        _derror = 0.0;
        _ierror = 0.0;
    }

    void SetTarget(T target)
    {
        _target_state = target;
    }

    T Update(T pos)
    {
        long delta = millis() - last_poll;

        if (!utils::almost_equal(_target_state, pos, EPSILON)) {
            _error = _target_state - pos;
            _derror = (_error - _last_error) / (T)delta;
            _ierror += _error * (T)delta;

            // PID Function
            _output = _kp * _error + _kd * _derror + _ki * _ierror;
            _last_error = _error;
        }

        return _output;
    }

private:
    unsigned long last_poll;

    const T _kp;
    const T _kd;
    const T _ki;

    T _last_error = 0;
    T _error = 0;
    T _derror = 0;
    T _ierror = 0;

    T _target_state = 0;
    T _output = 0;
};

