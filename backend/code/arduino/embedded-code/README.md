## Adding an Endpoint

Adding an endpoint is a simple three-step process.

### 1. Add a unique command

Define a unique 2-byte command in [Endpoints.hpp](./include/Endpoints.hpp).

```cpp
constexpr uint16_t RED_LED_POWER = 0x0003;
```

Make sure the command does not overlap with an existing endpoint.

### 2. Add/configure the hardware

If the endpoint uses **existing hardware**, skip this step.

If new hardware is required:

* Add the hardware object as a **private attribute** of [ArduinoController](./include/controller/ArduinoController.hpp).
* Initialise it in the [ArduinoController](./src/hardware/ArduinoController.cpp) constructor, passing any required configuration such as a pin number.
* Configure the hardware in `setupHardware()` (`pinMode()`, etc.).
* Add a getter using the `get{HardwareItem}()` convention.

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

```cpp
ArduinoController::ArduinoController(int redLedPin)
    : redLed(redLedPin)
{
}
```

The hardware object should be stored on `ArduinoController` so the same instance can be accessed elsewhere through its getter.

### 3. Register the endpoint

In [CommandDispatcher.cpp](./src/structures/hashTables/CommandDispatcher.cpp), inside `setup()`, register the command with the hardware object and method:

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```

**Every endpoint function MUST use the following signature:**

```cpp
Result functionName(const uint16_t* args, uint8_t count);
```

For example:

```cpp
Result Led::power(const uint16_t* args, uint8_t count)
{
    // ...
}
```

Even if the endpoint does not require any arguments, the function must still use this signature. In that case, `count` will indicate the number of arguments provided and `args` can be ignored.

The general registration format is:

```cpp
registerEndpoint(COMMAND, ac.getHardwareObj(), &HardwareClass::method);
```

### Checklist

* [ ] Unique command added to `Endpoints.hpp`
* [ ] New hardware added to `ArduinoController` (if required)
* [ ] Hardware initialised in the constructor
* [ ] Hardware configured in `setupHardware()`
* [ ] Getter added
* [ ] Endpoint uses the required `Result functionName(const uint16_t* args, uint8_t count)` signature
* [ ] Endpoint registered in `CommandDispatcher.cpp`








## FULL EXPLANATION OF PROCESS

## Adding a New Endpoint

Adding a new endpoint involves three main steps:

1. Assign a unique command.
2. Add/configure the required hardware in `ArduinoController` (if necessary).
3. Register the hardware method as an endpoint in `CommandDispatcher`.

### 1. Assign a unique command

Every endpoint must have a unique **2-byte binary command**. Commands are defined in:

`Endpoints.hpp`

For example, the `power()` function for the red LED uses:

```cpp
constexpr uint16_t RED_LED_POWER 0x0003
```

When adding a new endpoint, make sure the command does **not overlap with an existing command**.

For example:

```cpp
constexpr uint16_t RED_LED_POWER 0x0003
constexpr uint16_t RED_LED_BRIGHTNESS 0x0004
```

The command is what the Arduino receives to identify which endpoint should be executed.

---

### 2. Add the hardware to `ArduinoController`

If the endpoint requires a new piece of hardware, the hardware object must be added to `ArduinoController`.

Hardware objects are created **directly in the `ArduinoController` constructor**. Any required configuration, such as a pin number, should be passed into the constructor.

For example:

```cpp
class ArduinoController
{
public:
    void setupHardware();

    ArduinoController(int redLedPin);

    Led& getRedLed();
    OnboardLed& getOnBoardLed();

private:
    Led redLed;
    OnboardLed onboardLed;
};
```

The hardware object is then initialised in the constructor:

```cpp
ArduinoController::ArduinoController(int redLedPin)
    : redLed(redLedPin), onboardLed()
{
}
```

If adding another piece of hardware, add it as a **private attribute** and initialise it in the constructor.

For example:

```cpp
private:
    Led redLed;
    OnboardLed onboardLed;
    UltrasonicSensor ultrasonicSensor;
```

Then initialise it:

```cpp
ArduinoController::ArduinoController(int redLedPin, int ultrasonicPin)
    : redLed(redLedPin),
      onboardLed(),
      ultrasonicSensor(ultrasonicPin)
{
}
```

> **Important:** Hardware objects must be stored as private attributes of `ArduinoController`. This allows the same hardware object to be accessed elsewhere through its getter rather than creating multiple instances of the hardware.

---

### 3. Configure the hardware in `setupHardware()`

Any Arduino-specific hardware setup, such as `pinMode()`, should be performed in `setupHardware()`.

For example:

```cpp
void ArduinoController::setupHardware()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(Config::RED_LED_PIN, OUTPUT);
}
```

If the new hardware requires configuration, add it here.

For example:

```cpp
void ArduinoController::setupHardware()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(Config::RED_LED_PIN, OUTPUT);
    pinMode(Config::ULTRASONIC_PIN, INPUT);
}
```

---

### 4. Add a getter for the hardware

A getter must be provided so that the hardware object can be accessed by the endpoint dispatcher.

The naming convention is:

```text
get{HardwareItem}()
```

For example:

```cpp
Led& ArduinoController::getRedLed()
{
    return this->redLed;
}
```

For an ultrasonic sensor:

```cpp
UltrasonicSensor& ArduinoController::getUltrasonicSensor()
{
    return this->ultrasonicSensor;
}
```

The getter should return a **reference to the existing object** rather than creating or returning a new object.

---

### 5. Register the endpoint

Finally, register the endpoint in:

`CommandDispatcher.cpp`

inside the `setup()` function.

For example:

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```

This connects the command `RED_LED_POWER` to the `power()` method of the red LED.

The general format is:

```cpp
registerEndpoint(COMMAND, ac.getHardware(), &HardwareClass::method);
```

For example:

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```

This means:

> When the command `RED_LED_POWER` is received, call `Led::power()` on the red LED object managed by `ArduinoController`.

---

## Quick Checklist

When adding an endpoint, follow this checklist:

* [ ] Choose a unique 2-byte command.
* [ ] Add the command to `Endpoints.hpp`.
* [ ] If new hardware is required:

  * [ ] Add the hardware object as a **private attribute** of `ArduinoController`.
  * [ ] Add any required constructor parameters.
  * [ ] Initialise the hardware object in the `ArduinoController` constructor.
  * [ ] Configure the hardware in `setupHardware()`.
  * [ ] Add a `get{HardwareItem}()` getter.
* [ ] Register the endpoint in `CommandDispatcher.cpp`:

```cpp
registerEndpoint(COMMAND, ac.getHardware(), &HardwareClass::method);
```

### Example

Adding the red LED's `power()` function as an endpoint requires:

**`Endpoints.hpp`**

```cpp
constexpr uint16_t RED_LED_POWER 0x0003
```

**`ArduinoController.hpp`**

```cpp
Led& getRedLed();

private:
    Led redLed;
```

**`ArduinoController.cpp`**

```cpp
ArduinoController::ArduinoController(int redLedPin)
    : redLed(redLedPin), onboardLed()
{
}

Led& ArduinoController::getRedLed()
{
    return this->redLed;
}
```

**`CommandDispatcher.cpp`**

```cpp
registerEndpoint(RED_LED_POWER, ac.getRedLed(), &Led::power);
```

That's all that is required to expose the method as an endpoint.