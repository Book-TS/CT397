#include<Arduino.h>

char PinOut[] = {22,23,24,25,26,27,28,29};
unsigned char tbl[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void blinkLED(int n);
void setPinOut(char temp);
void shiftLeft();
void shiftLeft_1();
void shiftRight();
void shiftRight_1();
void brightShiftLeft();
void brightShiftRight();

void setup() {
  for(int i=0;i<8;i++)    pinMode(PinOut[i], OUTPUT);
  blinkLED(5);
}

void loop() {
  shiftLeft();
  // shiftLeft_1();
  shiftRight();
  // shiftRight_1();
  brightShiftLeft();
  brightShiftRight();
}

void setPinOut(char temp) { 
  for(int i=0;i<8;i++) {
    if(temp&0x01)     digitalWrite(PinOut[i],HIGH);
    else              digitalWrite(PinOut[i],LOW);
    temp=temp>>1;
  }
}

void blinkLED(int n) { 
  for(int i=0; i<n; i++) {
    setPinOut(0xff);
    delay(500);
    setPinOut(0x00);
    delay(500);
  }
}

// Dich tu phai sang trai
void shiftLeft() {
   for(int i=0; i <= 7; i++) {
    setPinOut(tbl[i]);
    delay(500);
  }
}

// Dich tu phai sang trai
void shiftLeft_1() {
  char temp = 0x01; 
  for(int i=0; i<8; i++) {
    setPinOut(temp); 
    delay(500); 
    temp = temp<<1;
  }
}

// Dich tu trai sang phai
void shiftRight() {
  for(int i=7; i>=0; i--) {
    setPinOut(tbl[i]);
    delay(500);
  }
}

// Dich tu trai sang phai        /*?*/
void shiftRight_1() {
  char temp = 0x80; 
  for(int i=0; i<8; i++) {
    setPinOut(temp); 
    delay(500); 
    temp = temp>>1;
  }
}

// Sang dan tu phai sang trai
void brightShiftLeft() {
  char temp = 0x01; 
  for(int i=0; i<8; i++) {
    setPinOut(temp); 
    delay(500); 
    temp = (temp<<1) + 0x01;
  }
}

// Sang dan tu trai sang phai       /*?*/
void brightShiftRight() {
  char temp = 0x80; 
  for(int i=0; i<8; i++) {
    setPinOut(temp); 
    delay(500); 
    temp = temp>>1;
  }
}