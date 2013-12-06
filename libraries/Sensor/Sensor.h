/**
 * Sensor.h
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#define MAX_INFO_SIZE 10
#define TERMINATOR    "\0"
#define EOT           "@"

#include "Arduino.h"

class Sensor {
  public:
    /**
     * Constructors
     */
    Sensor(String name, String units, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime);
  
    void initialize(String name, String units, unsigned long previousRun, unsigned long previousMeas, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime);
  
    /**
     * Default destructor
     */
    ~Sensor() {}
    
    /**
     * These are the serialized equivalents of Arduino's setup() and loop()
     * Subclasses must override these methods
     */
    virtual void init() {}
    virtual void run() {}
    
    /**
     * Returns a JSON String contianing the sensor's "registration"
     */
    String getRegistration();
    
    /**
     * Returns a JSON String containing a sensor reading
     */
    String getReading(String val);
    
    /**
     * Timer methods
     */
    void disable();
    void enable();
    int check();
    
  protected:
    String _name;
    String _units;
    unsigned long _interval;   // sensor run interval (ms)
    unsigned long _duration;   // sensor run duration (ms)
    unsigned long _resolution; // sensor measurement resolution (ms)
    void (*_callback)(String);
  
  private:
    bool _active;
    unsigned long _previousRun;
    unsigned long _previousMeas;
    volatile unsigned long *_pseudoTime;

};

#endif /* SENSOR_H_ */

