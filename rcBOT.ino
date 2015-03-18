#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>
#include <RF24_config.h>
#include <AFMotor.h>

AF_DCMotor motori(1);
AF_DCMotor motord(2);

//#define motor_left_1    2
//#define motor_left_2    3
//#define motor_right_1   7
//#define motor_right_2   8

char command[16];

RF24 radio(48,53);
const uint64_t pipes = 0xE8E8F0F0E1LL;

void setup() {
    pinMode(13, OUTPUT); //testigo de sw//
    //pinMode(motor_left_1, OUTPUT);
    //pinMode(motor_left_2, OUTPUT);
    //pinMode(motor_right_1, OUTPUT);
    //pinMode(motor_right_2, OUTPUT);
    
    Serial.begin(9600);
    
    radio.begin();
    radio.openReadingPipe(1,pipes);
    radio.startListening();
    
    motori.setSpeed(255);
    motord.setSpeed(255);
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

// establecer velocidad de los motores
    motori.setSpeed(i2i);
    motord.setSpeed(d3i);

// Debug      
      Serial.print(s1i);
      Serial.print(s2i);
      Serial.print(s3i);
      Serial.println(s4i);

      Serial.print(i1i);
      Serial.print(i2i);
      Serial.print(d3i);
      Serial.println(d4i); 
      
// palancas para movimiento continuo
      if (s1i == 0)  parar();//digitalWrite(13, LOW);
      if (s1i == 1)  alante();//digitalWrite(13, HIGH);
      if (s2i == 0)  parar(); 
      if (s2i == 1)  atras();
      if (s3i == 0)  parar(); 
      if (s3i == 1)  derecha();
      if (s4i == 0)  parar(); 
      if (s4i == 1)  izquierda();

// motor alante
      if (i2i > 90)     alante();
// motor atras
      if (i2i < 90)     atras();
// motor parado eje Y
      if (i2i == 90)    parar();
// motor derecha
      if (d3i > 90)     derecha();
// motor izquierda
      if (d3i < 90)     izquierda();
// motor parado eje X
      if (d3i == 90)    parar();

 }
}

void alante(){
 motori.run(FORWARD);
 motord.run(FORWARD);
//digitalWrite(motor_left_1, HIGH);
//digitalWrite(motor_left_2, LOW);
//digitalWrite(motor_right_1, HIGH);
//digitalWrite(motor_right_2, LOW);
}
void atras(){
    motori.run(BACKWARD);
    motord.run(BACKWARD);
//digitalWrite(motor_left_1, LOW);
//digitalWrite(motor_left_2, HIGH);
//digitalWrite(motor_right_1, LOW);
//digitalWrite(motor_right_2, HIGH);
}
void derecha(){
    motori.run(FORWARD);
    motord.run(BACKWARD);
//digitalWrite(motor_left_1, HIGH);
//digitalWrite(motor_left_2, LOW);
//digitalWrite(motor_right_1, LOW);
//digitalWrite(motor_right_2, HIGH);
}
void izquierda(){
    motori.run(BACKWARD);
    motord.run(FORWARD);
//digitalWrite(motor_left_1, LOW);
//digitalWrite(motor_left_2, HIGH);
//digitalWrite(motor_right_1, HIGH);
//digitalWrite(motor_right_2, LOW);
}
void parar(){
    motori.run(RELEASE);
    motord.run(RELEASE);
//digitalWrite(motor_left_1, LOW);
//digitalWrite(motor_left_2, LOW);
//digitalWrite(motor_right_1, LOW);
//digitalWrite(motor_right_2, LOW);
//delay(25);
}
