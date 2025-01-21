#ifndef LORA_HPP
#define LORA_HPP

#include <Arduino.h>

class Lora
{
    private:
        const int pin_NSS;         // LoRa radio chip select
        const int pin_RST;         // LoRa radio reset
        const int pin_DID0;        // LoRa enable interrupts
        const long frequency;
    public:
        Lora(const int, const int, const int, const long);
        ~Lora();

        bool initialize();
        void sendMsg(String);
        String receiveMsg();
};

#endif