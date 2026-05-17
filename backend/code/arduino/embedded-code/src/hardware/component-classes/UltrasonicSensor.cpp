#include <Arduino.h>
#include "hardware-components/UltrasonicSensor.hpp"
#include "output/Result.hpp"
#include "structures/HashTable.hpp"
#include "config/config.hpp"
#include "HCSR04.h"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) : us(trigPin, echoPin), lastRead(0) {};

/**
 * Handles all functions in relation to the ultrasonic sensor.
 */
Result UltrasonicSensor::handler(HashTable* command_and_params)
{
    String method = command_and_params->getValue("method");

    return Result::Error(ErrorCode::INVALID_COMMAND, "No such method found.");
}

/**
 * Function that returns the distance of the echo
 * in centimetres.
 */
size_t UltrasonicSensor::getDistance()
{
    return this->us.dist();
}