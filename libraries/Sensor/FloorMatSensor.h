/**
 * FloorMatSensor.h
 */

#ifndef FLOOR_MAT_SENSOR_H_
#define FLOOR_MAT_SENSOR_H_

#include "Sensor.h"

class FloorMatSensor : public Sensor {
  public:
    FloorMatSensor(String name, String units, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime) : Sensor(name, units, interval, duration, resolution, callback, pseudoTime) {}
    
    ~FloorMatSensor() {}
  
    /**
     * Mandatory overridden methods
     */
    void init();
    void run();
  
    /**
     * Returns a String representation of a sensor reading value
     */
    String getValueString(int val);
    
    /**
     * Sensor-specific methods
     */
    void snapshot();
    int countPeople();
    
  private:
    static const int _numSwitches = 15;
    int _switches[_numSwitches+1]; // pin-to-switch mapping
    int _states[_numSwitches]; // switch states
    
};

#endif /* FLOOR_MAT_SENSOR_H_ */
