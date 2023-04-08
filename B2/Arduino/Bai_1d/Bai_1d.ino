#include <LiquidCrystal.h>

LiquidCrystal lcd(40, 41, 37, 36, 35, 34);

#define BACKLIGHT_PIN 10
#define K1 47
#define K2 46
#define K3 43
#define COM 33

#define LM35 A0
#define PHOTO A1

unsigned long oldtime_1 = 0;
unsigned long oldtime_2 = 0;
unsigned long time_1    = 50;
unsigned long time_2    = 50;

int status = 0, temp, sen;

void setup()
{
  Serial.begin(9600);
  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);
  pinMode(COM, OUTPUT);
  digitalWrite(COM, LOW);

  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);

  lcd.begin(16, 2);
}

void loop()
{
  if ((unsigned long) (millis() - oldtime_1) > time_1) {
    Serial.println(status);
    lcd.setCursor(0, 0);
    lcd.print("Key status: ");
    lcd.print(status);
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.setCursor(9, 1);
    lcd.print("Photo: ");
    lcd.print(sen);
    oldtime_1 = millis();
  }
  if ((unsigned long) (millis() - oldtime_2) > time_2) {
    if (digitalRead(K1) == 0) {
      status = 1;
      while (!digitalRead(K1));
    }
    if (digitalRead(K2) == 0) {
      status = 2;
      while (!digitalRead(K2));
    }
    if (digitalRead(K3) == 0) {
      status = 3;
      while (!digitalRead(K3));
    }
    temp = analogRead(LM35);
    sen = analogRead(PHOTO);
    oldtime_2 = millis();
  }
  delay(200);
}
