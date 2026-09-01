#pragma once
#include <Arduino.h>
#include "structures/HashTable.hpp"
#include "packet/Packet.hpp"

ParsedPacket* parsePacket(uint8_t (&buffer)[BUFFER_SIZE]);
void arrayExpander(String*& inputArray, size_t& originalSize);
bool processByte(uint8_t byte, uint8_t (&buffer)[BUFFER_SIZE], uint16_t& bufferIndex, bool& packetStarted);
bool validateCRC(const uint8_t* data, uint16_t length);
void cleanUp(ParsedPacket* packet);