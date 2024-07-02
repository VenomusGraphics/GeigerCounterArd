/*!
  @file geiger.ino
  @brief    Detect CPM radiation intensity, the readings may have a large deviation at first, and the data tends to be stable after 3 times
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2021-9-17
  @get from https://www.dfrobot.com
  @https://github.com/DFRobot/DFRobot_Geiger
*/

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


// Edited by Tyler, Calvin, Isaac, and James

#include <SD.h> //Library for SD card reading

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();

#include <DFRobot_Geiger.h>
#if defined ESP32
#define detect_pin D3
#else
#define detect_pin 3
#endif
/*!
   @brief Constructor
   @param pin   External interrupt pin
*/
DFRobot_Geiger  geiger(detect_pin);
const int SD_PIN = 10;
int count = 0;
File logfile;

void setup()
{
  Serial.begin(9600);
  //Start counting, enable external interrupt
  geiger.start();
  init_SD();
  logfile = open_next_logfile();

  Serial.println(F("BME280 Sensor event test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  }
  
  bme_pressure->printSensorDetails();
}

void loop() {

  //Start counting, enable external interrupt
  //geiger.start();
  delay(3000);
  //Pause the count, turn off the external interrupt trigger, the CPM and radiation intensity values remain in the state before the pause
  //geiger.pause();
  //Get the current CPM, if it has been paused, the CPM is the last value before the pause
  //Predict CPM by falling edge pulse within 3 seconds, the error is ±3CPM
  Serial.print("CPM:");
  Serial.println(geiger.getCPM());
  logfile.print("CPM:");
  logfile.println(geiger.getCPM());
  //Get the current nSv/h, if it has been paused, nSv/h is the last value before the pause
  Serial.print("nSv/h:");
  Serial.println(geiger.getnSvh());
  logfile.print("nSv/h:");
  logfile.println(geiger.getnSvh());
  //Get the current μSv/h, if it has been paused, the μSv/h is the last value before the pause
  Serial.print("uSv/h:");
  Serial.println(geiger.getuSvh());
  logfile.print("uSv/h:");
  logfile.println(geiger.getuSvh());

  sensors_event_t temp_event, pressure_event, humidity_event;
  bme_pressure->getEvent(&pressure_event);

  Serial.print(F("Pressure = "));
  logfile.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  logfile.print(pressure_event.pressure);
  Serial.println(" hPa");
  logfile.println(" hPa");

  Serial.println();
  logfile.println();

  if (count > 20) {
    logfile.close();
    logfile = open_next_logfile();
    count = 0;
  }
}

void init_SD()
{
  Serial.print("Initializing  SD  card...");
  if (!SD.begin(SD_PIN)) {
    Serial.println("  failed!");
    while (1)
      ;
  }
  Serial.println("  done!");
}

File open_next_logfile() {
  char filename[24];
  //  Create  folder  for  logs  if  it  doesn’t  already  exist 
  if  (!SD.exists("/Geiger_Logs/")) {
    SD.mkdir("/Geiger_Logs/");
  }
  //  find  the  first  file  LOGxxx.TXT  that  doesn’t  exist, 
  //  then  create,  open  and  use  that  file
  for (int logn = 0; logn < 1000; logn++) {
    sprintf(filename, "/Geiger_Logs/LOG%03d.TXT", logn);
    if (!SD.exists(filename)) {
      Serial.print("Opened  \`SD:");
      Serial.print(filename);
      Serial.println("\`  for  logging.");
      break;
    }
  }
  return SD.open(filename, FILE_WRITE);
}
