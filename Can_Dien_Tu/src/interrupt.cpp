// #include <Arduino.h>
// #include <EEPROM.h>

// #define EEPROM_SIZE 16
// unsigned long EEPROM_VAL = 103476;

// bool isBTMode = false;
// bool isBTUp = false;
// bool isBTDown = false;

// void IRAM_ATTR bt_mode();
// void IRAM_ATTR bt_up();
// void IRAM_ATTR bt_down();

// void setup()
// {
//     Serial.begin(115200);
//     pinMode(25, INPUT_PULLUP);
//     pinMode(26, INPUT_PULLUP);
//     pinMode(27, INPUT_PULLUP);
//     attachInterrupt(25, bt_mode, FALLING);
//     attachInterrupt(26, bt_up, FALLING);
//     attachInterrupt(27, bt_down, FALLING);

//     EEPROM.begin(EEPROM_SIZE);
//     EEPROM.put(0, EEPROM_VAL);

// }

// void loop()
// {
//     if (isBTMode)
//     {
//         Serial.println("BT Mode");
//         isBTMode = false;
//         Serial.print("VAL: "); 
//         unsigned long val;
//         EEPROM.get(0, val);
//         Serial.println(val);
//     }
//     else if (isBTUp)
//     {
//         Serial.println("BT Up");
//         EEPROM.put(0, 659498);
//         isBTUp = false;
//     }
//     if (isBTDown)
//     {
//         Serial.println("BT Down");
//         EEPROM.put(0, 256879);
//         isBTDown = false;
//     }
// }

// void IRAM_ATTR bt_mode()
// {
//     isBTMode = true;
// }

// void IRAM_ATTR bt_up()
// {
//     isBTUp = true;
// }

// void IRAM_ATTR bt_down()
// {
//     isBTDown = true;
// }