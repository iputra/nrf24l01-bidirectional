#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address_write[6] = "00001";
const byte address_read[6] = "00002";

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address_write);
  radio.openReadingPipe(1, address_read);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  char msgSend[] = "Hello MCU!";
  Serial.print("Pesan Uno: ");
  Serial.println(msgSend);
  radio.openWritingPipe(address_write);
  radio.write(&msgSend, sizeof(msgSend));
  radio.startListening();
  delay(200);

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  else {
    Serial.println("Radio Unavailable");
  }
  radio.stopListening();
}
