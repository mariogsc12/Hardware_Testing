#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

const long frequency = 433E6; // LoRa Frequency

const int csPin = 4;          // LoRa radio chip select
const int resetPin = 2;       // LoRa radio reset
const int irqPin = 15;        // Change for your board; must be a hardware interrupt pin

int g_msg2 = 20;
int g_msg3 = 30;
int g_msg4 = 40;
int g_msg5 = 50;
int g_msg6 = 60;
int g_msg7 = 70;
int g_msg8 = 80;

void setup() {
  Serial.begin(115200); // Initialize serial communication
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true); // If failed, stop execution
  }

  Serial.println("LoRa init succeeded.");
}

void sendLoRaMessage() {
  unsigned long currentMillis = millis(); // Get the time in milliseconds since the program started

  // Create a message with the current time and other values separated by commas
  String message = String(currentMillis) + "," + String(g_msg2) + "," + String(g_msg3) + "," +
                   String(g_msg4) + "," + String(g_msg5) + "," + String(g_msg6) + "," +
                   String(g_msg7) + "," + String(g_msg8);

  LoRa.beginPacket();       // Start a new LoRa packet
  LoRa.print(message);      // Add the message to the packet
  LoRa.endPacket();         // Finish and send the packet

  Serial.print("Sent message: ");
  Serial.println(message);  // Print the message for debugging
}

void loop() {
  static unsigned long lastSendTime = 0;
  unsigned long currentTime = millis();

  // Send a message every 1000 milliseconds (1 second)
  if (currentTime - lastSendTime >= 1000) {
    lastSendTime = currentTime;
    sendLoRaMessage();
  }
}
