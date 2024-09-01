#pragma once
#include "CommunicationWithMissionModule.h"

#define ACK 0x06

class Command{
    private:
    CommunicationWithMissionModule mission;
        uint8_t ackOrNak;
        int masterSelectPin = 27;
    public:
        Command();
        bool execute(int subject);
        bool sendToPowerMC(int subject);
        bool sendToMission(int subject);
        bool confirmationAck();
        int packetSize(int subject);
};