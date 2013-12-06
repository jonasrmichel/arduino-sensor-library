arduino-sensor-library
======================

This is a super lightweight general purpose sensing framework for the [Arduino](http://arduino.cc/) platform. The library supports timed actions (like periodically reading the value of an analog pin) even if the Arduino board is being duty cycled (put to sleep). Using this library makes it easy to run multiple sensing applications, which may need to <i>sense</i> at different intervals, on a single Arduino board without cramming all your sensors' code into a single messy PDE file full of hard coded timing constraints.

<h2>Example Use Case</h2>
Let's say you'd like to build a mini Arduino-powered weather station to stick on your back porch and capture some weather data. Your weather station consists of an Arduino board and several pieces of sensing hardware to sense things like temperature, humudity, light level, wind speed, etc. Also, you'd really like to impress your friends, so you want your weather station to be solar powered.

Your application has several <b>constraints</b>. First, all of your application code will run on one board. Next, each sensor will probably capture a reading at a different interval (for example, there's no need to capture temperature as often as wind speed). Finally, you will probably want to duty cycle your board to conserve power.

Implementing this application poses some <b>challenges</b>. Putting all of your sensors' behavior in a single PDE file would almost certainly be ugly and difficult to maintain. Intertwining each sensors' timing would be complex. Duty cycling (powering down) your board resets the onboard timers making it difficult to maintain consistent timing intervals.

This library takes care of all of the above enabling you to juts focus on <i>what</i> each of your sensors needs to do and <i>how often</i>.

<h2>Installing</h2>


<h2>Usage</h2>
