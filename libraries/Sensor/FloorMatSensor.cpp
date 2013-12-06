/**
 * FloorMatSensor.cpp
 */

#include "FloorMatSensor.h"

/**
 * Mandatory overridden methods
 */
void FloorMatSensor::init() {
  // define switch-to-pin mapping
  _switches[0] = 32;
  _switches[1] = 34;
  _switches[2] = 36;
  _switches[3] = 38;
  _switches[4] = 40;
  _switches[5] = 23;
  _switches[6] = 25;
  _switches[7] = 27;
  _switches[8] = 29;
  _switches[9] = 31;
  _switches[10] = 33;
  _switches[11] = 35;
  _switches[12] = 37;
  _switches[13] = 39;
  _switches[14] = 41;
  _switches[15] = 22; // ground
  
  // configure the switch pins
  for (int pin = 0; pin < _numSwitches; pin++) {
    // make this pin an input
    pinMode(_switches[pin], INPUT);
    // turn on internal pullup resistors
    digitalWrite(_switches[pin], HIGH);
  }
  
  // make the ground pin an output
  pinMode(_switches[_numSwitches], OUTPUT);
  // ground it
  digitalWrite(_switches[_numSwitches], LOW);
}

void FloorMatSensor::run() {
  // take a snapshot of the mat
  snapshot();
  
  // count people on the mat
  int n = countPeople();
  
  // create a sensor reading and send it to the callback
  _callback(getReading(getValueString(n)));
}

String FloorMatSensor::getValueString(int val) {
  // validation: return an colon-delimited list of switch states preceded by people_count
//  String v = "\"";
//  v += val; // people_count
//  for (int s = 0; s < _numSwitches; s++) { // switch states
//    v += ":";
//    v += _states[s];
//  }
//  v += "\"";
//  return v;
  
  return String(val);
}

/**
 * Sensor-specific methods
 */
 
void FloorMatSensor::snapshot() {
  // read the switch pins
  int digstate;
  for (int pin = 0; pin < _numSwitches; pin++) {
    // record the state of the pin
    //   depressed: digital LOW
    //   otherwise: digital HIGH
    digstate = digitalRead(_switches[pin]);
    if (digstate == LOW) // depressed
      _states[pin] = 1;
    else
      _states[pin] = 0;
  }
}

int FloorMatSensor::countPeople() {
  // heuristic: one person ~ one or two switches depressed
  int count = 0;
  for (int s = 0; s < _numSwitches; s++) {
    count += _states[s];
    if (_states[s] > 0)
      s++;
  }
  return count;
}
