// #include <Arduino.h>
// #include <ModbusSlave.h>

// unsigned char SLAVE = 1;
// long BAUD = 9600;
// ModbusSlave mbs;
// #define K0 42
// #define K1 47
// #define K2 46
// #define K3 43
// #define COM 33

// enum
// {          // Slave registers
//   KEY,     // Register 0
//   COUNTER, // Register 1
//   NUM1,    // Register 2
//   NUM2,    // Register 3
//   MB_REGS
// };

// int regs[MB_REGS];
// int i = 0, counter = 0, timer = 0;

// const char PinOut[] = {22, 23, 24, 25, 26, 27, 28, 29};
// const char ctr[] = {37, 36, 35, 34};

// const unsigned char code7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// char temp_1[4] = {0, 0, 0, 0};
// int index = 0;

// void toDisplay(int num1, int num2);
// void setPinOut(char temp);
// void Scanled();

// void setup()
// {
//   for (int i = 0; i < 8; i++)
//     pinMode(PinOut[i], OUTPUT);
//   for (int i = 0; i < 4; i++)
//     pinMode(ctr[i], OUTPUT);
//   pinMode(COM, OUTPUT);
//   digitalWrite(COM, LOW);
//   pinMode(K0, INPUT_PULLUP);
//   pinMode(K1, INPUT_PULLUP);
//   pinMode(K2, INPUT_PULLUP);
//   pinMode(K3, INPUT_PULLUP);

//   mbs.configure(0, SLAVE, BAUD, 2);
// }

// void loop()
// {
//   mbs.update(regs, MB_REGS);
//   toDisplay(regs[NUM1], regs[NUM2]);

//   if (timer++ > 200)
//   {
//     timer = 0;
//     counter++;
//     regs[COUNTER] = counter;
//   }

//   if (digitalRead(K0) == 0)
//   {
//     regs[KEY] = 1;
//     while (!digitalRead(K0))
//       ;
//   }
//   if (digitalRead(K1) == 0)
//   {
//     regs[KEY] = 2;
//     while (!digitalRead(K1))
//       ;
//   }
//   if (digitalRead(K2) == 0)
//   {
//     regs[KEY] = 3;
//     while (!digitalRead(K2))
//       ;
//   }
//   if (digitalRead(K3) == 0)
//   {
//     regs[KEY] = 4;
//     while (!digitalRead(K3))
//       ;
//   }
//   Scanled();
//   delay(5);
// }

// // Chuyen so sang LED 7 doan
// void toDisplay(int num1, int num2)
// {
//   temp_1[3] = num2 / 10;
//   temp_1[2] = num2 % 10;
//   temp_1[1] = num1 / 10;
//   temp_1[0] = num1 % 10;
// }

// // Set muc logic
// void setPinOut(char temp)
// {
//   for (int i = 0; i < 8; i++)
//   {
//     if (temp & 0x01)
//       digitalWrite(PinOut[i], HIGH);
//     else
//       digitalWrite(PinOut[i], LOW);
//     temp = temp >> 1;
//   }
// }

// // Scan LED
// void Scanled()
// {
//   unsigned char ch;

//   digitalWrite(ctr[index == 0 ? 3 : (index - 1)], HIGH);

//   ch = temp_1[index];
//   setPinOut(code7seg[ch]);
//   digitalWrite(ctr[index], LOW);
//   index++;
//   if (index >= 4)
//     index = 0;
// }