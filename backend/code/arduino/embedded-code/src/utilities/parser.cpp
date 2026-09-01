#include <Arduino.h>
#include "config/config.hpp"
#include "utilities/errorHandler.hpp"
#include "utilities/parser.hpp"
#include "packet/Packet.hpp"

ParsedPacket* parsePacket(uint8_t (&buffer)[BUFFER_SIZE])
{

  uint16_t packetLength = TOTAL_PACKET_SIZE_WO_PAYLOAD + buffer[1];
  if (!validateCRC(buffer, packetLength))
  {
    return nullptr;
  }

  uint16_t command = (static_cast<uint16_t>(buffer[2]) << 8) | buffer[3]; // combines two bytes to form command, this is sort of like a low-level version of concatenation!

  uint8_t payloadLength = buffer[1];

  if (payloadLength % 2 != 0) // our protocol states that each arg is two bytes, enforce this
  {
      return nullptr;
  }

  uint8_t count = payloadLength / 2; // 2 bytes per index value, so we divide by 2 to loop through what we need

  uint16_t* args = nullptr;
  if (count > 0) // we have parameters, so we add them
  {
    args = new uint16_t[count]; // creates args array on heap, this is deleted in cleanUp function
    for (uint8_t i = 0; i < count; i++)
    {
        uint8_t index = 4 + (i * 2); // need to skip header, count and command bytes
        args[i] = (static_cast<uint16_t>(buffer[index]) << 8) | buffer[index + 1];
        // Combines two bytes into one uint16_t. The first byte is shifted left 8 bits,
        // e.g. 00000001 << 8 = 00000001 00000000. The second byte is then OR'd with
        // it: 00000001 00000000 | 00000000 11110100 = 00000001 11110100 (0x01F4).
        // Because the second byte occupies the lower 8 bits, OR simply adds it without
        // changing the upper 8 bits.
    }
  }

   ParsedPacket* parsedPacket = new ParsedPacket {command, args, count};
   return parsedPacket;
}

bool processByte(uint8_t byte, uint8_t (&buffer)[BUFFER_SIZE], uint16_t& bufferIndex, bool& packetStarted)
{
  if (!packetStarted)
  {
      // We aren't currently reading a packet.
      // Therefore, ignore everything until we receive the header.
      if (byte != HEADER_BYTE)
      {
        return false;
      }

      packetStarted = true;
      bufferIndex = 0;
  }

  // Don't write beyond the end of the buffer.
  if (bufferIndex >= BUFFER_SIZE)
  {
      bufferIndex = 0;
      packetStarted = false;
      return false;
  }

  buffer[bufferIndex++] = byte;

  if (bufferIndex >= 2)
  {
      // Once we have the length byte, we can determine
      // how large the complete packet should be.
      if (bufferIndex == 2)
      {
          uint16_t packetLength = static_cast<uint16_t>(TOTAL_PACKET_SIZE_WO_PAYLOAD) + buffer[1];
          if (packetLength > BUFFER_SIZE)
          {
              bufferIndex = 0;
              packetStarted = false;
              return false;
          }
      }

      uint16_t packetLength = static_cast<uint16_t>(TOTAL_PACKET_SIZE_WO_PAYLOAD) + buffer[1];

      if (bufferIndex == packetLength)
      {
        packetStarted = false;
        return true; // we have constructed full packet, we can now pass buffer into the parser
      }
  }
  
  return false;
}

/**
 * Checksum algorithm to validate packet.
 */
bool validateCRC(const uint8_t* data, uint16_t length)
{
    uint16_t crc = 0xFFFF;

    for (uint16_t i = 0; i < length - 2; i++)
    {
        crc ^= static_cast<uint16_t>(data[i]) << 8;

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }

    uint16_t receivedCRC =
        (static_cast<uint16_t>(data[length - 2]) << 8) |
        data[length - 1];

    return crc == receivedCRC;
}

void cleanUp(ParsedPacket* packet)
{
  delete[] packet->args; // this was allocated earlier on heap, so we must destroy to avoid leaks
  delete packet;
}