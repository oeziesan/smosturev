#include "SoftwareSerial.h" //open lib sogtware serial
#include "DFRobotDFPlayerMini.h" //open lib dfrobot

static const uint8_t PIN_MP3_TX = 10; //tx pin
static const uint8_t PIN_MP3_RX = 11;  //rx pin
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

const int moistureSensorPin = A0; //soil mosture sensor pin
int moistureThreshold = 800; //threshold value of sensor

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);
    if (player.begin(softwareSerial)) {
    Serial.println("OK");
    player.volume(30);
    } else {
      Serial.println("NOT OK");
    }
  delay(3000);
}

void loop() {
  int moistureValue = analogRead(moistureSensorPin); //sensor reading value => moisturevalue
  if (moistureValue > moistureThreshold) {
    player.volume(30);
    player.play(1);
    delay (3000);
    ifdry (); //go to void ifrdy (for not looping in one condition, but if the condition change it back again to void loop)
  } else {    
    player.volume(30);
    player.play(2);
    delay (3000);
    ifwet (); //go to void ifwet (for not looping in one condition, but if the condition change it back again to void loop)
    }
}

void ifdry() {
  int moistureValue = analogRead(moistureSensorPin);
  if (moistureValue > moistureThreshold) {
    ifdry();
  } else {
    loop();
  }
}

  void ifwet(){
  int moistureValue = analogRead(moistureSensorPin);
  if (moistureValue < moistureThreshold) {
    ifwet();
  } else {
    loop();
    }
  }