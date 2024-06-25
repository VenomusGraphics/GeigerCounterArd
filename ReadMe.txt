Enter all new info used for the the project in here only.
https://github.com/cdjq/DFRobot_Geiger/tree/main
https://github.com/adafruit/Adafruit_BMP280_Library
https://learn.adafruit.com/adafruit-bmp280-barometric-pressure-plus-temperature-sensor-breakout/arduino-test

During normal operation, high voltage is added at both ends of the Geiger tube, and the Geiger tube itself is equivalent to an open circuit.
When a high-energy particle is injected into the Geiger tube, the particle energy ionizes the gas in the tube and discharges it.
The negative pole of the Geiger tube outputs a pulse signal.

This pulse signal is processed to drive the buzzer to output a 'click' sound, which is counted by the digital circuitry.
The basic unit of counting is CPM, which is the number of pulses per minute, according to the Geiger tube data sheet
conversion factor, which converts CPM into a unit of radiant intensity, μSv.

Product images (SVG is not recommended here)

SVG renderings on the front and back

Output signals and calculations
The default level is high, and the Geiger tube outputs a pull-down pulse with a pulse width of about 300 μs when the signal is generated.

CPM is the pulse count per minute, which can actually be counted without one minute, if there are 10 pulses in 20 seconds, then 10*(20/60)=30CPM

μSv/h is the unit of radiation intensity, and the relationship between μSv/h and CPM is μSv/h=CPM/151, that is, when CPM is 30, the radiation intensity is μSv/h=30/151=0.199

nSv/h is the unit of radiant intensity, and the relationship is 1000 nSv/h = 1 μSv/h

Common CPM levels

Common CPM levels
CPM Description
40 Basic radiation of the natural environment
400 External radiation from a high-flying airliner
Next to the 800 Chernobyl nuclear power plant
150,000 High radiation hazard zone inside nuclear power plants
Table of Contents

bod rate is 9600
