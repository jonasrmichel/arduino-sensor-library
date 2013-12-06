/**
 * NoiseLevelSensor.cpp
 */

#include "NoiseLevelSensor.h"

/**
 * Mandatory overridden methods
 */
void NoiseLevelSensor::init() {
  _bufferSize = (_duration / _resolution); // samples / window
  _buffer = (int*) malloc (_bufferSize * sizeof(int));
  _sample = 0;
}

void NoiseLevelSensor::run() {
  _buffer[_sample++] = analogRead(_sensorPin);
  
  if (_sample == _bufferSize) {
    _sample = 0;
//    Serial.print("window: ");
//    Serial.print(_window);
//    Serial.println("s");
//    
//    Serial.print("max: ");
//    Serial.print(getVoltage(maximum(_buffer)));
//    Serial.println(" Volts");
//    
//    Serial.print("min: ");
//    Serial.print(getVoltage(minimum(_buffer)));
//    Serial.println(" Volts");
//    
//    Serial.print("avg: ");
//    Serial.print(getVoltage(average(_buffer)));
//    Serial.println(" Volts");
//    
//    Serial.println();
    
    // create a sensor reading and send it to the callback
    _callback(getReading(getValueString()));
  }
}

String NoiseLevelSensor::getValueString() {
  // validation: return an colon-delimited list of statistics
//  char min_voltage[32];
//  dtostrf(getVoltage(minimum()), 2, 5, min_voltage);
//  
//  char max_voltage[32];
//  dtostrf(getVoltage(maximum()), 2, 5, max_voltage);
//  
//  char avg_voltage[32];
//  dtostrf(averageVoltage(), 2, 5, avg_voltage);
//  
//  char med_voltage[32];
//  dtostrf(getVoltage(median()), 2, 5, med_voltage);
//  
//  char std_voltage[32];
//  dtostrf(stdevVoltage(), 2, 5, std_voltage);
//  
//  // validation: return a string
//  String s = "\"";
//  s += min_voltage;
//  s += ":";
//  s += max_voltage;
//  s += ":";
//  s += avg_voltage;
//  s += ":";
//  s += med_voltage;
//  s += ":";
//  s += std_voltage;
//  s += "\"";
//  
//  return s;
  
  // return the max voltage heard in the window
//  char max_voltage[32];
//  dtostrf(getVoltage(maximum()), 2, 2, max_voltage);
//  
//  return max_voltage;
  
  return String(maximum());
}

/**
 * Sensor-specific methods
 */

double NoiseLevelSensor::getVoltage(int analogReading) {
  return 100.0 * (((double) analogReading) / 1023.0);
}

int NoiseLevelSensor::minimum() {
  int m = 1023;
  for (int i = 0; i < _bufferSize; i++) {
    if (_buffer[i] < m)
      m = _buffer[i];
  }
  return m;
}

int NoiseLevelSensor::maximum() {
  int m = 0;
  for (int i = 0; i < _bufferSize; i++) {
    if (_buffer[i] > m)
      m = _buffer[i];
  }
  return m;
}

double NoiseLevelSensor::averageVoltage() {
  double sum = 0;
  for (int i = 0; i < _bufferSize; i++) {
    sum = sum + getVoltage(_buffer[i]);
  }
  double avg = sum / ((double) _bufferSize);
  return avg;
}

int NoiseLevelSensor::median() {
  sort(0, _bufferSize-1);
  return _buffer[(int)floor(_bufferSize / 2)];
}

double NoiseLevelSensor::stdevVoltage() {
  double m = averageVoltage();
  double sum = 0;
  for (int i = 0; i < _bufferSize; i++) {
    sum = sum + pow(getVoltage(_buffer[i]) - m, 2);
  }
  return sqrt( (1/((double) _bufferSize)) * sum );
}

void NoiseLevelSensor::sort(int bottom, int top) {
  // quick sort
  int middle;
  if (top < bottom) {
    middle = partition(bottom, top);
    sort(bottom, middle);   // sort first section
    sort(middle+1, top);    // sort second section
  }
}

int NoiseLevelSensor::partition(int bottom, int top) {
  // partitions the buffer and returns the middle subscript
  int x = _buffer[top];
  int i = top - 1;
  int j = bottom + 1;
  int temp;
  while (i < j) {
    while (x > _buffer[j]) {
      j--;
    }
    
    while (x < _buffer[i]) {
      i++;
    }
    
    if (i < j) {
      temp = _buffer[i];
      _buffer[i] = _buffer[j];
      _buffer[j] = temp;
    }
  }
  
  return j; // middle subscript
}