/**
 * SensorDemo: Demonstrates the usage of the Sensor library.
 */
 
// AVR / Arduino libraries
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
 
// Custom libraries
#include <Sensor.h>
#include <FloorMatSensor.h>

// set to true if you want the board to enter low power mode (e.g., sleep) when possible
#define SLEEPY  true

// define the sleep mode as one of the following...
// SLEEP_MODE_IDLE - the least power savings
// SLEEP_MODE_ADC
// SLEEP_MODE_PWR_SAVE
// SLEEP_MODE_STANDBY
// SLEEP_MODE_PWR_DOWN - the most power savings
#define SLEEP_MODE  SLEEP_MODE_STANDBY

// a counter to emulate a timer 
// (on-board timers pause when arduino sleeps deeper than IDLE)
volatile unsigned long emuTimer = 0;
volatile unsigned long wakeupTime = 0;
volatile unsigned long wakeupMillis = 0;

// pin used to sleep the XBee
int xbeeSleep = 11;

// create sensor objects
// pass NULL for the last parameter if you don't need a persistent pseudo-timer 
// (e.g., if your board will always be on)
FloorMatSensor floormat = FloorMatSensor("floor-mat", "Integer", 60000, 10, 1, sensorCallback, &emuTimer);

void setup() {
  // setup the watchdog timer
  setupWDT();
  
  Serial.begin(9600);
  
  // initialize each sensor
  floormat.init();
 
  // initialize the pseudo-timer
  emuTimer = 0;
  wakeupTime = 0;
}

void loop() {
  // check each sensor for data readings
  int sensing = 0;
  
  sensing += floormat.check();
  
  // get some rest and save power if we can
  goToSleep(sensing);
}

void sensorCallback(String s) {
  Serial.println(s);
}

/**
 * Sleep functions
 *
 * Helpful resource on arduino sleep modes and watchdog timer: 
 *   http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
 */
 
// Setup the watchdog timer
void setupWDT() {
  // Clear the reset flag.
  MCUSR &= ~(1<<WDRF);
  
  // In order to change WDE or the prescaler, we need to
  // set WDCE (This will allow updates for 4 clock cycles).
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  // Set new watchdog timeout prescaler value.
  WDTCSR = 1<<WDP3; // 4.0 seconds
  
  // Enable the WD interrupt (note, no system reset).
  WDTCSR |= _BV(WDIE);
}
 
// Watchdog interrupt service. This is executed when watchdog times out.
ISR(WDT_vect) {
  // update the timer emulator
  emuTimer += 4000; // 4000 ms = 4.0 seconds
  
  // store the wakeup time for reference
  wakeupTime = emuTimer;
  
  // store the wakeup millis for reference
  wakeupMillis = millis();
}

// Sleeps the arduino when there are no sensors that require the arduino to remain awake
void goToSleep(int sensing) {
  if (!SLEEPY)
    return;
  
  if (!sensing) {
    // Re-enter sleep mode
    enterSleep();
    
  } else {
    // update the timer emulator with relative time since wakeup
    emuTimer = wakeupTime + (millis() - wakeupMillis);
    
  }
}

// Puts the arduino into sleep mode.
void enterSleep() {
  set_sleep_mode(SLEEP_MODE);
  sleep_enable();
  
  // put the XBee to sleep
  sleepXBee();
  
  // Now enter sleep mode.
  sleep_mode();
  
  // The program will continue from here after the WDT timeout
  sleep_disable(); // First thing to do is disable sleep.
  
  // wake up the XBee
  wakeXBee();
  
  // Re-enable the peripherals.
  power_all_enable();
}

void sleepXBee() {
  digitalWrite(xbeeSleep, HIGH);
}

void wakeXBee() {
  digitalWrite(xbeeSleep, LOW);
}
