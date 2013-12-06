arduino-sensor-library
======================

This is a super lightweight general purpose sensing framework for the [Arduino](http://arduino.cc/) platform. The library supports timed actions (like periodically reading the value of an analog pin) even if the Arduino board is being duty cycled (put to sleep). Using this library makes it easy to run multiple sensing applications, which may need to *sense* at different intervals, on a single Arduino board without cramming all your sensors' code into a single messy sketch file full of hard coded timing constraints.

## Example Use Case
Let's say you'd like to build a mini Arduino-powered weather station to stick on your back porch and capture some weather data. Your weather station consists of an Arduino board and several pieces of sensing hardware to sense things like temperature, humudity, light level, wind speed, etc. Also, you'd really like to impress your friends, so you want your weather station to be solar powered.

Your application has several **constraints**. First, all of your application code will run on one board. Next, each sensor will probably capture a reading at a different interval (for example, there's no need to capture temperature as often as wind speed). Finally, you will probably want to duty cycle your board to conserve power.

Implementing this application poses some **challenges**. Putting all of your sensors' behavior in a single sketch file would almost certainly be ugly and difficult to maintain. Intertwining each sensors' timing would be complex. Duty cycling (powering down) your board resets the onboard timers making it difficult to maintain consistent timing intervals.

This library takes care of all of the above enabling you to juts focus on *what* each of your sensors needs to do and *how often*.

## Installing
Install the Sensor library like you would any other [Arduino library](http://arduino.cc/en/Guide/Libraries). Drop the `Sensor/` directory into your Arduino home `libraries/` directory.

## Usage
See the `FloorMatSensor` class included in this project as a usage example. The `FloorMatSensor` reads the values of 15 digital pins into a bit vector once every 60 seconds.

1. Extend the `Sensor` class for each required independent timed sensing action. 

2. Your subclass just needs to implement the following methods.
  - `void init()`: Contains everything that needs to run in your sketch's `setup()`.
  - `void run()`: Defines your sensor's periodic behavior (e.g., reading the values of 15 digital pins into a bit vector).

3. In your sketch...
  1. Include the `Sensor` baseclass: `#include <Sensor.h>`
  2. Include each of your subclasses: `#include <FloorMatSensor.h>`
  3. Instantiate each of your sensors:
    ```java
    /**
     *  The constructor parameters are:
     *  name, units, interval (ms), duration (ms), resolution (ms), callback, pseudo-timer
     */

    FloorMatSensor floormat = FloorMatSensor("floor-mat", "Integer", 60000, 10, 1, sensorCallback, NULL);
    ```
  4. Initialize each of your sensors:
    ```java
    void setup() {

      floormat.init();
      
    }
    ```
  5. Run each of your sensors:
    ```java
    void loop() {

      floormat.check();
      
    }
    ```
  6. Define a callback, which you may call from any of your sensor subclasses using `_callback()`:
    ```java
    void sensorCallback(String s) {

      Serial.print("Sensor value read: ");
      Serial.println(s);
      
    }
    ```
