#include <TinyGPS.h>

#include <SoftwareSerial.h>

#include <Arduino_LSM6DS3.h>

#include <SPI.h>

#include <SD.h>
const int PulseWire = 0;
const int chipSelect = 4;
TinyGPS gps;
SoftwareSerial ss(4, 3);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin()
  while (!Serial);

  //Accelerometer
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  // see if the SD card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Pulsesensor
  float pulse = analogRead(PulseWire);
  
  //Accelerometer
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);

  //Gyroscope
  float gx, gy, gz;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);

    Serial.print(gx);
    Serial.print('\t');
    Serial.print(gy);
    Serial.print('\t');
    Serial.println(gz);}

  //GPS
  bool newData = false;
  unsigned long chars;

  // For one second we parse GPS data and report some key values
  
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)){ // Did a new valid sentence come in?
        newData = true;}
    }
  

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    }
  
  //SD card
  String dataString = "";
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");}
}
  
