#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <WebServer.h>

#define MESSAGE_DATA_PRECISION 2
#define DATA_LENGTH 11
#define WIFI_SAMPLE_TIME 100 

struct MessageVariable{
    char name[10];
    float* value;
};

struct Message {
    MessageVariable* data;
    Message(int length) {
        data = new MessageVariable[length];
    }
    ~Message() {
        delete[] data;
    }
};


class WifiManager
{
private:
    const char* ssid;
    const char* password;
    const int data_length;
    WebServer server;
    Message message;
    int sample_time; //miliseconds
public:
    WifiManager(const char* ssid, const char* password, int n_data, int sample_time);
    ~WifiManager();
    void initialize();
    void initialize_server();
    void fill_names(const char** data_names);
    String serialized_message(const Message& message);
    void link_data(float** variables);
    void handle();
};

#endif