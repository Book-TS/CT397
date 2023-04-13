#include <ModbusMaster.h>
#define DAT 12
#define CLK 10
#define STR 11

// Instantiate ModbusMaster object as slave ID 1
// Slave(Serial,SlaveID,txenpin);
ModbusMaster slave1(0,1,2); 
// Define addreses for reading
#define COUNTER 0 
#define LED     1 

//define the number of bits to read
#define bytesQty 2

void setup()
{
    pinMode(STR, OUTPUT);
    pinMode(DAT, OUTPUT);
    pinMode(CLK, OUTPUT);

  //Power on the USB for viewing data in the serial monitor. 
  //Serial.begin(9600);

  // Initialize Modbus communication baud rate
  slave1.begin(9600);
  //Print hello message
  //Serial.println("Modbus communication over RS-232");
  delay(100);
}

int count = 0;
int count2 = 0;
void loop()
{ 
  
 //----------Nhan du lieu tu SLAVE-------------
  int result =  slave1.readHoldingRegisters(COUNTER ,1);
  if (result != 0) {
    //If no response from the slave, print an error message. 
    //Serial.println("Communication error. Couldn't read from slave");
    delay(100);
  }else{ 
     int dat = slave1.getResponseBuffer(COUNTER); // doc du lieu tu vung nho
         ShiftOut(dat); // dua du lieu ra LED    
  }      
  //Clear the response buffer. 
  slave1.clearResponseBuffer();

  //----------Truyen du lieu xuong SLAVE-------------

  slave1.setTransmitBuffer(0,count++);
  slave1.writeMultipleRegisters(LED ,1);

 // thiet lap chu ky quet----------------
  delay(1000);
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

