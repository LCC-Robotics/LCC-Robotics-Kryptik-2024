#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_

#include <float.h>

namespace utils {


template <class T>
struct Range {
    T min;
    T max;
};

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
constexpr inline T threshold(T raw, T thresh)
{
    return raw > thresh ? raw : 0;
}


}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
