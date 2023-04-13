#include <Arduino.h>

#define K0 42
#define K1 47
#define K2 46
#define K3 43
#define COM 33

char PinOut[] = {22, 23, 24, 25, 26, 27, 28, 29};

void setPinOut(char temp);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++)
    pinMode(PinOut[i], OUTPUT);

  pinMode(COM, OUTPUT);
  digitalWrite(COM, LOW);

  pinMode(K0, INPUT_PULLUP);
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    setPinOut(ch);
  }

  if (digitalRead(K0) == 0) {
    Serial.println('0');
    while(!digitalRead(K0));
  }
  if (digitalRead(K1) == 0) {
    Serial.println('1');
    while(!digitalRead(K1));
  }
  if (digitalRead(K2) == 0) {
    Serial.println('2');
    while(!digitalRead(K2));
  }
  if (digitalRead(K3) == 0) {
    Serial.println('3');
    while(!digitalRead(K3));
  }
  delay(5);
}

// Set chan theo hex
void setPinOut(char temp) {
  for (int i = 0; i < 8; i++) {
    if (temp & 0x01)
      digitalWrite(PinOut[i], HIGH);
    else
      digitalWrite(PinOut[i], LOW);
    temp = temp >> 1;
  }
}