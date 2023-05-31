// https://github.com/PaulStoffregen/RadioHead
#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  while (!Serial) ;

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  
  if (!rf95.init()) {
    Serial.println("LoRa module init failed.");
    while (1);
  }
  
  rf95.setFrequency(915.0);
  rf95.setTxPower(23);
  Serial.println("LoRa module initilzed!.");
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    
    if (rf95.recv(buf, &len)) {
      float snr = rf95.lastSNR();
      int rssi = rf95.lastRssi();
      
      Serial.print("Received message: ");
      Serial.println((char *)buf);
      Serial.print("SNR: ");
      Serial.print(snr);
      Serial.print(" dB, RSSI: ");
      Serial.print(rssi);
      Serial.println(" dBm");
    }
  }
}
