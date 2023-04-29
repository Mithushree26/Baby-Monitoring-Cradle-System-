//Baby Monitoring Cradle System
//#define CAYENNE_DEBUG
//#define CAYENNE_PRINT Serial
//#include <CayenneMQTTESP8266.h>
#include "DHT.h"
#include "Servo.h"



// Inputs
#define DHTTYPE DHT11
#define waterSensor 2 //Digital
#define DHTPIN  3      // Digital
#define pulseSensor A0  //Analog
#define soundSensor A1  //Analog

// outputs

#define bulb 5
#define dcMotor 6
#define servoMotor A2
#define buzzer 8
#define waterFlag 4   




// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";

int isWaterDetected();

unsigned long lastMillis = 0;



//Intializing DHT and Servo objects
DHT dht(DHTPIN,DHTTYPE);
Servo myCradle;

void setup() {
 Serial.begin(9600);
 dht.begin();
//  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

//  Input Pin Setup
  pinMode(waterSensor,INPUT);
  pinMode(pulseSensor,INPUT);
  pinMode(soundSensor,INPUT);
  


//  Output Pin Setup

  pinMode(bulb,OUTPUT);
  pinMode(dcMotor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(waterFlag,OUTPUT);
  myCradle.attach(servoMotor);

  
}

void loop() {
//  Cayenne.loop();
  int k = isWaterDetected();
  if(k){
    digitalWrite(waterFlag ,HIGH);
  }
  else{
    digitalWrite(waterFlag ,LOW);
    }

  //Ready a pulse and sending to Dashboard
   float pulseData = analogRead(pulseSensor);
   displayToDashboard (1, pulseData);

   float h = dht.readHumidity();
   displayToDashboard (2, h);

   float t = dht.readTemperature();
   displayToDashboard (3, t);
   if (t >=32){
    digitalWrite(dcMotor,HIGH);
    }
   else{
    digitalWrite(dcMotor ,LOW);
    }

    float soundData = analogRead(soundSensor); 
    if (soundData  > 800){
      int speedVar  = 1000;
      moveCradle(speedVar);
      playMusic();
      turnOffLamp();
    }
    else {
      stopCradle();
      stopMusic();
      turnOnLamp();
    }
}

int isWaterDetected(){
  // Sending Sensor Data to cayenne 
  int waterDetect = digitalRead(waterSensor);
//  Cayenne.virtualWrite(0,waterDetect);
  if(waterDetect == 1 || waterDetect == HIGH){
    return 1;
    }
    return 0;
}


void displayToDashboard (int channel ,float Input){
//   Cayenne.virtualWrite(channel ,Input);
   return;
  
}


void moveCradle(int speed){
  myCradle.write(0);
  delay(speed);
  myCradle.write(180);
  delay(speed);
  return;
  }

void playMusic(){
  digitalWrite(buzzer,HIGH);
  return;
 
}

void stopMusic(){
  digitalWrite(buzzer,LOW);
  return;

}

void stopCradle(){
 myCradle.write(90);
 return;
}

void turnOnLamp(){
  digitalWrite(bulb,HIGH);
  return;
  }


void turnOffLamp() {
  digitalWrite(bulb,LOW);
  return;
 
}
