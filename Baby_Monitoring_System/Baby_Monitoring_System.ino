//Baby Monitoring Cradle System
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "DHT.h"
#include <PulseSensorPlayground.h> 
//#include <Servo.h>?



// Inputs
#define DHTTYPE DHT11
#define waterSensor D2 //Digital
#define DHTPIN  D3      // Digital
#define pulseSensor A0  //Analog
//#define soundSensor A1  //Analog

// outputs

#define dcMotor D6
//#define servoMotor 7
#define buzzer D8

// WiFi network info.
char ssid[] = "Ranganath";
char wifiPassword[] = "Tiptur@25373";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "1ac4b120-e0d4-11ed-8485-5b7d3ef089d0";
char password[] = "e29ad28b9e2dc3afe6ee49e7f421f61897135dc3";
char clientID[] = "20b3db60-e0d4-11ed-8485-5b7d3ef089d0";

unsigned long lastMillis = 0;


//Intializing DHT and Servo objects
DHT dht(DHTPIN,DHTTYPE);
//Servo myservo;

void setup() {
 Serial.begin(9600);
 dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

//  Input Pin Setup
  pinMode(waterSensor,INPUT);
//  pinMode(pulseSensor,INPUT);
//  pinMode(soundSensor,INPUT);


//  Output Pin Setup

//  pinMode(bulb,OUTPUT);
  pinMode(dcMotor,OUTPUT);
  pinMode(buzzer,OUTPUT);
//  myservo.attach(servoMotor);
digitalWrite (dcMotor,LOW);
  
}

void loop() {
  Cayenne.loop();
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  int waterDetected = digitalRead(waterSensor);
  float bpm = analogRead(pulseSensor);
  if(t > 27){
    digitalWrite (dcMotor,HIGH);
  }
  else {
    digitalWrite (dcMotor,LOW);
  }

  if(waterDetected){
    digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
  }

  
  
  Cayenne.celsiusWrite(1,t);
  Cayenne.virtualWrite(2,h,TYPE_RELATIVE_HUMIDITY);
  Cayenne.virtualWrite(3,waterDetected, TYPE_DIGITAL_SENSOR, UNIT_DIGITAL);
  Cayenne.virtualWrite(4,bpm);
  
  
}
