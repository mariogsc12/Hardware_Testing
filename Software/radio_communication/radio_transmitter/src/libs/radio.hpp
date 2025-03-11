
#ifndef RADIO_H
#define RADIO_H

#define NMESSAGES 2
#define MSG_STATUS_LENGTH 6
#define MSG_COMMANDS_LENGTH 6
#define EOL "\r\n"

typedef enum SerialMsgId
{
    MSG_IDLE,       // 0 
    MSG_STATUS,     // 1
    MSG_COMMANDS,   // 2
    MSG_ERROR,      // 3
}SerialMsgId;

class Radio
{
private:
    int serialMsg_Status[MSG_STATUS_LENGTH];
    int serialMsg_Commands[MSG_COMMANDS_LENGTH];
    SerialMsgId serialMsg_Id;
public:
    Radio();
    ~Radio();
    void sendPacket();
    void read();
    void setId_StatusMessage(int,int);
    void setId_CommandsMessage(int,int);
    void setMsg_Status(int,int,int,int,int,int);
    void setMsg_Commands(int,int,int,int);
};




#endif 