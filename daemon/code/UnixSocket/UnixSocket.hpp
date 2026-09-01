#pragma once

#include "../config.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstddef>
#include <sys/types.h>

class UnixSocket
{
private:
    int serverSocket = -1;
    const char* socketPath = SOCKET_PATH;

public:
    bool setup();
    int acceptClient();
    ssize_t receive(
        int clientSocket,
        char* buffer,
        std::size_t bufferSize
    );
    ssize_t send(
        int clientSocket,
        const char* data,
        std::size_t dataSize
    );
    void closeClient(int clientSocket);
    void shutdown();
};