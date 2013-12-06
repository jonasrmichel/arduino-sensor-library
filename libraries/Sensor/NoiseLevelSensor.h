/**
 * NoiseLevelSensor.h
 */

#ifndef NOISE_LEVEL_SENSOR_H_
#define NOISE_LEVEL_SENSOR_H_

#include "Sensor.h"


class NoiseLevelSensor : public Sensor {
  public:
  NoiseLevelSensor(String name, String units, unsigned long interval, unsigned long duration, unsigned long resolution, void (*callback)(String), volatile unsigned long *pseudoTime) : Sensor(name, units, interval, duration, resolution, callback, pseudoTime) {}
    
    ~NoiseLevelSensor() { free(_buffer); }
  
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
    double getVoltage(int analogReading);
    int minimum();
    int maximum();
    double averageVoltage();
    int median();
    double stdevVoltage();
    void sort(int bottom, int top);
    int partition(int bottom, int top);
  
  /* every _intervalMeas ms report stat (min,max,avg) over last _window ms */
  private:
    static const int _sensorPin = A0;
    int _bufferSize;
    int* _buffer;
    int _sample;
    
};

#endif /* NOISE_LEVEL_SENSOR_H_ */
