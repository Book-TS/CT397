#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(40, 41, 37, 36, 35, 34);

#define K1 47
#define K2 46
#define K3 43
#define K4 47
#define LR  13
#define LG  11
#define LB  12

#define LM35 A0
#define PHOTO A7

void setup()
{
    pinMode(K1, INPUT_PULLUP);
    pinMode(K2, INPUT_PULLUP);
    pinMode(K3, INPUT_PULLUP);
    pinMode(K4, INPUT_PULLUP);
    pinMode(LR, OUTPUT);
    pinMode(LG, OUTPUT);
    pinMode(LB, OUTPUT);

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hello world ! ");
    lcd.setCursor(0, 1);
    lcd.print("DLDK INSEE ");
    delay(500);
    lcd.clear();

    Serial.begin(9600);
    delay(200);
    Serial.println("Hello world !");
}

void loop()
{
    int tmp = map(analogRead(LM35), 0, 1023, 0, 5000) / 10;
    int lux = analogRead(PHOTO);
    lcd.setCursor(0, 1);
    lcd.print("T: ");
    lcd.setCursor(10, 1);
    lcd.print("P: ");
    lcd.setCursor(0, 1);
    lcd.print(tmp);
    lcd.setCursor(10, 1);
    lcd.print(lux);

    Serial.println("T" + String(tmp) + "P" + String(lux));

    if (Serial.available() > 0)
    {
        String str = Serial.readString();
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print(str);

        String cmd = str.substring(0, 1);
        String val = str.substring(1, str.length() - 1);

        if (cmd == "R")
            analogWrite(LR, val.toInt());
        if (cmd == "G")
            analogWrite(LG, val.toInt());
        if (cmd == "B")
            analogWrite(LB, val.toInt());
    }
    delay(100);
}
