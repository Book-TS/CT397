#include <ModbusSlave.h>
// Modbus slave configuration parameters
#define DAT 12
#define CLK 10
#define STR 11


// SlaveId
const unsigned char TX_EN = 2; // Pin TX_enable
const unsigned char SLAVE = 1; 
const long          BAUD = 9600;

// Create new mbs instance 
ModbusSlave mbs;

// Slave registers
enum {        
  COUNTER,    // Register 0 
  LED,    // Register 1 
  MB_REGS  // Dummy register. using 0 offset to keep size of array
};

// Global buffer
int regs[MB_REGS];

void setup(){
    pinMode(STR, OUTPUT);
    pinMode(DAT, OUTPUT);
    pinMode(CLK, OUTPUT);

  // Configure msb
  mbs.configure(0,SLAVE,BAUD,TX_EN);
  pinMode(13,OUTPUT);
}

int i=0,count=0, timecount = 0;
void loop()
{
  // Pass current register values to mbs
  mbs.update(regs, MB_REGS);

  // Store the values in the Modbus registers
  if (timecount++>100){
      timecount = 0;
      regs[COUNTER] = count++;
  }  
  // Only for serial monitor visualizing
  ShiftOut(regs[LED]);
  delay(10);
}

//----------------------
void ShiftOut(char dat){
    digitalWrite(STR, LOW);
    for(int i=0;i<8;i++){
      if(dat&0x80) digitalWrite(DAT,LOW);
      else         digitalWrite(DAT,HIGH);
      dat=dat<<1;
      digitalWrite(CLK, LOW);        
      digitalWrite(CLK, HIGH);        
    }
    digitalWrite(STR, HIGH);        
}

