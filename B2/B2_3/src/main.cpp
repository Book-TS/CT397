#include <Arduino.h>

#define VR1   A3
#define VR2   A2
#define VR3   A4
#define LM35  A0
#define LEDR  13
#define LEDG  11
#define LEDB  12
#define K0    42

// LED 7 Doan
char PinOut[] = {22,23,24,25,26,27,28,29};
const char ctr[] = {37, 36, 35, 34};
const unsigned char code7seg[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
char temp_1[4] = {0, 0, 0, 0};
int index = 0;

unsigned long oldtime_1 = 0;
unsigned long oldtime_2 = 0;
unsigned long oldtime_3 = 0;
unsigned long time_1    = 5;
unsigned long time_2    = 500;
unsigned long time_3    = 10;

int val1, val2, val3, val4 = 0;
int counter = 0;

void setPinOut(char temp);
void blinkLED(int n);
void toDisplay(int counter);
void pinOut(char temp);
void Scanled();

void yc1_setUp(void);
void yc2_setUp(void);
void yc3_setUp(void);
void yc4_setUp(void);
void yc1_voidLoop(void);
void yc2_voidLoop(void);
void yc3_voidLoop(void);
void yc4_voidLoop(void);

void setup() {
  Serial.begin(9600);
  yc4_setUp();
}

void loop() {
  yc4_voidLoop();
}

void yc1_setUp(void) {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  analogWrite(LEDR, 0); 
  analogWrite(LEDG, 0);
  analogWrite(LEDB, 0);
  for(int i=0; i<8; i++)    
    pinMode(PinOut[i], OUTPUT);
  blinkLED(5);
}

void yc2_setUp(void) {
  for(int i=0; i<8; i++)    
    pinMode(PinOut[i], OUTPUT);
  for(int i=0;i<4;i++) pinMode(ctr[i], OUTPUT);

  analogReference(DEFAULT);
  toDisplay(0);
  Scanled();
  delay(1);
}

void yc3_setUp(void) {
  for(int i=0; i<8; i++)    
    pinMode(PinOut[i], OUTPUT);
  for(int i=0;i<4;i++) pinMode(ctr[i], OUTPUT);

  analogReference(DEFAULT);
  toDisplay(0);
  Scanled();
  delay(1);
}

void yc4_setUp(void) {
  pinMode(K0, INPUT_PULLUP);
  for(int i=0; i<8; i++)    
    pinMode(PinOut[i], OUTPUT);
  for(int i=0;i<4;i++) pinMode(ctr[i], OUTPUT);
  analogReference(DEFAULT);
  toDisplay(0);
  Scanled();
  delay(1);
}

// Doc bien tro va xuat PWM ra LED RGB
void yc1_voidLoop(void) {
  val1 = analogRead(VR1);
  val1 = map(val1, 0, 1024, 0, 255);
  analogWrite(LEDR, val1);

  val2 = analogRead(VR2);
  val2 = map(val2, 0, 1024, 0, 255);
  analogWrite(LEDG, val2);

  val3 = analogRead(VR3);
  val3 = map(val3, 0, 1024, 0, 255);
  analogWrite(LEDB, val3);
 
  delay(200);
}

// Doc bien tro hien thi LED 7 doan
void yc2_voidLoop(void) {
  if ((unsigned long) (millis() - oldtime_1) > time_1) {
    Scanled();
    oldtime_1 = millis();
  }
  if ((unsigned long) (millis() - oldtime_2) > time_2) {
    val1 = analogRead(VR1);
    val1 = map(val1, 0, 1024, 0, 5000);
    Serial.println(val1);
    toDisplay(val1);
    oldtime_2 = millis();
  }
}

// Doc LM35 va hien thi LED 7 doan
void yc3_voidLoop(void) {
  if ((unsigned long) (millis() - oldtime_1) > time_1) {
    Scanled();
    oldtime_1 = millis();
  }
  if ((unsigned long) (millis() - oldtime_2) > time_2) {
    val4 = map(analogRead(LM35), 0, 1023, 0, 5000)/10;        // 10mV/oC
    Serial.println(val4);
    toDisplay(val4);
    oldtime_2 = millis();
  }
}

// Yeu cau 4
void yc4_voidLoop(void) {
  if ((unsigned long) (millis() - oldtime_1) > time_1) {
    Scanled();
    oldtime_1 = millis();
  }
  if ((unsigned long) (millis() - oldtime_2) > time_2) {
    if(digitalRead(K0)==0) {
      if(counter >= 4) counter = 1;
      else counter++;
      Serial.println(counter);
      while (!digitalRead(K0));
    }
    if(counter == 1) toDisplay(val1);
    else if(counter == 2) toDisplay(val2);
    else if(counter == 3) toDisplay(val3);
    else if (counter == 4) toDisplay(val4);
    
    oldtime_2 = millis();
  }
  if ((unsigned long) (millis() - oldtime_3) > time_3) {
    val1 = map(analogRead(VR1), 0, 1023, 0, 5000);
    val2 = map(analogRead(VR2), 0, 1023, 0, 5000);
    val3 = map(analogRead(VR3), 0, 1023, 0, 5000);
    val4 = map(analogRead(LM35), 0, 1023, 0, 5000)/10;
    oldtime_3 = millis();
  }
}

// Set chan theo hex
void setPinOut(char temp) { 
  for(int i=0;i<8;i++) {
    if(temp&0x01)     digitalWrite(PinOut[i], HIGH);
    else              digitalWrite(PinOut[i], LOW);
    temp=temp>>1;
  }
}

// Ham blink LED
void blinkLED(int n) { 
  for(int i=0; i<n; i++) {
    setPinOut(0xff);
    delay(500);
    setPinOut(0x00);
    delay(500);
  }
}

// Chuyen so sang LED 7 doan
void toDisplay(int counter) {
  temp_1[3] = counter/1000;
  temp_1[2] = (counter%1000)/100;
  temp_1[1] = ((counter%1000)%100)/10;
  temp_1[0] = counter%10; 
}

// Set muc logic
void pinOut(char temp_2) { 
  for(int i=0; i<8; i++) {
    if(temp_2 & 0x01)   digitalWrite(PinOut[i], HIGH);
    else              digitalWrite(PinOut[i], LOW);
    temp_2=temp_2>>1;
  }
}

// Scan LED
void Scanled() {
    unsigned char ch;

    digitalWrite(ctr[index==0?3:(index-1)], HIGH);
    
    ch = temp_1[index];
    pinOut(code7seg[ch]);
    
    digitalWrite(ctr[index], LOW);
    index++;
    if (index>=4) index = 0;
}
