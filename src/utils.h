#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_

#include <float.h>
#include <stdint.h>

#include <const.h>
namespace utils {

template <class T>
struct Range {
    T min;
    T max;
};

template <class T>
constexpr inline T percent(T val, int percent)
{
    int i = val;
    return (i * percent) / 100;
}

constexpr inline bool almost_equal(double a, double b, double EPSILON = DBL_EPSILON)
{
    auto diff = a - b;
    return (diff < EPSILON) && (diff > -EPSILON);
}

template <class T>
constexpr inline T map(T raw, T in_min, T in_max, T out_min, T out_max)
{
    return (raw - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <class T>
constexpr inline T threshold(T raw, T threshold)
{
    return raw > threshold ? raw : 0;
}

constexpr inline int8_t convert_analog(int8_t val, int8_t vmin = INT8_MIN, int8_t vmax = INT8_MAX, int8_t thresh = ANALOG_THRESHOLD)
{
    return threshold(
        map<int8_t>(val, vmin, vmax, 0, vmax),
        thresh);
}

}
#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
