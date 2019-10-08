#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(9, 10);              // nRF24L01 (CE,CSN)
RF24Network network(radio);     // Include the radio in the network
uint16_t this_node = 01;       // Address of our node in Octal format ( 04,031, etc)m8
const uint16_t node00 = 00;     //Address of the Master
const unsigned long reply =01;  //1->7 like 01,02,...,07 then 8 ...
int buttonPin = 2;
bool LED_state=1;
RF24NetworkHeader header(node00);



 void State(){
         LED_state=0; 
 }



void setup() {
  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  Serial.begin(9600);   
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(3, OUTPUT);
   
}



void loop() {
  
  network.update();

  attachInterrupt(digitalPinToInterrupt(buttonPin), State, LOW);
  
  if(!LED_state){
    
  bool ok= network.write(header, &reply, sizeof(reply));
  
  Serial.print(reply);
  LED_state=1;
  digitalWrite(3,HIGH);
  delay(10000);
  digitalWrite(3,LOW);
  }
  
}
