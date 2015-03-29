#include <SPI.h>
#include <Ethernet.h>
#include <stdlib.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

char c;
char command[16];
boolean incoming = 0;

RF24 radio(8,9);
const uint64_t pipes = 0xE8E8F0F0E1LL;

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02};
IPAddress ip(192,168,1,177);
EthernetServer server(80);

void setup(){
//  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  server.begin();
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPayloadSize(sizeof(unsigned long));
  radio.openWritingPipe(pipes);
}

void loop(){
 
  EthernetClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        c = client.read();
        if (c == '$') incoming = 1;
        if (incoming == 1){
         
          for (int x=0 ; x<16 ; x++){
          c = client.read();
          command[x] = c;
          radio.write(command, 16);

//        Serial.print(command);

      }
      incoming = 0;
      }
    }
  }
} 
 
Serial.print(command);

delay(1);
client.stop();
radio.powerDown(); 
//delay(1000);
radio.powerUp();

}
