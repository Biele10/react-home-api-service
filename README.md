# Samaritan

## Short Message From Developer

This project has been written **90% by hand**, with occassional functions being written by AI (stuff like CRC algorithms for checksum). In an age where speed is prioritised over learning and overcoming obstacles, I wanted to ensure that if someone asked me what any line of code did in this project, I could tell them straight away. I have already learnt a great deal about software engineering and architecture through this project, in web development and embedded engineering. I hope that anyone who stumbles upon this might also just take the time to appreciate the importance of learning through failure.

I named this program Samaritan because it is intended to be helpful, like the good Samaritan... and also partially because of Person of Interest ;).

The rest of the README was written by AI, as I found that it would explain things far better than I could in a way that was understandable. As you can see, I am not opposed to AI, I simply know its place.

Happy learning.

## Samaritan

Samaritan is a home automation project combining web development and embedded engineering to allow hardware connected to an Arduino to be controlled through a web interface.

The system runs on a **Raspberry Pi**, which acts as the server and communicates with an **Arduino UNO R3**. The Arduino is connected to various hardware components on a breadboard.

The overall communication flow is:
```text
+----------------+       HTTP       +----------------+    Unix Socket    +----------------+     Serial     +----------------+
| React Frontend | ---------------> |    PHP API     | ----------------> | C++ Daemon     | ------------> | Arduino UNO R3 |
|                |                  |   FastRoute    |                   | Raspberry Pi   |                |                |
+----------------+                  +----------------+                   +----------------+                +----------------+
                                                                                                                    |
                                                                                                                    v
                                                                                                               +----------+
                                                                                                               | Hardware |
                                                                                                               +----------+
```

## Setup & Deployment

Samaritan is designed to be **quick and easy to set up**, with the installation and deployment process handled almost entirely by scripts.

### Requirements

The Raspberry Pi is expected to already be:

- Connected to the network
- Running a basic Raspberry Pi server installation
- Accessible over SSH

No Samaritan software needs to be installed on the Raspberry Pi beforehand. The installation script will install and configure everything required by Samaritan.

The **Arduino UNO R3 must be connected to the Raspberry Pi via USB during installation**. This allows the installer to detect the Arduino and configure the required serial connection automatically.

### Installation

On a new development machine, clone the repository and run [install.bat](./scripts/install.bat):

```bash
scripts/install.bat
```

The installer will:

- Check and install the required development tools
- Prepare the Raspberry Pi with the required software
- Configure Apache and the Samaritan daemon
- Configure the required permissions and services
- Detect the connected Arduino
- Configure the Arduino serial connection

Once installation is complete, the Raspberry Pi is ready to run Samaritan.

### Deployment

Deploying a new version is as simple as running [deploy.bat](./scripts/deploy.bat):

```bash
scripts/deploy.bat
```

This automatically:

- Builds the React frontend
- Installs and prepares the PHP backend
- Compiles the Arduino firmware
- Builds the C++ daemon
- Uploads everything to the Raspberry Pi
- Uploads the firmware to the Arduino
- Restarts the required services

After the initial setup, **deploying Samaritan should require little more than running one script**.

Simply open your web browser to your Raspberry Pi IP on your network e.g. 192.168.1.88 and you should see the Samaritan homepage.

## Frontend

The frontend is built using **ReactJS**.

All React code is contained in the [`src`](./src/) directory.

The [`crud.js`](./src/api/crud.js) file provides the interface between the frontend and the PHP API. It is responsible for sending HTTP requests and handling responses from the backend.

The frontend communicates with the PHP API rather than communicating directly with the Arduino.

## Backend

The backend is written in **PHP** and is responsible for providing the HTTP API used by the frontend.

All PHP application code is stored in [`backend/code`](./backend/code/).

### HTTP Routing

API routes are handled using **FastRoute**. FastRoute determines which endpoint should handle an incoming HTTP request based on its HTTP method and URL.

For example:

```text
PUT /hardware/redLed/power
```

is matched to the appropriate PHP [handler](./backend/code/controllers/hardware/led/LedController.php).

This keeps HTTP routing separate from the code responsible for communicating with the Arduino.

### Adding a PHP Endpoint

PHP endpoints are registered using **FastRoute**.

To add a new endpoint:

1. **Define the route** in the appropriate routes file in the [routes](./backend/code/routes/) directory.
2. **Create the controller** for the request in the [controllers](./backend/code/controllers/) directory.
3. **Create the actual function** you want to write in the [services](./backend/code/services/) directory.
4. If the endpoint communicates with the Arduino, have the handler send the appropriate command through the daemon.

For example:

```php
$dispatcher->addRoute(
    'PUT',
    '/hardware/redLed/power',
    function () {
        // Handle request
    }
);
```

