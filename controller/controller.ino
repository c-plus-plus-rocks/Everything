//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

float joyval;
int joy_pin = A2;

void setup()
{
Serial.begin(9600);

     radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
} 

void loop()
{  joyval = analogRead(joy_pin);
delay(100); 
  radio.write(&joyval, sizeof(joyval));

delay(1000);
  }

