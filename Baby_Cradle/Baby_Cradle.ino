//Baby Monitoring Cradle System
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "DHT.h"
#include <Servo.h>



// Inputs
#define DHTTYPE DHT11
#define waterSensor 2 //Digital
#define DHTPIN  3      // Digital
#define pulseSensor A0  //Analog
#define soundSensor A1  //Analog

// outputs

#define bulb 5
#define dcMotor 6
#define servoMotor 7
#define buzzer 8

// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";

unsigned long lastMillis = 0;


//Intializing DHT and Servo objects
DHT dht(DHTPIN,DHTTYPE);
Servo myservo;

void setup() {
 Serial.begin(9600);
 dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

//  Input Pin Setup
  pinMode(waterSensor,INPUT);
  pinMode(pulseSensor,INPUT);
  pinMode(soundSensor,INPUT);


//  Output Pin Setup

  pinMode(bulb,OUTPUT);
  pinMode(dcMotor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  myservo.attach(servoMotor);

  
}

void loop() {
  Cayenne.loop();
}
