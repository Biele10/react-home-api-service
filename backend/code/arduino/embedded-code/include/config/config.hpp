#pragma once
#include <Arduino.h>

namespace Config
{
    constexpr int RED_LED_PIN = 11;
    constexpr size_t BASE_ARRAY_SIZE = 10;
    constexpr size_t DEFAULT_ARRAY_ADDITION = 5;       // default amount to increase an array size by
    constexpr size_t BASE_HASH_TABLE_SIZE = 10;
}

namespace ErrorCode
{
    enum class Code : uint8_t
    {
        NONE = 0,
        INVALID_MODULE = 1,
        INVALID_COMMAND = 2,
        INVALID_PIN = 3,
        HARDWARE_FAILURE = 4
    };
}