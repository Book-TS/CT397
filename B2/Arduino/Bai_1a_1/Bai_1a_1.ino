char PinOut[] = {22,23,24,25,26,27,28,29};
unsigned char tbl[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void blinkLED(int n);
void setPinOut(char temp);
void shiftLeft();

void setup() {
  for(int i=0;i<8;i++)    pinMode(PinOut[i], OUTPUT);
  blinkLED(5);
}

void loop() {
  shiftLeft();
  delay(1000);
}

void setPinOut(char temp) { 
  for(int i=0;i<8;i++) {
    if(temp&0x01)     digitalWrite(PinOut[i],HIGH);
    else              digitalWrite(PinOut[i],LOW);
    temp=temp>>1;
  }
}

// Chop tat LED
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
