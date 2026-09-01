#pragma once

#include "../config.hpp"
#include <cstddef>
#include <sys/types.h>

class ArduinoSerial
{
private:
    int serial = -1;
    const char* serialPath = SERIAL_PATH;

public:
    bool setup();
    ssize_t send(
        const char* data,
        std::size_t dataSize
    );
    ssize_t receive(
        char* buffer,
        std::size_t bufferSize
    );
    void shutdown();
};