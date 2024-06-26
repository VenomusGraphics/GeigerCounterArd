/////////////////////////////////////////////////////////
//  very  simple  voltmeter
//  will  measure  0  to  5V  only!
//  Voltages  outside  0  to  5V  will  destroy  your  Arduino!!!
//  Don’t  wire  this  backwards!
/////////////////////////////////////////////////////////
//  define  a  variable  that  tells  which  analog  pin  we  will use

int  AI0  =  1;         //AI0  stands  for  analog  input  zero
int  AI1  =  2;

//  define  a  variable  that  holds  our  Delta_v_min

float  delta_v_min=0.0049;       //  volts  per  A2D  unit

//  define  a  variable  for  our  A2D  version  of  our  signal 

int  ADC_value  =  0;

//  define  a  variable  for  our  voltage  version  of  our  signal

float  voltage  =  0.0;

///////////////////////////////////////////////////////// 
void  setup()  {
//  put  your  setup  code  here,  to  run  once  when  your  Arduino  starts  up:
//
//  Initiate  Serial  Communication,  so  we  can  see the voltage  on  our  computer
  
Serial.begin(9600);         //9600  baud  rate
}

///////////////////////////////////////////////////////// 
void  loop()  {
//  Read  in  the  voltage  in  A2D  units  form  the  serial  port 
//  remember  that  AI0  is  the  pin  number  to  read  from 
ADC_value  =  analogRead(AI0);
//  Let’s  print  out  our  A2D  version  of  our  signal 
Serial.print("  A2D  ");
Serial.print(ADC_value);
//  Now  convert  to  voltage  units  using  delta_v_min
voltage  =  ADC_value * delta_v_min;
//  And  print  out  our  voltage  version  of  our  signal 
Serial.print("  voltage  ");
//  Print  the  voltage  with  4  significant  figures) 
Serial.println(voltage,  4);
}
///////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////

// This is the start of the altimeter code
/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  This example shows how to take Sensor Events instead of direct readings
  
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2652

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 Sensor event test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  }
  
  bme_temp->printSensorDetails();
  bme_pressure->printSensorDetails();
  bme_humidity->printSensorDetails();
}

void loop() {
  sensors_event_t temp_event, pressure_event, humidity_event;
  bme_temp->getEvent(&temp_event);
  bme_pressure->getEvent(&pressure_event);
  bme_humidity->getEvent(&humidity_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Humidity = "));
  Serial.print(humidity_event.relative_humidity);
  Serial.println(" %");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();
  delay(3000);
}
