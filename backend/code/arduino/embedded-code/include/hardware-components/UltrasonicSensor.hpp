#pragma once
#include "structures/HashTable.hpp"
#include "output/Result.hpp"
#include "HCSR04.h"

class UltrasonicSensor
{
    public:
        UltrasonicSensor(int trigPin, int echoPin);
        Result handler(HashTable* command_and_params);       // function that handles what to do with user input
        size_t getDistance();
        unsigned long lastRead;     // the last time the ultrasonic sensor was read from, used to determine whether to send a signal or not

    private:
        HCSR04 us;
};