#include <Arduino.h>
#include "hardware-components/UltrasonicSensor.hpp"
#include "output/Result.hpp"
#include "structures/HashTable.hpp"
#include "config/config.hpp"
#include "HCSR04.h"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) : us(trigPin, echoPin), lastRead(0) {};

/**
 * Function that returns the distance of the echo
 * in centimetres.
 */
size_t UltrasonicSensor::getDistance()
{
    return this->us.dist();
}

/**
 * Function that determines whether or not to allow
 * the ultrasonic sensor to send an echo.
 */
bool UltrasonicSensor::doEcho()
{
    if ((millis() - this->lastRead) >= this->MINIMUM_ECHO_WAIT)      // check to see if ultrasonic sensor should be sent an instruction
    {
        this->lastRead = millis();
        return true;
    }

    return false;
}

/**
 * Function that is used to detect movement from a given distance.
 */
MovementResult UltrasonicSensor::movementCheck(size_t avgDistance)
{
    if (!this->doEcho())
    {
        return WAITING;
    }

    size_t curAvgDistance = this->getAvgDistance();      // variable that will store the average distance the sensor is returning
    int diff = (int)avgDistance - (int)curAvgDistance;
    if (abs(diff) > this->MOVEMENT_THRESHOLD)       // detects distance change of increase or decrease
    {
        return MOVEMENT;        // movement detected
    }

    return NO_MOVEMENT;
}

size_t UltrasonicSensor::getAvgDistance()
{
    size_t curAvgDistance = 0;
    size_t avgCount = 0;

    for (size_t i = 0; i < this->READS_FOR_AVG_DIST_COUNT; i++)
    {
        size_t dist = this->getDistance();

        if (dist > this->MIN_DIST_BOUNDARY && dist < this->MAX_DIST_BOUNDARY)
        {
            curAvgDistance += dist;
            avgCount++;
        }

        delay(50);
    }

    if (avgCount == 0)
    {
        return 0;
    }

    return curAvgDistance / avgCount;
}