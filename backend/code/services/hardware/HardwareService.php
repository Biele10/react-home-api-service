<?php

namespace Samaritan\services\hardware;


// base hardware class that contains functions other components may use often

abstract Class HardwareService extends \Samaritan\services\Service
{
    protected ?int $pin;
    private \Samaritan\transport\TransportInterface $transportInterface;

    public function __construct()
    {
        $this->transportInterface = new \Samaritan\transport\UnixSocketTransport(\Samaritan\arduino\Protocol::UNIX_SOCKET_PATH);
    }

    public function getPin(): int
    {
        return $this->pin;
    }

    final protected function sendCommand(string $command, array $params = []): ?array
    {
        $packet = new \Samaritan\transport\Packet($command, $params);

        $this->transportInterface->send($packet);
        return ['success' => true];     // true for now until we get Arudino to send data back to server
    }

    /**
     * Takes associative array of parameters and parses into a string
     * @param array $params
     * @return void
     */
    private function _parseParams(array $params) : string
    {
        // add logic so if error, just return "" instead
        return "TEMP";
    }
}