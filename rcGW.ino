#include <SPI.h>
#include <Ethernet.h>
#include <stdlib.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(8,9);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02};
IPAddress ip(192,168,1,177);
EthernetServer server(80);

char c;
char command[16];
boolean incoming = 0;

void setup(){
  
  Ethernet.begin(mac, ip);
  server.begin();
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
// For debug
  Serial.begin(9600);

}

void loop(){
 
  EthernetClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        c = client.read();
        if (c == '$') incoming = 1;
        if (incoming == 1){
         
// Get the commands:
          for (int x=0 ; x<16 ; x++){
          c = client.read();
          command[x] = c;
          radio.write( &c, sizeof(unsigned long) );
// For debug
          Serial.print(c);
              


// Send DATA to nrf24l01+ destination

      }
      incoming = 0;
      }
    }
  }
} 
 
delay(1);
client.stop();

} 
