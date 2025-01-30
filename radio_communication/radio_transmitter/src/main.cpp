#include <Arduino.h>
#include <libs/Metro.h>
#include <RF24.h>

// NRF24L01 Pinout
#define CE 4
#define CSN 5

Metro sampleTime(50); // Sample time: 50ms

RF24 radio(CE, CSN);

const byte canalId[6] = "00001";

const int bufferSize = 32; // Maximum payload size for NRF24L01
char buffer[bufferSize];   // Buffer to hold the formatted message

int data1 = 0; // Example data
int data2 = 1;
int data3 = 2;

void setup()
{
    Serial.begin(115200);
    radio.begin();
    radio.openWritingPipe(canalId);
    radio.setPALevel(RF24_PA_MIN); // Maximum range
    radio.stopListening();
}

void loop()
{
    if(sampleTime.check()==1)
    {
        // Format the data into the buffer as a string with a terminator \r\n
        int messageLength = snprintf(buffer, bufferSize, "%d,%d,%d\r\n", data1, data2, data3);
        // Send only the necessary bytes (messageLength)
        if (messageLength > 0 && messageLength <= bufferSize)
        {
            radio.write(buffer, messageLength); 
            Serial.print("Sent: "); // For debugging
            Serial.print(buffer); 
            Serial.print(" - bufferSize: ");
            Serial.println(messageLength);   
        }
        else
        {
            Serial.println("Error: Message exceeds buffer size!");
        }
        // Example: Update data for the next loop
        data1++;
        data2 += 2;
        data3 += 3;
    }

}
