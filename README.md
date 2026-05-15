# HomeAPI Project

This project incorporates web development and embedded engineering in order to build a website which will allow for people at home to interact with hardware.
The server is run on a Raspberry Pi, this is connected to an Arduino UNO R3 which is connected to a breadboard with hardware attached.

# Frontend

This is built using ReactJS, I have created multiple classes which can later be reused, however for now the website is just one static page.
All React code is in the [src](./src/) folder.

The [crud.js](./src/api/crud.js) file is what takes inputs from the frontend and then sends to the backend, this is the frontend handler for sending
and receiving information from the backend.

# Backend

This is built using raw PHP which is comprised of a variety of classes which relate to different pieces of hardware which will store the related methods.
All PHP code is stored in the [code](./backend/code/) folder.

In order to send data to the Arduino, PHP receives the requests from the JavaScript frontend and passes them to a Python flask server which is also being
run on the Pi, the code for the Python is stored in [arduino.py](./backend/code/arduino/python-api/arduino.py).

Python has its own serial library which allows for direct communication with the arduino, allowing for PHP requests to be sent to Python and then passed directly
to the Arduino.

# Embedded Code

This is built using C++, the code for this is stored in the [embedded-code](./backend/code/arduino/embedded-code/) folder.
I have created my own custom [hash table](./backend/code/arduino/embedded-code/src/utilities/HashStruct.cpp) structure which is used to store multiple parameters 
in an array-like structure with O(1) lookups, improving efficiency.

I have also created a custom parameter [parser](./backend/code/arduino/embedded-code/src/utilities/parser.cpp) that takes inputs from Python and parses them and stores 
them correctly in the hash table. 

Commands are expected to be passed in this format:  module=Led&method=power. The parser seperate key and value by the = and determines the next key by &.

The main program flow is all handled via the [ArduinoController](./backend/code/arduino/embedded-code/src/hardware/ArduinoController.cpp) class which correclty sends
data to the right modules.

As of right now the Arduino is linked to two pieces of hardware, a red LED and the onboard LED. In the next version I plan to introduce an ultrasonic sensor.