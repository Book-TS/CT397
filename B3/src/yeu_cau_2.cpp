// #include <Arduino.h>

// #define K0 42
// #define K1 47
// #define K2 46
// #define K3 43
// #define COM 33

// const char PinOut[] = {22, 23, 24, 25, 26, 27, 28, 29};
// const char ctr[] = {37, 36, 35, 34};

// const unsigned char code7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// char temp_1[4] = {0, 0, 0, 0};
// int index = 0;
// int counter = 0;

// int dat = 0, idx = 0;
// char buff[5];

// unsigned long oldtime_1 = 0;
// unsigned long oldtime_2 = 0;
// unsigned long time_1 = 5;
// unsigned long time_2 = 100;

// void toDisplay(int counter);
// void setPinOut(char temp);
// void Scanled();
// void Scanled_1();

// void setup()
// {
//     Serial.begin(9600);

//     for (int i = 0; i < 8; i++)
//         pinMode(PinOut[i], OUTPUT);

//     for (int i = 0; i < 4; i++)
//         pinMode(ctr[i], OUTPUT);

//     pinMode(COM, OUTPUT);
//     digitalWrite(COM, LOW);

//     pinMode(K0, INPUT_PULLUP);
//     pinMode(K1, INPUT_PULLUP);
//     pinMode(K2, INPUT_PULLUP);
//     pinMode(K3, INPUT_PULLUP);
// }

// void loop()
// {
//     if ((unsigned long)(millis() - oldtime_1) > time_1)
//     {
//         Scanled_1();
//         oldtime_1 = millis();
//     }
//     if ((unsigned long)(millis() - oldtime_2) > time_2)
//     {
//         if (digitalRead(K0) == 0)
//         {
//             Serial.println("Chao cac ban");
//             while (!digitalRead(K0))
//                 ;
//         }

//         if (digitalRead(K1) == 0)
//         {
//             Serial.println("Do luong & dieu khien bang PC");
//             while (!digitalRead(K1))
//                 ;
//         }
//         if (digitalRead(K2) == 0)
//         {
//             Serial.println("CT397 - DLDK");
//             while (!digitalRead(K2))
//                 ;
//         }
//         if (digitalRead(K3) == 0)
//         {
//             Serial.println("TH giao tiep RS232");
//             while (!digitalRead(K3))
//                 ;
//         }
//         oldtime_2 = millis();
//     }

//     if (Serial.available())
//     {
//         char ch = Serial.read();
//         if (ch == 13)
//         {
//             buff[idx] = 0;
//             dat = atoi(buff);
//             toDisplay(dat);
//             idx = 0;
//         }
//         else
//         {
//             buff[idx] = ch;
//             idx++;
//         }
//     }
// }

// // Chuyen so sang LED 7 doan
// void toDisplay(int counter)
// {
//     temp_1[3] = counter / 1000;
//     temp_1[2] = (counter % 1000) / 100;
//     temp_1[1] = ((counter % 1000) % 100) / 10;
//     temp_1[0] = counter % 10;
// }

// // Set muc logic
// void setPinOut(char temp)
// {
//     for (int i = 0; i < 8; i++)
//     {
//         if (temp & 0x01)
//             digitalWrite(PinOut[i], HIGH);
//         else
//             digitalWrite(PinOut[i], LOW);
//         temp = temp >> 1;
//     }
// }

// // Scan LED
// void Scanled()
// {
//     unsigned char ch;

//     digitalWrite(ctr[index == 0 ? 3 : (index - 1)], HIGH);

//     ch = temp_1[index];
//     setPinOut(code7seg[ch]);
//     digitalWrite(ctr[index], LOW);
//     index++;
//     if (index >= 4)
//         index = 0;
// }

// // Scan LED
// void Scanled_1()
// {
//     unsigned char ch;

//     digitalWrite(ctr[index == 0 ? 3 : (index - 1)], LOW);

//     ch = temp_1[index];
//     setPinOut(code7seg[ch]);
//     digitalWrite(ctr[index], HIGH);
//     index++;
//     if (index >= 4)
//         index = 0;
// }