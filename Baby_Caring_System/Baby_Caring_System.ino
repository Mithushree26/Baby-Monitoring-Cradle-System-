#include <Servo.h>
#define soundSensor A1
#define servoMotor A2
#define bulb 3

Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soundSensor,INPUT);
  pinMode(bulb,INPUT);
  myservo.attach(servoMotor);
}

void loop() {
  // put your main code here, to run repeatedly:
  float soundData = analogRead(soundSensor);
  if (soundData  > 800){
  digitalWrite(bulb,HIGH);
  myservo.write(0);
  delay(2000);
  myservo.write(180);
  delay(2000);
  
  }

  else {
    myservo.write(90);
    digitalWrite(bulb,LOW);
  }

}
