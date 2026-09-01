<?php

namespace Samaritan\transport;

interface TransportInterface
{
    public function send(\Samaritan\transport\Packet $packet): void;
}