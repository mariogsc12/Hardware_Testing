float speed, control_action;
unsigned long previousMillis = 0;
const int interval = 20;
String message;

void setup() {
  Serial.begin(115200);
  speed = 0.5;
  control_action = 100.7;
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    speed++;
    control_action++;
    message = String(millis()) + "," + String(control_action)+ "," + String(speed) ;
    Serial.println(message);
  }
}
