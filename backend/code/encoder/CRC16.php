<?php

namespace Samaritan\encoder;

final class CRC16
{
    private const int _POLYNOMIAL = 0x1021;
    private const int _INITIAL_VALUE = 0xFFFF;

    public static function calculate(string $data): int
    {
        $crc = self::_INITIAL_VALUE;

        for ($i = 0; $i < \strlen($data); $i++)
        {
            // Add the current byte into the CRC register.
            $crc ^= \ord($data[$i]) << 8;

            // Process all 8 bits in this byte.
            for ($bit = 0; $bit < 8; $bit++)
            {
                if (($crc & 0x8000) !== 0)
                {
                    $crc = ($crc << 1) ^ self::_POLYNOMIAL;
                }
                else
                {
                    $crc <<= 1;
                }

                // Keep CRC at exactly 16 bits.
                $crc &= 0xFFFF;
            }
        }

        return $crc;    // return the final checksum
    }
}