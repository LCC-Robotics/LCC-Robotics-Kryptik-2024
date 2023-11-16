#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_

#include <CrcLib.h>


// TODO
template <class T>
class PID {
    using Timer = CrcLib::Timer;
public:
     explicit PID(const float kp = 1.0, const float kd = 0.0, const float ki = 0.0)
        : _kp { kp }
        , _kd { kd }
        , _ki { ki }
    {
    }

    T Update(T set_val) {

    }

private:
    const float _kp;
    const float _kd;
    const float _ki;
    const uint32_t _sample_interval;

    Timer _timer;
    T _set_val;
    T _output;
};

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_PID_H_
