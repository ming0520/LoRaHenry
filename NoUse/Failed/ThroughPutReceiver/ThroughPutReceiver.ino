#include <SPI.h>
#include <LoRa.h>

#define BAND 433E6 // Frequency band for SX1278 module

#define MESSAGE_SIZE 100 // Size of the message to transmit
#define NUM_MESSAGES 9999 // Number of messages to transmit for throughput calculation

unsigned long startTime;
unsigned long endTime;
unsigned int messageCount;

void setup() {
  Serial.begin(9600);

  while (!Serial);

  Serial.println("LoRa Throughput Test");

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  LoRa.setSpreadingFactor(12); // Set spreading factor (SF)
  LoRa.setSignalBandwidth(125000); // Set signal bandwidth (Hz)
  LoRa.setCodingRate4(5); // Set coding rate
  LoRa.enableCrc(); // Enable CRC calculation

  Serial.println("LoRa initialization successful. Ready to transmit.");
}

void loop() {
  if (messageCount < NUM_MESSAGES) {
    // Generate random message data
    byte message[MESSAGE_SIZE];
    for (int i = 0; i < MESSAGE_SIZE; i++) {
      message[i] = random(0, 256);
    }

    // Start timer
    startTime = micros();

    // Send message
    LoRa.beginPacket();
    LoRa.write(message, MESSAGE_SIZE);
    LoRa.endPacket();

    // Stop timer
    endTime = micros();

    // Calculate throughput
    unsigned long elapsedTime = endTime - startTime;
    float throughput = (float)(MESSAGE_SIZE * 8 * 1000000) / (float)elapsedTime;

    Serial.print("Message ");
    Serial.print(messageCount + 1);
    Serial.print(": ");
    Serial.print(throughput, 2);
    Serial.println(" bps");

    messageCount++;
  }
}