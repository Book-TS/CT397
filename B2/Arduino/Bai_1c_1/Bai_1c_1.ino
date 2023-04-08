#define VR1   A3
#define VR2   A2
#define VR3   A4

#define LEDR  13
#define LEDG  11
#define LEDB  12

char PinOut[] = {22,23,24,25,26,27,28,29};

int val1, val2, val3;

void setPinOut(char temp);
void blinkLED(int n);

void setup() {
  Serial.begin(9600);
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

void loop() {
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
