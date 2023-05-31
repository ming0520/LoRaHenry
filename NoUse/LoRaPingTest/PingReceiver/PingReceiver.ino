#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define DI0_PIN 2

unsigned long receiveTimestamp;
unsigned long sendTimestamp; // Declare sendTimestamp as a global variable

void setup() {
  Serial.begin(9600);
  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections!");
    while (1);
  }
}

void loop() {
  if (LoRa.parsePacket()) {
    String message = "";

    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    if (message == "PING") {
      receiveTimestamp = millis();
      sendPong();
      calculateLatency();
    }
  }
}

void sendPong() {
  LoRa.beginPacket();
  LoRa.print("PONG");
  LoRa.endPacket();
}

void calculateLatency() {
  unsigned long latency = receiveTimestamp - sendTimestamp;
  Serial.print("Latency: ");
  Serial.print(latency);
  Serial.println(" ms");
}
