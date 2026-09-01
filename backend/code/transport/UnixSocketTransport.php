<?php

namespace Samaritan\transport;

final class UnixSocketTransport implements TransportInterface
{
    private \Socket $socket;
    private bool $isConnected = false;

    public function __construct(
        private readonly string $socketPath
    )
    {
        $this->_create();
        $this->_connect();
        $this->isConnected = true;
    }

    public function send(Packet $packet): void
    {
        if (!$this->isConnected)
        {
            return;
        }

        $this->_write($packet);
    }

    private function _create(): void
    {
        $socket = socket_create(
            AF_UNIX,
            SOCK_STREAM,
            0
        );

        if ($socket === false)
        {
            throw new \RuntimeException(
                socket_strerror(socket_last_error())
            );
        }

        $this->socket = $socket;
    }

    private function _connect(): void
    {
        if (!socket_connect(
            $this->socket,
            $this->socketPath
        ))
        {
            throw new \RuntimeException(
                socket_strerror(socket_last_error($this->socket))
            );
        }
    }

    private function _write(Packet $packet): void
    {
        $data = $packet->getData();
        $length = \strlen($data);
        $sent = 0;

        while ($sent < $length)
        {
            $result = socket_write(
                $this->socket,
                substr($data, $sent),
                $length - $sent
            );

            if ($result === false)
            {
                throw new \RuntimeException(
                    socket_strerror(socket_last_error($this->socket))
                );
            }

            $sent += $result;
        }
    }

    public function __destruct()
    {
        if ($this->isConnected)
        {
            socket_close($this->socket);
        }
    }
}