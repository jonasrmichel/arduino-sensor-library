/**
 * PeopleCounterSensor.h
 */

#ifndef PEOPLE_COUNTER_SENSOR_H_
#define PEOPLE_COUNTER_SENSOR_H_

#define ENTER_DELTA  "1"
#define EXIT_DELTA   "-1"

#include "Sensor.h"


class PeopleCounterSensor : public Sensor {
  public:
  PeopleCounterSensor(String name, String units, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime) : Sensor(name, units, interval, duration, resolution, callback, pseudoTime) {}
    
    ~PeopleCounterSensor() { }
  
    /**
     * Mandatory overridden methods
     */
    void init();
    void run();
  
    /**
     * Returns a String representation of a sensor reading value
     */
    String getValueString();
    
    /**
     * Sensor-specific methods
     */
    boolean detect(int pin);

  private:
    static const int _enterPin = A0; // the proximity sensor closest to the doorway
    static const int _exitPin = A1; // the proximity sensor farthest from the doorway
    
    static const float _threshold = 0.80; // detection threshold (volts)

    boolean _detectedEntrance;
    boolean _detectedExit;
    
};

#endif /* PEOPLE_COUNTER_SENSOR_H_ */
