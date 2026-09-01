#include "ArduinoSerial.hpp"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>


bool ArduinoSerial::setup()
{
    // Open the Arduino serial device.
    serial = open(
        serialPath,
        O_RDWR | O_NOCTTY
    );

    if (serial == -1)
    {
        std::cerr << "Failed to open Arduino serial device\n";
        return false;
    }

    // Get the current serial configuration.
    termios settings{};

    if (tcgetattr(serial, &settings) == -1)
    {
        std::cerr << "Failed to get serial settings\n";

        close(serial);
        serial = -1;

        return false;
    }

    // Set baud rate to 9600.
    cfsetispeed(&settings, B9600);
    cfsetospeed(&settings, B9600);

    // 8 data bits.
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8;

    // No parity.
    settings.c_cflag &= ~PARENB;

    // One stop bit.
    settings.c_cflag &= ~CSTOPB;

    // Enable receiver.
    settings.c_cflag |= CREAD;

    // Tell Linux that this is a local connection.
    settings.c_cflag |= CLOCAL;

    // Apply the settings immediately.
    if (tcsetattr(
        serial,
        TCSANOW,
        &settings
    ) == -1)
    {
        std::cerr << "Failed to configure serial device\n";
        close(serial);

        serial = -1;
        return false;
    }

    std::cout << "Arduino serial connection established\n";
    return true;
}

ssize_t ArduinoSerial::send(
    const char* data,
    std::size_t dataSize
)
{
    std::cout << "Sending to Arduino: ";

    for (std::size_t i = 0; i < dataSize; i++)
    { // outputs the packet data being transmitted
        std::cout << std::hex
            << static_cast<unsigned int>(
                    static_cast<unsigned char>(data[i])
                )
            << " ";
    }

    std::cout << std::dec << "\n";
    
    return write(
        serial,
        data,
        dataSize
    );
}

ssize_t ArduinoSerial::receive(
    char* buffer,
    std::size_t bufferSize
)
{
    return read(
        serial,
        buffer,
        bufferSize
    );
}

void ArduinoSerial::shutdown()
{
    if (serial != -1)
    {
        close(serial);
        serial = -1;
    }
}