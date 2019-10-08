#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include "TM1637.h"

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;  
const uint16_t node02 = 02;  
unsigned long reply = 01;
unsigned long reset = 2;
unsigned long tester = 0;
unsigned long incomingData=0;


#define CLK 4//Pins for TM1637       
#define DIO 5

TM1637 tm(CLK,DIO);

void setdisplaynumber(){
  tm.dispNumber(0);
  tester = 0; 
}

void setup() {

  attachInterrupt(digitalPinToInterrupt(reset), setdisplaynumber, HIGH);

  tm.init();

  delay(1500);

  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
      Serial.begin(9600);
      pinMode(reset, INPUT_PULLUP);
}

void loop() {
  network.update();

  while ( network.available() ) {
    RF24NetworkHeader header;
    while(1){
      bool ok = network.read(header, &incomingData, sizeof(incomingData));
      Serial.print(incomingData);
      if (ok)break;
    
    }
if(tester == 0){
           
      tm.dispNumber(incomingData);
     
      tester++;}
    
  }
}
