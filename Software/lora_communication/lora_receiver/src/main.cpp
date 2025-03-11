#include <SPI.h>
#include <LoRa.h>

const long frequency = 433E6; // LoRa Frequency

const int csPin = 9;          // LoRa radio chip select
const int resetPin = 15;      // LoRa radio reset
const int irqPin = 4;         // LoRa interrupt pin

void setup() {
  Serial.begin(115200); // Initialize serial communication
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    while (1); // Stop execution if initialization fails
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String receivedMessage = "";

    // Read the received packet
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // Split the received message by commas and print each value
    int startIndex = 0;
    while (startIndex < receivedMessage.length()) {
      int commaIndex = receivedMessage.indexOf(',', startIndex);
      if (commaIndex == -1) {
        // No more commas, take the rest of the string
        commaIndex = receivedMessage.length();
      }

      String value = receivedMessage.substring(startIndex, commaIndex);
      Serial.print(value); // Print the individual value

      // Print a comma only if it's not the last value
      if (commaIndex != receivedMessage.length()) {
        Serial.print(',');
      }

      startIndex = commaIndex + 1; // Move to the next part of the string
    }
    Serial.println(); // New line after the full message
  }

  delay(10); // Small pause
}
