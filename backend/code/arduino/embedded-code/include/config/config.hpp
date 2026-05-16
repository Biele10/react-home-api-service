#pragma once
#include <Arduino.h>

namespace Config
{
    constexpr int RED_LED_PIN = 11;
    constexpr int GREEN_LED_PIN = 3;
    constexpr int US_TRIG_PIN = 9;
    constexpr int US_ECHO_PIN = 10;
    constexpr size_t BASE_ARRAY_SIZE = 10;
    constexpr size_t DEFAULT_ARRAY_ADDITION = 5;       // default amount to increase an array size by
    constexpr size_t BASE_HASH_TABLE_SIZE = 10;
}

namespace ErrorCode
{
    enum Code : uint8_t
    {
        NONE = 0,
        INVALID_MODULE = 1,
        MODULE_NOT_EXIST = 2,
        INVALID_COMMAND = 3,
        INVALID_PIN = 4,
        HARDWARE_FAILURE = 5
    };
}