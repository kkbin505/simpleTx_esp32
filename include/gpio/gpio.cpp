#include "Arduino.h"
#include "gpio.h"

void initGpio () {

//analogReference(EXTERNAL);
  pinMode(DIGITAL_PIN_SWITCH_ARM, INPUT);
  pinMode(DIGITAL_PIN_SWITCH_AUX2, INPUT);
  pinMode(DIGITAL_PIN_LED, OUTPUT);//LED
  //pinMode(DIGITAL_PIN_BUZZER, OUTPUT);//
  //digitalWrite(DIGITAL_PIN_BUZZER, LOW);
  //batteryVoltage=7.0; 
}
