#include <lib/lora.hpp>
#include <LoRa.h>

Lora::Lora(const int NSS, const int RST, const int DID0, const long freq):
                pin_NSS(NSS),
                pin_RST(RST),
                pin_DID0(DID0),
                frequency(freq)  
{

}

bool Lora::initialize()
{
    LoRa.setPins(pin_NSS, pin_RST, pin_DID0);

    if (!LoRa.begin(frequency)) {
        Serial.println("ERROR - LoRa init failed. Check the connections."); 
        return false;
    }

    // Serial.println("LoRa init succeeded.");
    return true;
}

void Lora::sendMsg(String message)
{
    LoRa.beginPacket();       
    LoRa.print(message);      
    LoRa.endPacket();         

    // Print the message for debugging
    Serial.print("Sent message: ");
    Serial.println(message);  
}

String Lora::receiveMsg()
{
    String receivedMessage = "";

    int packetSize = LoRa.parsePacket();

    if (packetSize) {
        // Read the received packet
        while (LoRa.available()) {
        receivedMessage += (char)LoRa.read();
        }

        // Split the received message by commas and print each value
        int startIndex = 0;
        while (startIndex < receivedMessage.length()) 
        {
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
        Serial.println(); // New line after the full message (message terminator)
    }

    return receivedMessage;
}