#include <Nrf2401.h>
#include <NRF24.h>
#include <SPI.h>
#include <stdlib.h>

#define alante_c     sw1
#define atras_c      sw2
#define derecha_c    sw3
#define izquierda_c  sw4

#define alante    u
#define atras     d
#define derecha   r
#define izquierda l

boolean sw1;
boolean sw2;
boolean sw3;
boolean sw4;

boolean alante;
boolean atras;
boolean derecha;
boolean izquierda;

char c;
char command[16];

RF24 radio(48,53);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup() {

    radio.begin();  
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);

    radio.startListening();

    Serial.begin(9600);
}

void loop() {

 while ( ! radio.available()) { 
  
// recibir DATA de nrf24l01+ origen

      unsigned long got_message;

      for (int x=0 ; x<16 ; x++){
      c = radio.read( &got_message, sizeof(unsigned long) );
      command[x] = c;
            
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
      
      Serial.print(s1i);
      Serial.print(s2i);
      Serial.print(s3i);
      Serial.println(s4i);

      Serial.print(i1i);
      Serial.print(i2i);
      Serial.print(d3i);
      Serial.println(d4i); 
      
// palancas para movimiento continuo
      if (s1i == '0')  sw1=0;
      if (s1i == '1')  sw1=1; 
      if (s2i == '0')  sw2=0; 
      if (s2i == '1')  sw2=1;
      if (s3i == '0')  sw3=0; 
      if (s3i == '1')  sw3=1;
      if (s4i == '0')  sw4=0; 
      if (s4i == '1')  sw4=1;

// motor alante
      if (i2i > 90)    u=1;
// motor atras
      if (i2i < 90)    d=1;
// motor parado eje Y
      if (i2i == 90) {
                      u=0;
                      d=0;
                     }
// motor derecha
      if (d3i > 90)    r=1;
// motor izquierda
      if (d3i < 90)    l=1;
// motor parado eje X
      if (d3i == 90) {
                      r=0;
                      l=0;
                     }


// activar motors segun valores swx o uprl
      }
 }
}
