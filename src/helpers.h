#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_MISC_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_MISC_H_

#include <stdint.h>

#include "const.h"
#include "utils.h"

namespace helpers {

constexpr inline int8_t convert_analog(int8_t val, int8_t vmin = INT8_MIN, int8_t vmax = INT8_MAX, int8_t thresh = 5)
{
    return utils::threshold(
        utils::map<int8_t>(val, vmin, vmax, 0, vmax),
        thresh);
}

}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_HELPERS_MISC_H_
