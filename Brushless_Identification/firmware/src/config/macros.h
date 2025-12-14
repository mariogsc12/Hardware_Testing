/* ----------------------------------------------------------------- */
/* ----------------------- MACRO DEFINITIONS ----------------------- */

#ifndef MACROS_H
#define MACROS_H

#include <iostream>

#define ASSERT_RANGE(value, min, max)                                                   \
    do {                                                                                \
        if ((value) < (min) || (value) > (max)) {                                       \
            std::cerr << "Assertion failed: (" #value " in range ["                     \
                      << #min << ", " << #max << "]), "                                 \
                      << "actual value: " << (value)                                    \
                      << " (file: " << __FILE__ << ", line: " << __LINE__ << ")\n";     \
            return;                                                                     \
        }                                                                               \
    } while (0)


#define ASSERT_RANGE_RETURN(value, min, max, retValue)                                  \
    do {                                                                                \
        if ((value) < (min) || (value) > (max)) {                                       \
            std::cerr << "Assertion failed: (" #value " in range ["                     \
                      << #min << ", " << #max << "]), "                                 \
                      << "actual value: " << (value)                                    \
                      << " (file: " << __FILE__ << ", line: " << __LINE__ << ")\n";     \
            return retValue;                                                            \
        }                                                                               \
    } while (0)


#define ASSERT_NULL(ptr)                                                                \
    do {                                                                                \
        if ((ptr) == nullptr) {                                                         \
            std::cerr << "Assertion failed: Pointer " #ptr " is null "                  \
                      << "(file: " << __FILE__ << ", line: " << __LINE__ << ")\n";      \
            return;                                                                     \
        }                                                                               \
    } while (0)




#endif