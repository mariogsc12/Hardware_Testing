#include <Arduino.h>
#include <RF24.h>

// NRF24L01 Pinout
#define CE 3
#define CSN 10

RF24 radio(CE, CSN);

const byte canalId[6] = "00001"; // Communication channel

void setup()
{
    Serial.begin(115200); // Debugging output
    radio.begin();
    //radio.setChannel(5);
    radio.setPALevel(RF24_PA_MIN);
    radio.openReadingPipe(0, canalId);
    radio.startListening();
}

void loop()
{
    char receivedBuffer[32]; // Buffer to store the received data
    if (radio.available())
    {
        radio.read(receivedBuffer, sizeof(receivedBuffer));

        // Debugging output
        Serial.print("Received raw: ");
        Serial.print(receivedBuffer);

        // Parse the received string
        int receivedData[3];
        sscanf(receivedBuffer, "%d,%d,%d", &receivedData[0], &receivedData[1], &receivedData[2]);

        // Print the received data
        Serial.print("- Parsed: ");
        Serial.print(receivedData[0]);
        Serial.print(", ");
        Serial.print(receivedData[1]);
        Serial.print(", ");
        Serial.println(receivedData[2]);
    }
}
