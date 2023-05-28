#include <SPI.h>
#include <LoRa.h>

// LoRa settings
#define LORA_CS_PIN 10
#define LORA_RST_PIN 9
#define LORA_IRQ_PIN 2
#define LORA_FREQUENCY 433E6 // Set frequency to 915MHz (adjust according to your region)

// Minimum and maximum packet sizes
#define MIN_PACKET_SIZE 10
#define MAX_PACKET_SIZE 200

// Number of packets to send
#define NUM_PACKETS 10

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_IRQ_PIN);
  
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }

  // Set spreading factor (adjust based on your requirements)
  LoRa.setSpreadingFactor(7);

  // Set signal bandwidth (adjust based on your requirements)
  LoRa.setSignalBandwidth(125E3);
}

void loop() {
  // Loop to send packets
  for (int i = 0; i < NUM_PACKETS; i++) {
    // Generate a random packet size
    int packetSize = random(MIN_PACKET_SIZE, MAX_PACKET_SIZE + 1);

    // Generate random payload data
    byte payload[packetSize];
    for (int j = 0; j < packetSize; j++) {
      payload[j] = random(256);
    }

    // Send packet
    LoRa.beginPacket();
    LoRa.write(payload, packetSize);
    LoRa.endPacket();

    // Wait for some time before sending the next packet
    delay(1000);
  }
}
