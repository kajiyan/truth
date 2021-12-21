#include "l6470duino.h"
#include "MsTimer2.h"

l6470duino::driver Driver;

float FPS = 1000 / 30;
int SONAR_PIN = A0;
int THRESHOLD = 50;

boolean isRunning = false;

void setup() {
  Serial.begin(9600);
  
  Driver.init(1);
  Driver.voltage_acc(0xDF);
  Driver.voltage_dec(0xDF);
  Driver.voltage_run(0xDF);
  Driver.voltage_hold(0x30);

  MsTimer2::set(FPS, readSonar);
  MsTimer2::start();
}

void loop() {
  if (isRunning) {
    Driver.Run(1000, false);
  } else {
    Driver.SoftStop();
  }
}

void readSonar() {
  int sensorValue = analogRead(SONAR_PIN);
  
  Serial.println(sensorValue);

  if (sensorValue < THRESHOLD) {
    isRunning = true;
  } else {
    isRunning = false;
  }
}
