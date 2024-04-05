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
            _derror = (_error - _last_error) / (float)delta;
            _ierror += _error * (float)delta;

            // PID Function
            _output = (T)(_kp * _error + _kd * _derror + _ki * _ierror);
            _last_error = _error;
        }

        return _output;
    }

    inline T get_output() const {return _output;}

private:
    unsigned long last_poll;

    const float _kp;
    const float _kd;
    const float _ki;

    float _last_error = 0;
    float _error = 0;
    float _derror = 0;
    float _ierror = 0;

    T _target_state = 0;
    T _output = 0;
};

