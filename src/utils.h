#pragma once

#include <Arduino.h>
#include <float.h>

namespace utils {

template <class T>
struct Range {
    T min;
    T max;
};

constexpr inline bool almost_equal(float a, float b, float EPSILON = FLT_EPSILON)
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
constexpr inline T limit_range(T raw, T min, T max)
{
    if (raw < min) {
        return min;
    } else if (raw > max) {
        return max;
    } else {
        return raw;
    }
}

template <class T>
constexpr inline T thresh(T raw, T thresh)
{
    return raw > thresh ? raw : 0;
}

template <class T>
constexpr inline T pm_thresh(T raw, T thresh)
{
    return abs(raw) > thresh ? raw : 0;
}

}

