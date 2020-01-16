#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 4); // CE, CSN

const byte address_read[6] = "00001";
const byte address_write[6] = "00002";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address_write);
  radio.openReadingPipe(1, address_read);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

int counter = 1;

void loop() {
  char msgSend[] = "Hello Uno!";

  Serial.print("Pesan NodeMCU: ");
  Serial.println(msgSend);
  radio.openWritingPipe(address_write);
  radio.write(&msgSend, sizeof(msgSend));
  radio.startListening();
  delay(200);

  Serial.print("Pesan Arduino: ");
  if (radio.available()) {
    char msgRcv[32] = "";
    radio.read(&msgRcv, sizeof(msgRcv));
    Serial.println(msgRcv);
  }
  else {
    Serial.println("Radio Unavailable");
  }
  radio.stopListening();
}
