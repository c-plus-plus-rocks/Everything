#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <RF24.h>

int gy_x, gy_y;

int servop1 = 4;
int servop2 = 5;

#define LIS3DH_CLK 6
#define LIS3DH_MISO 20
#define LIS3DH_MOSI 21
// Used for hardware & software SPI
#define LIS3DH_CS 10
//software SPI

    RF24 radio(8, 9); // CE, CSN         
    const byte address[6] = "00001"; 

Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);

void setup(){
    radio.begin();   
    radio.openWritingPipe(address); 
    radio.setPALevel(RF24_PA_MIN);  
    radio.stopListening();          
  Serial.begin(9600);
  Serial.println("LIS3DH test!");  
  if (! lis.begin(0x18)) {   
    Serial.println("Try again, couldn't start");
  }
  Serial.println("LIS3DH found!");
}

void loop(){
  lis.read();      

  sensors_event_t event;
  lis.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x);
  Serial.print(" Y: "); Serial.print(event.acceleration.y);
  Serial.print(" Z: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2 ");

  Serial.println();

  delay(200);

gy_x = event.acceleration.x;
gy_y = event.acceleration.y;

Serial.println(gy_y);
Serial.println(gy_x);


radio.write(&gy_x, sizeof(gy_x));
radio.write(&gy_y, sizeof(gy_y));
Serial.println("test");

delay(100);


}
