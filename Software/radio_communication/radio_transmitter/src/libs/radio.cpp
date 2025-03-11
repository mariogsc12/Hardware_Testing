#include <libs/radio.hpp>
#include <Arduino.h>

Radio::Radio()
{
    setMsg_Status(0, 0, 0, 0, 0, 0);
    setMsg_Commands(0, 0, 0, 0);
    serialMsg_Id = MSG_IDLE; 
}

Radio::~Radio()
{
}

void Radio::sendPacket()
{
    
}

void Radio::read()
{
}

void Radio::setId_StatusMessage(int value, int id)
{
    if (id >= 0 && id < MSG_STATUS_LENGTH)
    {
        serialMsg_Status[id] = value;
    }
}

void Radio::setId_CommandsMessage(int value, int id)
{
    if (id >= 0 && id < MSG_COMMANDS_LENGTH)
    {
        serialMsg_Commands[id] = value;
    }
}

void Radio::setMsg_Status(int v1, int v2, int v3, int v4, int v5, int v6)
{
    int v[MSG_STATUS_LENGTH] = {v1, v2, v3, v4, v5, v6};
    for (int i = 0; i < MSG_STATUS_LENGTH; i++)
    {
        setId_StatusMessage(v[i], i);
    }
}

void Radio::setMsg_Commands(int v1, int v2, int v3, int v4)
{
    int v[MSG_COMMANDS_LENGTH] = {v1, v2, v3, v4};
    for (int i = 0; i < MSG_COMMANDS_LENGTH; i++)
    {
        setId_CommandsMessage(v[i], i);
    }
}
