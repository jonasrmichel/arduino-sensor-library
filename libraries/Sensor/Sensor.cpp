/**
 * Sensor.cpp
 */

#include "Sensor.h"
#include <stlib.h>

/**
 * Constructors
 */
Sensor::Sensor(String name, String units, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime) {
  initialize(name, units, 0, 0, interval, duration, resolution, callback, pseudoTime);
}

void Sensor::initialize(String name, String units, unsigned long previousRun, unsigned long previousMeas, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime) {
  _active = true;
  _name = name;
  _units = units;
  _previousRun = previousRun;
  _previousMeas = previousMeas;
  _interval = interval;
  _duration = duration;
  _resolution = resolution;
  _callback = callback;
  _pseudoTime = pseudoTime;
}

/**
 * Returns a JSON String contianing the sensor's "registration"
 */
String Sensor::getRegistration() {
  String reg = String();
  reg += "{";
  
  // name
  reg += "\"source\":\"" + _name + "\",";
  
  // units
  reg += "\"units\":\"" + _units + "\"";
    
  reg += "}";
  
  return reg;
}

/**
 * Returns a JSON String containing a sensor reading
 */
String Sensor::getReading(String val) {
  String reading = String();
  
  reading += "{";
  
  // source (name)
  reading += "\"source\":\"" + _name + "\",";
  // value
  reading += "\"value\":" + val + ",";
  // units
  reading += "\"units\":\"" + _units + "\"";
  
  reading += "}";
  
  return reading;
}

/**
 * Timer methods
 */

void Sensor::disable() {
  _active = false;
}


void Sensor::enable() {
  _active = true;
}

int Sensor::check() {
  unsigned long t;
  if (_pseudoTime) {
    t = *_pseudoTime;
  } else {
    t = millis();
  }
  
  if (!_active) {
    if ((t - _previousRun) >= _interval) {
      // interval has expired
      _active = true; // enable measurement
      _previousRun = t;
    
    } else {
      // do nothing
    }
  }
  
  if (_active) {
    if ((t - _previousRun) >= _duration) {
      // duration has expried
      _active = false; // disable measurement
      
    } else if ((t - _previousMeas) >= _resolution) {
      // perform a measurement
      _previousMeas = t;
      run();
      
    }
  }
  
  return _active ? 1 : 0;
}
