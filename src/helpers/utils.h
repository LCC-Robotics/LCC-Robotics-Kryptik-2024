#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_

#include <CrcLib.h>

template <class T>
struct Range {
    T min;
    T max;
};

constexpr Range<int8_t> PWM_RANGE { -128, 127 };

template <class T>
inline constexpr T threshold(T raw, T lower_threshold, T upper_threshold)
{
    if (lower_threshold < raw || raw < upper_threshold)
        return 0;
    else
        return raw;
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
