#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "RTClib.h"

RTC_DS1307 DS1307_RTC;

////////////////////////////////////////////////////////////
File myFile;
int pinCS = 53,y,mm,d,m,h,s; // Pin 10 on Arduino Uno
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#include "temprature.h"
float T[12];
//////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Serial.println("LABEL, Date, Time,Temprature T1,Temprature T2,Temprature T3,Temprature T4,Temprature T5,Temprature T6,Temprature T7,Temprature T8,Temprature T9,Temprature T10,Temprature T11,Temprature T12");
  pinMode(pinCS, OUTPUT);
  if (! DS1307_RTC.begin()) {
    //Serial.println("Couldn't find RTC");
  //  Serial.flush();
   // abort();
  }
// DS1307_RTC.adjust(DateTime(2022, 3, 26, 10, 50, 0));//January 21, 2014 at 3am
  // SD Card Initialization
  if (SD.begin())
  {
   // Serial.println("SD card is ready to use.");
  } else
  {
  //  Serial.println("SD card initialization failed");
    return;
  }
 


}  


void loop() {
  Serial.print("DATA,DATE,TIME,");
    if (SD.begin())
  {
   // Serial.println("SD card is ready to use.");
  } else
  {
   // Serial.println("SD card initialization failed");
    return;
  }
  myFile = SD.open("test.txt", FILE_WRITE);
 sensors.requestTemperatures(); // Send the command to get temperature
  float tempC = sensors.getTempCByIndex(0);
   if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print(tempC);
  }   
  else
  {
    Serial.print("No data");
  }
  Serial.print(" , ");
float b = sensors.getTempCByIndex(1);
if(b != DEVICE_DISCONNECTED_C) 
  {
    Serial.print(b);
  } 
  else
  {
    Serial.print("No data");
  }
  // Check if reading was successful
 Serial.print(" , ");
 for(int i=1;i<=12;i++)
 {
 T[i-1]=temprature(analogRead(i));//A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14 a11 problem
 }
 DateTime now = DS1307_RTC.now();

    y=now.year();
    mm=now.month();
    d=now.day();
    h=now.hour();
    m=now.minute();
   s=now.second();
   myFile.print(d);
   myFile.print(":");
   myFile.print(mm);
   myFile.print(":");
   myFile.print(y);
   myFile.print("  ");
   myFile.print(h);
   myFile.print(":");
   myFile.print(m);
      myFile.print(":");
   myFile.print(s);
   myFile.print(",");
    for(int i=1;i<=12;i++)
 {
    myFile.print(T[i-1]);
   myFile.print(",");
   Serial.print(T[i-1]);
  Serial.print(",");
 }
 myFile.print(b);
 myFile.print(",");
  myFile.println(tempC);
Serial.print(tempC);
Serial.print(",");
   Serial.print(b);
  Serial.println(",");
  myFile.close();
   delay(3000);   
 
}
