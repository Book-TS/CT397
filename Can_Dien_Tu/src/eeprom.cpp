// #include <Arduino.h>
// #include <EEPROM.h>

// #define EEPROM_SIZE 1

// void setup() {
//     Serial.begin(115200);
//     EEPROM.begin(EEPROM_SIZE);
//     // EEPROM.write(0, 1);
//     // delay(1000);
//     // Serial.println("ghi EEPROM");
//     int a = EEPROM.read(0) + 1;
//     EEPROM.write(0, a);
//     delay(1000);
// }

// void loop() {
//     Serial.println("Gia tri doc tu EEPROM la: " + String(EEPROM.read(0)));
//     delay(1000);
// }