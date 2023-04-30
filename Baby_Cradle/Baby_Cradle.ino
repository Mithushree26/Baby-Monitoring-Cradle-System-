//Baby Monitoring Cradle System
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266Shield.h>
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
char ssid[] = "Ranganath";
char wifiPassword[] = "Tiptur@25373";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "daf90710-e657-11ed-9ab8-d511caccfe8c";
char password[] = "d036a456c510c8bcfc9db0b52be7c6ac1329e805";
char clientID[] = "6f7c5470-e737-11ed-8485-5b7d3ef089d0";

int isWaterDetected();

//Need to Change Acordingly based on your Requirement
int speedConstant =  1; 


int speedRPM = 100;

unsigned long lastMillis = 0;

// Set ESP8266 Serial object. In this example we use the Serial1 hardware serial which is available on boards like the Arduino Mega.
#define EspSerial Serial

ESP8266 wifi(&EspSerial);



//Intializing DHT and Servo objects
DHT dht(DHTPIN,DHTTYPE);
Servo myCradle;

void setup() {
 Serial.begin(9600);
 delay(10);
 EspSerial.begin(115200);
 dht.begin();
 Cayenne.begin(username, password, clientID, wifi, ssid, wifiPassword);


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
  Cayenne.loop();
  int k = isWaterDetected();
  if(k){
    digitalWrite(waterFlag ,HIGH);
  }
  else{
    digitalWrite(waterFlag ,LOW);
    }

  //Ready a pulse and sending to Dashboard
   float pulseData = analogRead(pulseSensor);
    Cayenne.virtualWrite(1,pulseData);

   float h = dht.readHumidity();
   Cayenne.virtualWrite(2,h,TYPE_RELATIVE_HUMIDITY,UNIT_PERCENT);

   float t = dht.readTemperature();
   Cayenne.celsiusWrite(3, t);
   
    
   
   if (t >=32){
    digitalWrite(dcMotor,HIGH);
    }
   else{
    digitalWrite(dcMotor ,LOW);
    }

    float soundData = analogRead(soundSensor); 
    if (soundData  > 800){
      int speedVar  = speedConstant*speedRPM;
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
  Cayenne.virtualWrite(0,waterDetect);
  if(waterDetect == 1 || waterDetect == HIGH){
    return 1;
    }
    return 0;
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

CAYENNE_IN(5)
{
  int value = getValue.asInt(); // 0 to 255
  speedRPM = value;

}
