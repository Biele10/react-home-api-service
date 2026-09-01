<?php

namespace Samaritan\transport;

final Class Packet
{
    // non-decoded values
    private int $_header = \Samaritan\arduino\Protocol::HEADER_BYTE; // indicates start of packet
    private int $_command;
    private int $_length = 0;    // how many bytes of payload there are
    private array $_parameters;

    // encoded values
    private string $_eHeader;
    private string $_eCommand;
    private string $_eLength;
    private string $_ePayload;
    private string $_eChecksum;
    
    private string $_packet = ''; // actual packet to be used

    public function __construct(int $command, array $params = []) // creates complete binary packet
    {
        $this->_command = $command;
        $this->_parameters = $params;
        $this->_encode();
    }

    public function getData()
    {
        return $this->_packet;
    }

    private function _encode() : void
    {
        $this->_eHeader = pack(\Samaritan\arduino\Protocol::U8INT_FORMAT, $this->_header);
        $this->_eCommand = pack(\Samaritan\arduino\Protocol::U16INT_FORMAT, $this->_command);

        $this->_ePayload = '';
        if (!empty($this->parameters))
        {
            $this->_ePayload = $this->_encodeParameters();
        }

        $this->_setPayloadLength();

        $packet = $this->_eHeader .
                  $this->_eLength .
                  $this->_eCommand .
                  $this->_ePayload;

        
        $this->_setChecksum($packet);
        $packet .= $this->_eChecksum;

        $this->_packet = $packet;     // final packet data that will be sent to device
    }

    private function _encodeParameters() : string
    {
        $encodedValues = '';
        foreach($this->_parameters as $param)
        {
            $byteMultiplier = 1;    // if int, then 2 bytes is final, but string may use more so we need to adjust length accordingly
            if (\is_int($param))
            {
                if ($param < 0 || $param > \Samaritan\arduino\Protocol::U16INT_LIMIT)
                {
                    throw new \Exception('Integer parameter cannot be greater than 65,535!');
                }
            }

            if (\is_string($param))
            {
                // add logic for a string later
                continue;
            }

            // each param always costs 2 bytes
            $encodedValues .= pack(\Samaritan\arduino\Protocol::U16INT_FORMAT, $param);
            $this->_length += (\Samaritan\arduino\Protocol::PARAMETER_BYTE_SIZE * $byteMultiplier);
        }

        return $encodedValues;
    }

    private function _setPayloadLength()
    {
        if ($this->_length > 255)
        {
            // we can't have length be greater than one byte for now
            throw new \Exception('Length cannot be greater than 1 byte!');
        }

        $this->_eLength = pack(\Samaritan\arduino\Protocol::U8INT_FORMAT, $this->_length);
    }

    private function _setChecksum(string $packet)
    {
        $this->_eChecksum = pack(\Samaritan\arduino\Protocol::U16INT_FORMAT, 
                                \Samaritan\encoder\CRC16::calculate($packet));
    }
}