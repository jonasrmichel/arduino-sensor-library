/**
 * PeopleCounterSensor.cpp
 */

 #include "PeopleCounterSensor.h"

 
/**
 * Mandatory overridden methods
 */
void PeopleCounterSensor::init() {
  _detectedEntrance = false;
  _detectedExit = false;
}

void PeopleCounterSensor::run() {
  boolean entrance = detect(_enterPin);
  boolean exit = detect(_exitPin);

  if (!(_detectedEntrance || _detectedExit)) {
  	// initial state...something ineresting could happen...
  	if (entrance && !exit) {
  	  // detected an entrance
  	  _callback(getReading(ENTER_DELTA));

  	} else if (exit && !entrance) {
  	  // an exit event
  	  _callback(getReading(EXIT_DELTA));
  	}
  }

  _detectedEntrance = entrance;
  _detectedExit = exit;
}

boolean PeopleCounterSensor::detect(int pin) {
	// read the input on the analog pin
	int reading = analogRead(pin);
	// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
	float voltage = reading * (5.0 / 1023.0);

	return (voltage >= _threshold);
}