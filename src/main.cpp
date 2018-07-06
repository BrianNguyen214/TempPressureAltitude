//need to include the adafruit bmp085 library
#include <Adafruit_BMP085.h>
//adafruit depends on wire, but you don't need to include the wire library since arduino already has it
#include <Wire.h>
#include <Arduino.h>

#define Green 13
#define Red 12

//declare an instance of the adafruit_bmp085 object since we are using its methods
Adafruit_BMP085 bmp;

void setup() {

  Serial.begin(9600);
  delay(500);
  pinMode(Green,OUTPUT);
  pinMode(Red,OUTPUT);
  bmp.begin();
  delay(1000);

}

float tempC;
float tempF;

//the sensor reads the temperature, pressure, and altitude
//the goal of the algorithm is to read off the data the sensor gets and tell the user if
//the sensor is at a high altitude (which is 1385.0 meters in this case)
//the system will shine a red LED if it is at high altitude; otherwise, it shines the green LED

void loop() {

  //the sensor read the temperature in Celsius, so you can convert it to Fahrenheit if you want
  //as shown below

  tempC = bmp.readTemperature();
  tempF = tempC*1.8 + 32.;
  Serial.print("Temperature = ");
  Serial.print(tempF);
  Serial.println(" F");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa"); //units are pascals

  //the high altitude is just some arbitrary altitude declared as "high"
  if (bmp.readAltitude() > 1385.0){
  Serial.print("(High) ");
    digitalWrite(Red,HIGH);
    digitalWrite(Green,LOW);
  }
  else{
  Serial.print("(Low) ");
    digitalWrite(Red,LOW);
    digitalWrite(Green,HIGH);
  }

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.println();
  delay(2000);

}
