#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>
#include <RF24_config.h>
#include <AFMotor.h>

AF_DCMotor motori(1,MOTOR12_64KHZ);
AF_DCMotor motord(2,MOTOR12_64KHZ);

char command[16];
int vel = 0;

RF24 radio(48,53);
const uint64_t pipes = 0xE8E8F0F0E1LL;

void setup() {
// Debug
    //pinMode(13, OUTPUT); //testigo de sw//
//    Serial.begin(9600);
    
    radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.setPayloadSize(sizeof(unsigned long));
    radio.openReadingPipe(1,pipes);
    radio.startListening();
    
    motori.setSpeed(vel);
    motord.setSpeed(vel);
}

void loop() {
 if (radio.available()) { 
  
// recibir DATA de nrf24l01+ origen
      radio.read(command, 16);
            
      char s1[2] = {command[0], '\0'};
      char s2[2] = {command[1], '\0'};
      char s3[2] = {command[2], '\0'};
      char s4[2] = {command[3], '\0'};   

      char i1[4] = {command[4], command[5], command[6], '\0'};
      char i2[4] = {command[7], command[8], command[9], '\0'};
      char d3[4] = {command[10], command[11], command[12], '\0'};
      char d4[4] = {command[13], command[14], command[15], '\0'};   
     
// Convert char to int:
      int s1i = atol (s1);
      int s2i = atol (s2);
      int s3i = atoi (s3);
      int s4i = atoi (s4);   

      int i1i = atol (i1);
      int i2i = atol (i2);
      int d3i = atoi (d3);
      int d4i = atoi (d4);   

// establecer velocidad de los motores segun posicion de la palanca
//    unsigned int spi = (i2i-90)+150;
//    unsigned int spd = (d3i-90)+150;
//    motori.setSpeed(spi);
//    motord.setSpeed(spd);

    motori.setSpeed(vel);
    motord.setSpeed(vel);

// Debug      
//      Serial.print(s1i);
//      Serial.print(s2i);
//      Serial.print(s3i);
//      Serial.println(s4i);

//      Serial.print(i1i);
//      Serial.print(i2i);
//      Serial.print(d3i);
//      Serial.println(d4i); 
      
//      Serial.print(spi);
//      Serial.println(spd); 
//      Serial.println(vel); 
      
// palancas para velocidad
      if (s1i == 1)  vel=50;//digitalWrite(13, HIGH);
      if (s2i == 1)  vel=150;
      if (s3i == 1)  vel=200;
      if (s4i == 1)  vel=250;
      if (s1i == 0 & s2i == 0 & s3i == 0 & s4i == 0) vel=0;
      

// motor alante
      if (i2i > 90)     alante();
// motor atras
      if (i2i < 90)     atras();
// motor derecha
      if (d3i > 90)     derecha();
// motor izquierda
      if (d3i < 90)     izquierda();
      
// motor parado eje XY
      if (d3i == 90 & i2i == 90)    parar();

 }
}

void alante(){
    motori.run(FORWARD);
    motord.run(FORWARD);
}
void atras(){
    motori.run(BACKWARD);
    motord.run(BACKWARD);
}
void derecha(){
    motori.run(FORWARD);
    motord.run(RELEASE);
}
void izquierda(){
    motori.run(RELEASE);
    motord.run(FORWARD);
}
void parar(){
    motori.run(RELEASE);
    motord.run(RELEASE);
}
