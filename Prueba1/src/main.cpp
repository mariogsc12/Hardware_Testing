#include <Arduino.h>
#include <utilities/Metro.h>

Metro sample_time(100);

void setup() {
  Serial.begin(115200);
  
}

void loop() {
  if(sample_time.check()==1)
  {
    Serial.println("Hola");
  }
}
