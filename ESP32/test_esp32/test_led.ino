/* Es necesrio tener instalada la extensión Adafruit NeoPixel
   El programa enciende el led interno de la placa con los tres colores 
   La placa debe estar conectada en el puerto UART y seleccionado el tipo ESP32S3 Dev Module 
   Si no reconoce la placa mantener pulsado reset antes de conectar */

#include <Adafruit_NeoPixel.h>

#define LED_BUILTIN 38  // Generalmente, el pin del LED incorporado en el ESP32 es el GPIO 2

Adafruit_NeoPixel LED_RGB(1,48,NEO_GRBW + NEO_KHZ800);

void setup() {
  LED_RGB.begin();
  LED_RGB.setBrightness(150);
}

void loop() {
  LED_RGB.setPixelColor(0,uint32_t(LED_RGB.Color(255,0,0)));
  LED_RGB.show();
  delay(1000);

  LED_RGB.setPixelColor(0,uint32_t(LED_RGB.Color(0,255,0)));
  LED_RGB.show();
  delay(1000);

  LED_RGB.setPixelColor(0,uint32_t(LED_RGB.Color(0,0,255)));
  LED_RGB.show();
  delay(1000);
}