Keep the HTTP route responsible for handling the web request, while Arduino-specific communication should remain separate from the HTTP routing logic.


### Arduino Communication

PHP does not communicate directly with the Arduino.

Instead, requests that require hardware interaction are sent to a **daemon running on the Raspberry Pi**. PHP communicates with this daemon through a **Unix domain socket**.

The daemon is responsible for communicating with the Arduino over its serial connection.

This separation means that the PHP API does not need to manage the Arduino's serial connection itself.

The communication flow is therefore:

```text
React
  │
  │ HTTP
  ▼
PHP / FastRoute
  │
  │ Unix socket
  ▼
Raspberry Pi daemon
  │
  │ Serial
  ▼
Arduino
```

## Embedded Code

The Arduino software is written in **C++** and is stored in [`backend/code/arduino/embedded-code`](./backend/code/arduino/embedded-code/).

The embedded application is responsible for:

* Receiving and validating binary packets.
* Extracting the command and payload.
* Dispatching commands to the correct hardware method.
* Managing the connected hardware.

### ArduinoController

[`ArduinoController`](./backend/code/arduino/embedded-code/src/hardware/ArduinoController.cpp) manages the hardware connected to the Arduino.

Hardware objects are stored as private attributes of `ArduinoController` and are created in its constructor.

For example:

```cpp
class ArduinoController
{
public:
    ArduinoController(int redLedPin);

    Led& getRedLed();

private:
    Led redLed;
};
```

Hardware can then be accessed elsewhere through its getter.

`setupHardware()` is responsible for Arduino-specific hardware configuration such as `pinMode()`.

This keeps hardware ownership and configuration in one place.

### CommandDispatcher

The [`CommandDispatcher`](./backend/code/arduino/embedded-code/src/) is responsible for mapping incoming commands to hardware methods.

Endpoints are registered using the templated `registerEndpoint()` function:

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```

This associates:

```text
RED_LED_POWER
      │
      ▼
ArduinoController::getRedLed()
      │
      ▼
Led::power()
```

The endpoint system uses a common base endpoint type while allowing each endpoint to retain the type information required to call its specific hardware method.

This allows different hardware classes to be registered in the same endpoint table without requiring every hardware class to inherit from a common hardware interface.

### Endpoint Commands

Each endpoint is assigned a unique **2-byte command**.

Commands are defined in [`Endpoints.hpp`](./backend/code/arduino/embedded-code/src/).

For example:

```cpp
constexpr uint16_t RED_LED_POWER 0x0003
```

The command acts as the identifier used by the Arduino to determine which endpoint should be executed.

Commands must be unique and must not overlap with existing commands.

## Hash Table

A custom [`HashTable`](./backend/code/arduino/embedded-code/src/utilities/HashTable.hpp) is used by the embedded endpoint system to store and retrieve registered endpoints.

The command is used as the key, allowing the dispatcher to locate an endpoint efficiently without requiring a long chain of conditional statements.

Conceptually:

```text
Command
   │
   ▼
Hash Table
   │
   ▼
Endpoint
   │
   ▼
Hardware method
```

For example:

```text
0x0003
  │
  ▼
RED_LED_POWER
  │
  ▼
Led::power()
```

The hash table is particularly useful on the Arduino because the endpoint lookup needs to be lightweight and predictable.

## Packets

Communication between the Raspberry Pi daemon and the Arduino uses **binary packets**.

The packet structure is:

```text
+--------+--------+---------+---------+----------+
| HEADER | LENGTH | COMMAND | PAYLOAD | CHECKSUM |
+--------+--------+---------+---------+----------+
| 1 byte | 1 byte | 2 bytes | N bytes | 2 bytes  |
+--------+--------+---------+---------+----------+
```

For example:

```text
+----+--------+---------+-------------+----------+
| AA |   03   |  01 03  |  01 F4 03  | CHECKSUM |
+----+--------+---------+-------------+----------+
|    |        |         |             |          |
|    |        |         |             |          |
+----+--------+---------+-------------+----------+
```

Header Length  Command     Payload      Checksum

The **command** identifies the endpoint that should be executed, while the payload contains any data required by that endpoint.

The Arduino validates the packet before passing the command to the `CommandDispatcher`.

## Adding an Endpoint

For instructions on adding a new endpoint, see **[Adding an Endpoint](./backend/code/arduino/embedded-code/README.md)**.

In general, the process is:

1. Assign a unique 2-byte command in `Endpoints.hpp`.
2. Add and configure new hardware in `ArduinoController` if required.
3. Add a getter for the hardware.
4. Register the endpoint in `CommandDispatcher`.

For example:

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```