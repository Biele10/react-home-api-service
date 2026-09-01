#pragma once
#include "Arduino.h"

// this is what data is stored in once packet has been parsed
struct ParsedPacket
{
    const uint16_t command;
    uint16_t* args;
    uint8_t count;
};

constexpr uint8_t HEADER_BYTE = 0xAA;
constexpr uint8_t TOTAL_PACKET_SIZE_WO_PAYLOAD = 6; // header = 1 byte, length = 1 byte, command = 2 bytes, payload = n bytes (we dont know yet), checksum = 2 bytes
constexpr uint16_t BUFFER_SIZE = 256; // used to read all bytes into one array