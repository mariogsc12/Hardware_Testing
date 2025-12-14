#include <WifiManager.hpp>
#include <WiFi.h>
#include <Arduino.h>


WifiManager::WifiManager(const char* _ssid, const char* _password, int _length, int _sample_time):
    server(80),
    ssid(_ssid),
    password(_password),
    data_length(_length),
    message(_length),
    sample_time(_sample_time)
{
}

WifiManager::~WifiManager()
{
}

void WifiManager::initialize(){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    initialize_server();
}

void WifiManager::initialize_server(){
    server.on("/", [this]() {
        String content = "";
        content += "<html><body>";
        content += "<h1>Sensor Readings </h1>";
        content += "<div id='sensorData'>Loading data...</div>";
        content += "<script>";
        content += "function fetchSensorData() {";
        content += "fetch('/data').then(response => response.text()).then(data => {";
        content += "document.getElementById('sensorData').innerText = data;";
        content += "}).catch(error => console.error('Error:', error));";
        content += "}";
        content += "setInterval(fetchSensorData, " + String(sample_time) + ");"; 
        content += "</script>";
        content += "</body></html>";
    
        server.send(200, "text/html", content);
    });

    // HTTP status code 200: OK (successful response) 
    server.on("/data", [this]() {
        String data = serialized_message(message);
        server.send(200, "text/plain", data);
    });

    server.begin();
}

void WifiManager::handle() {
    server.handleClient();
}

String WifiManager::serialized_message(const Message& message) {
    String serialized = "";
    for (int i = 0; i < data_length; i++) {
        serialized += String(*(message.data[i].value),MESSAGE_DATA_PRECISION);
        if (i < data_length - 1) {
            serialized += ",";
        }
    }
    return serialized;
}

void WifiManager::fill_names(const char** data_names) {
    for (int i = 0; i < DATA_LENGTH; i++) {
        strncpy(message.data[i].name, data_names[i], sizeof(message.data[i].name) - 1);
        message.data[i].name[sizeof(message.data[i].name) - 1] = '\0'; 
    }
}

void WifiManager::link_data(float** variables) {
    for (int i = 0; i < DATA_LENGTH; i++) {
        message.data[i].value = variables[i];
    }
}