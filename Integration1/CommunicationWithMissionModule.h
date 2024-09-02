#pragma once
#include "Arduino.h"
#include "RealTimeClock.h"
#include "IoExpander.h"

// NOTE:プレインテグレーションで使用したコードを移植する形になっている
class CommunicationWithMissionModule
{
private:
    RealTimeClock RTC;
    IoExpander exp;

    uint8_t masterSelectPin = 27;

#define ACK 0x06
#define NAK 0x15
    uint8_t missionStatus = 0;
    uint32_t TSUKUTOtime;
    uint8_t HkData[31];
    uint32_t TLE;
    uint8_t cameraParameter;
    uint8_t adParameter;
    uint8_t pmdStartTime;
    uint8_t pmdResult[9];
    uint8_t adResult;
    uint8_t cameraTestDate;
    uint8_t cameraDateForPMD;

public:
    CommunicationWithMissionModule();

    mission();

    // NOTE:下記2つの関数はCommandの方に実装
    bool confirmationAck();
    bool execute(int subject);

    bool getMissionModuleStatus();
    bool confirmStartUpPIC();
    bool startUpRSP();
    bool endRSP();
    bool reStartUpRSP();
    bool confirmStartUpRSP();
    bool sendTsukutoTime(uint32_t time);
    bool sendHkDate(uint8_t a[31]);
    bool sendTle(uint32_t TLEdata);
    bool sendCameraParameter(uint8_t cameraParameter);
    bool sendAdParamater(uint8_t adParameter);
    bool startPmdMission();
    bool startAdMission();
    bool confirmMssionEnd();
    bool announceMissionEnd();
    bool getPmdStartTime();
    bool getPmdMissionDate();
    bool getAdMissionDate();
    bool getCameraTestDate();
    bool getCameraDateForPmd();

    bool getError();
    bool disposal();
    // TODO 以下実装待ち
    // NOTE:ミッションモジュールとの通信のためのクラス コマンドを実装していく形になる
};