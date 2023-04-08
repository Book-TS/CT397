#define K1 47
#define K2 46
#define K3 43
#define COM 33

const char pin7seg[] = {22, 23, 24, 25, 26, 27, 28, 29};
const char ctr[] = {37, 36, 35, 34};

// DEC: 1 = 1111 1001    DP G F E D C B A
const unsigned char code7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
char temp_1[4] = {0, 0, 0, 0};
int index = 0;
int counter = 0;

unsigned long oldtime_1 = 0;
unsigned long oldtime_2 = 0;
unsigned long time_1 = 5;
unsigned long time_2 = 500;

void toDisplay(int counter);
void pinOut(char temp);
void Scanled();

void setup()
{
  for (int i = 0; i < 8; i++)
    pinMode(pin7seg[i], OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(ctr[i], OUTPUT);

  pinMode(COM, OUTPUT);
  digitalWrite(COM, LOW);

  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
  
  toDisplay(counter);
  Scanled();
  delay(1);
}

void loop()
{
  if ((unsigned long)(millis() - oldtime_1) > time_1)
  {
    Scanled();
    oldtime_1 = millis();
  }

  if (digitalRead(K1) == 0)
  {
    counter++;
    toDisplay(counter);
    while (!digitalRead(K1))
      ;
  }
  if (digitalRead(K2) == 0)
  {
    counter--;
    toDisplay(counter);
    while (!digitalRead(K2))
      ;
  }
  if (digitalRead(K3) == 0)
  {
    counter = 0;
    toDisplay(counter);
    while (!digitalRead(K3))
      ;
  }
}

// Chuyen so sang LED 7 doan
void toDisplay(int counter)
{
  temp_1[3] = counter / 1000;
  temp_1[2] = (counter % 1000) / 100;
  temp_1[1] = ((counter % 1000) % 100) / 10;
  temp_1[0] = counter % 10;
}

// Set muc logic
void pinOut(char temp_2)
{
  for (int i = 0; i < 8; i++)
  {
    if (temp_2 & 0x01)
      digitalWrite(pin7seg[i], HIGH);
    else
      digitalWrite(pin7seg[i], LOW);
    temp_2 = temp_2 >> 1;
  }
}

// Scan LED
void Scanled()
{
  unsigned char ch;

  digitalWrite(ctr[index == 0 ? 3 : (index - 1)], HIGH);

  ch = temp_1[index];
  pinOut(code7seg[ch]);
  digitalWrite(ctr[index], LOW);
  index++;
  if (index >= 4)
    index = 0;
}
