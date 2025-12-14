#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

const long frequency = 433E6; // LoRa Frequency

const int csPin = 4;          // LoRa radio chip select
const int resetPin = 2;       // LoRa radio reset
const int irqPin = 15;        // Change for your board; must be a hardware interrupt pin

float g_msg2 = 50.0;  // battery
int g_msg3 = 20;      // commandThrottle
int g_msg4 = -20;     // commandSteering
int g_msg5 = 1;       // RcMode
float g_msg6 = 0.5;   // pitch
float g_msg7 = 5.5;   // yaw
int g_msg8 = 80;      // left_motor
int g_msg9 = -80;     // right_motor

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
  String message = String(currentMillis/1000) + "," + String(g_msg2) + "," + String(g_msg3) + "," +
                   String(g_msg4) + "," + String(g_msg5) + "," + String(g_msg6) + "," +
                   String(g_msg7) + "," + String(g_msg8) + "," + String(g_msg9);

  LoRa.beginPacket();       // Start a new LoRa packet
  LoRa.print(message);      // Add the message to the packet
  LoRa.endPacket();         // Finish and send the packet

  Serial.print("Sent message: ");
  Serial.println(message);  // Print the message for debugging
}

void loop() {
  static unsigned long lastSendTime = 0;
  unsigned long currentTime = millis();

  // Send a message every 500 milliseconds (1 second)
  if (currentTime - lastSendTime >= 500) {
    lastSendTime = currentTime;
    sendLoRaMessage();
  }
}
