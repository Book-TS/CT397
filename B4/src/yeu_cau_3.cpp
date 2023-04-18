#include <Arduino.h>
#include <ModbusMaster.h>

#define K0 42
#define K1 47
#define K2 46
#define K3 43
#define COM 33

ModbusMaster slave1(0, 1, 2);
enum
{ // Define addreses for reading
    KEYCODE,
    COUNTER,
    NUM1,
    NUM2,
    MB_REGS
};

int Regs[MB_REGS]; // vùng đệm chứa dữ liệu
int timecount = 0, count = 0;

const char PinOut[] = {22, 23, 24, 25, 26, 27, 28, 29};
const char ctr[] = {37, 36, 35, 34};

const unsigned char code7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
char temp_1[4] = {0, 0, 0, 0};
int index = 0;

void setPinOut(char temp);
void Scanled();
void toDisplay(int num1, int num2);

void setup()
{
    for (int i = 0; i < 8; i++)
        pinMode(PinOut[i], OUTPUT);
    for (int i = 0; i < 4; i++)
        pinMode(ctr[i], OUTPUT);
    pinMode(COM, OUTPUT);
    digitalWrite(COM, LOW);
    pinMode(K0, INPUT_PULLUP);
    pinMode(K1, INPUT_PULLUP);
    pinMode(K2, INPUT_PULLUP);
    pinMode(K3, INPUT_PULLUP);
   
    slave1.begin(9600);
}
void loop()
{
    if (slave1.readHoldingRegisters(NUM1, 2) == 0)
    {
        Regs[NUM1] = slave1.getResponseBuffer(0);
        Regs[NUM2] = slave1.getResponseBuffer(1);
        toDisplay(Regs[NUM1], Regs[NUM2]);

        slave1.clearResponseBuffer();
    }
    
    if (timecount++ > 2)
    {
        timecount = 0;
        Regs[COUNTER] = count++;
    }
    
    if (digitalRead(K0) == 0)
        Regs[KEYCODE] = 1;
    if (digitalRead(K1) == 0)
        Regs[KEYCODE] = 2;
    
    slave1.setTransmitBuffer(1, Regs[COUNTER]);
    slave1.setTransmitBuffer(0, Regs[KEYCODE]);
    slave1.writeMultipleRegisters(KEYCODE, 2);
    Scanled();
    delay(50);
}

void setPinOut(char temp)
{
  for (int i = 0; i < 8; i++)
  {
    if (temp & 0x01)
      digitalWrite(PinOut[i], HIGH);
    else
      digitalWrite(PinOut[i], LOW);
    temp = temp >> 1;
  }
}

// Scan LED
void Scanled()
{
  unsigned char ch;

  digitalWrite(ctr[index == 0 ? 3 : (index - 1)], HIGH);

  ch = temp_1[index];
  setPinOut(code7seg[ch]);
  digitalWrite(ctr[index], LOW);
  index++;
  if (index >= 4)
    index = 0;
}

void toDisplay(int num1, int num2)
{
  temp_1[3] = num2 / 10;
  temp_1[2] = num2 % 10;
  temp_1[1] = num1 / 10;
  temp_1[0] = num1 % 10;
}