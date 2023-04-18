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
// {            // Slave registers
//     KEY,     // Register 0
//     COUNTER, // Register 1
//     NUM1,    // Register 2
//     NUM2,    // Register 3
//     MB_REGS
// };

// int regs[MB_REGS];
// int i = 0, counter = 0, timer = 0;

// const char PinOut[] = {22, 23, 24, 25, 26, 27, 28, 29};

// void setPinOut(char temp);

// void setup()
// {
//     for (int i = 0; i < 8; i++)
//         pinMode(PinOut[i], OUTPUT);

//     pinMode(COM, OUTPUT);
//     digitalWrite(COM, LOW);
//     pinMode(K0, INPUT_PULLUP);
//     pinMode(K1, INPUT_PULLUP);
//     pinMode(K2, INPUT_PULLUP);
//     pinMode(K3, INPUT_PULLUP);

//     mbs.configure(0, SLAVE, BAUD, 2);
// }

// void loop()
// {
//     mbs.update(regs, MB_REGS);
//     setPinOut(regs[NUM1]);
//     if (timer++ > 20)
//     {
//         timer = 0;
//         counter++;
//         regs[COUNTER] = counter;
//     }

//     if (digitalRead(K0) == 0)
//     {
//         regs[KEY] = 1;
//         while (!digitalRead(K0))
//             ;
//     }
//     if (digitalRead(K1) == 0)
//     {
//         regs[KEY] = 2;
//         while (!digitalRead(K1))
//             ;
//     }
//     if (digitalRead(K2) == 0)
//     {
//         regs[KEY] = 3;
//         while (!digitalRead(K2))
//             ;
//     }
//     if (digitalRead(K3) == 0)
//     {
//         regs[KEY] = 4;
//         while (!digitalRead(K3))
//             ;
//     }
//     delay(50);
// }

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