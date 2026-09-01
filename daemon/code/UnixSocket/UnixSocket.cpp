#include "UnixSocket.hpp"

#include <iostream>
#include <cstring>

bool UnixSocket::setup()
{
    // Remove an old socket file if one exists.
    unlink(socketPath);

    // Create the Unix Domain Socket.
    serverSocket = socket(
        AF_UNIX,
        SOCK_STREAM,
        0
    );

    if (serverSocket == -1)
    {
        std::cerr << "Failed to create Unix socket\n";
        return false;
    }

    // Create the socket address structure.
    sockaddr_un address{};

    // Tell Linux this is a Unix Domain Socket address.
    address.sun_family = AF_UNIX;

    // Put our socket path into the address structure.
    std::strncpy(
        address.sun_path,
        socketPath,
        sizeof(address.sun_path) - 1
    );

    // Bind the socket to /tmp/home-api.sock.
    if (bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&address),
        sizeof(address)
    ) == -1)
    {
        std::cerr << "Failed to bind Unix socket\n";

        close(serverSocket);
        serverSocket = -1;

        return false;
    }

    // Tell Linux that this socket should accept connections.
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Failed to listen on Unix socket\n";

        close(serverSocket);
        serverSocket = -1;

        unlink(socketPath);
        return false;
    }

    std::cout << "Unix socket listening on "
              << socketPath
              << "\n";

    return true;
}

int UnixSocket::acceptClient()
{
    return accept(
        serverSocket,
        nullptr,
        nullptr
    );
}

ssize_t UnixSocket::receive(
    int clientSocket,
    char* buffer,
    std::size_t bufferSize
)
{
    return recv(
        clientSocket,
        buffer,
        bufferSize,
        0
    );
}

ssize_t UnixSocket::send(
    int clientSocket,
    const char* data,
    std::size_t dataSize
)
{
    return write(
        clientSocket,
        data,
        dataSize
    );
}

void UnixSocket::closeClient(int clientSocket)
{
    close(clientSocket);
}

void UnixSocket::shutdown()
{
    if (serverSocket != -1)
    {
        close(serverSocket);
        serverSocket = -1;
    }

    // Remove the socket file.
    unlink(socketPath);
}