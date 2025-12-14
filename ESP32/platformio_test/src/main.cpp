#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define POT_PIN 10

Adafruit_NeoPixel LED_RGB(1,48,NEO_GRBW + NEO_KHZ800);

int potVal=0;

void setup() {
  Serial.begin(115200);
  LED_RGB.begin();
  LED_RGB.setBrightness(150);
}

void loop() {
  potVal=analogRead(POT_PIN);
  potVal = map(potVal,0,1023,0,255);
  LED_RGB.setPixelColor(0,uint32_t(LED_RGB.Color(0,potVal,0)));
  LED_RGB.show();
  Serial.print(">PotVal:"); Serial.println(potVal);
  delay(200);
}