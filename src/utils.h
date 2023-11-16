#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_

#include <CrcLib.h>

namespace utils {

template <class T>
struct Range {
    T min;
    T max;
};

template <class T>
inline constexpr T map(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <class T>
inline constexpr T threshold(T raw, T threshold)
{
    if (raw < threshold)
        return 0;
    else
        return raw;
}

}
#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_UTILS_H_
