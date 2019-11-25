/*
╔------------------------------------------------------------╗
║             Super Mario Interactive Light Cube             ║
╠------------------------------------------------------------╣
║ This is a Super Mario interactive light cube project based ║
║ on a Digispark Attiny85 board.                             ║
╠------------------------------------------------------------╣
║ Filename: SuperMarioInteractiveLightCube.ino               ║
║ Last modified: 10 June 2017 by Leonardo Sposina.           ║
╚------------------------------------------------------------╝
*/

#include "pitches.h"

const byte BUZZER_PIN = 0;
const byte SENSOR_PIN = 2;
const byte LEDS_PIN = 4;

const byte LOOP_DELAY = 250;
const byte TOUCH_COUNT_MAX = 7;
const int TIME_COUNT_MAX = 3000;
const byte LIGHT_STEP = 255 / TOUCH_COUNT_MAX;

const int COIN_TONES[] = {NOTE_B5, NOTE_E6};
const int COIN_TEMPO[] = {80, 450};

const int ONEUP_TONES[] = {NOTE_E6, NOTE_G6, NOTE_E7, NOTE_C7, NOTE_D7, NOTE_G7};
const int ONEUP_TEMPO[] = {125, 125, 125, 125, 125, 125};

byte touchCount = 0;
int timeCount = 0;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LEDS_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(SENSOR_PIN)) {
    if (touchCount < TOUCH_COUNT_MAX && timeCount < TIME_COUNT_MAX) {
      timeCount = 0;
      touchCount++;
      setLightIntensity(touchCount);
      playTone(COIN_TONES, COIN_TEMPO, 2);
    } else if (touchCount == TOUCH_COUNT_MAX || timeCount == TIME_COUNT_MAX) {
      playTone(ONEUP_TONES, ONEUP_TEMPO, 6);
      resetCube();
    }
  }
  if (touchCount != 0 && timeCount < TIME_COUNT_MAX) {
    timeCount += LOOP_DELAY;
  }
  delay(LOOP_DELAY);
}

void playTone(const int* tones, const int* tempo, byte notes) {
  for (byte index = 0; index < notes; index++) {
    tone(BUZZER_PIN, tones[index], tempo[index]);
    delay(tempo[index]);
  }
}

void resetCube() {
  delay(500);
  digitalWrite(LEDS_PIN, LOW);
  touchCount = 0;
  timeCount = 0;
}

void setLightIntensity(byte touches) {
  byte intensity = touches * LIGHT_STEP;
  analogWrite(LEDS_PIN, intensity);
}