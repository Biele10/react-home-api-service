#include "UnixSocket/UnixSocket.hpp"
#include "ArduinoSerial/ArduinoSerial.hpp"

#include <iostream>


int main()
{
    UnixSocket server;
    ArduinoSerial arduino;

    // -------------------------
    // INITIAL SETUP
    // -------------------------

    if (!server.setup())
    {
        return 1;
    }

    if (!arduino.setup())
    {
        server.shutdown();
        return 1;
    }

    // -------------------------
    // MAIN DAEMON LOOP
    // -------------------------

    while (true)
    {
        std::cout << "Waiting for client...\n";

        int clientSocket = server.acceptClient();
        if (clientSocket == -1)
        {
            std::cerr << "Failed to accept client\n";
            continue;
        }

        std::cout << "Client connected\n";

        // Receive data from PHP.
        char buffer[1024];

        ssize_t bytesReceived = server.receive(
            clientSocket,
            buffer,
            sizeof(buffer)
        );

        if (bytesReceived <= 0)
        {
            std::cerr << "Client disconnected or receive failed\n";
            server.closeClient(clientSocket);
            continue;
        }

        // Show what we received.
        std::cout << "Received "
                  << bytesReceived
                  << " bytes from client\n";

        // Send exactly those bytes to the Arduino.
        ssize_t bytesSent = arduino.send(
            buffer,
            bytesReceived
        );

        if (bytesSent == -1)
        {
            std::cerr << "Failed to send data to Arduino\n";
            server.closeClient(clientSocket);
            continue;
        }


        std::cout << "Sent "
                  << bytesSent
                  << " bytes to Arduino\n";


        // For now, just send a simple response back to PHP.
        const char* response = "Command received";

        server.send(
            clientSocket,
            response,
            16
        );

        // We're finished with this PHP connection.
        server.closeClient(clientSocket);
    }


    // We won't actually reach this during normal operation,
    // because the daemon loop runs forever.

    arduino.shutdown();
    server.shutdown();

    return 0;
}