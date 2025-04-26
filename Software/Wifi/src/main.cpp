#include <WiFi.h>
#include <WebServer.h>
#include <WifiManager.hpp>


const char* WIFI_SSID = "WifiRobot";
const char* WIFI_PSW = "SelfBalancingRobot";

WifiManager wifi_manager(WIFI_SSID, WIFI_PSW, DATA_LENGTH, WIFI_SAMPLE_TIME);
const char* names[] = {"time", "input_yaw", "input_throttle", "input_switch", "control_action_left", "control_action_right", "speed_left", "speed_right", "voltage", "imu_pitch", "imu_yaw"};

// Variables de sensores
float time_value, pwm1, pwm2, pwm3, ca1, ca, vel1, vel2, volt, pitch, yaw;
float* sensors[DATA_LENGTH] = { &time_value, &pwm1, &pwm2, &pwm3, &ca1, &ca, &vel1, &vel2, &volt, &pitch, &yaw };

unsigned long last_update = 0; 
unsigned long current_time = 0;

void setup() {
  Serial.begin(115200); 
  
  wifi_manager.link_data(sensors);    
  wifi_manager.fill_names(names);     
  wifi_manager.initialize();
}

void loop() {
  
  current_time = millis();
  
  // Simulation of the variable changes 
  if (current_time - last_update >= WIFI_SAMPLE_TIME) {  
    last_update += WIFI_SAMPLE_TIME;
    
    time_value = (float)current_time;
    pwm1 = sin(current_time / 500.0) * 100;       
    pwm2 = cos(current_time / 500.0) * 100;
    pwm3 = (current_time % 1000) / 10.0;           
    ca1  = (current_time % 2000) / 20.0;           
    ca   = random(0, 100) / 1.0;                   
    vel1 = random(-50, 50) / 1.0;                  
    vel2 = random(-50, 50) / 1.0;
    volt = 12.0 + sin(current_time / 1000.0);       
    pitch = sin(current_time / 700.0) * 10.0;       
    yaw = cos(current_time / 700.0) * 10.0;         
    
  }
  wifi_manager.handle();
}
