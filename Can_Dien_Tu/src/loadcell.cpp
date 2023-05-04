// #include <Arduino.h>
// #include <HX711.h>

// #define LOADCELL_DOUT_PIN 23
// #define LOADCELL_SCK_PIN 22

// #define calibValue 103918

// float val;

// HX711 scale;

// void initLoadCell();

// void setup()
// {
//     Serial.begin(115200);
//     initLoadCell();
// }

// void loop()
// {
//     Serial.print("one reading:\t");
//     Serial.print(scale.get_units(), 2);
//     Serial.print("\t| average:\t");
//     val = abs(scale.get_units(10));
//     Serial.println(val, 2);

//     scale.power_down();
//     delay(5000);
//     scale.power_up();
// }

// void initLoadCell()
// {
//     scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

//     scale.set_scale(calibValue); 
//     scale.tare();
// }