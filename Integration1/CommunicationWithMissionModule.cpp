#include "CommunicationWithMissionModule.h"

CommunicationWithMissionModule::CommunicationWithMissionModule()
{
    pinMode(masterSelectPin, OUTPUT);
}

bool CommunicationWithMissionModule::execute(int subject)
{
    // NOTE:ミッション用コマンドが送られてきたらミッションモジュールを起動したいのでmosfetをHIGHにする
    digitalWrite(moduleMosfetPin, HIGH);

    // subject番号に応じて動作を変える
    switch (subject)
    {
    case 33:
        return getMissionModuleStatus();

    case 34:
        // NOTE:起動する前にほんの少しディレイをかけたい
        delay(100);
        return confirmStartUpPIC();

    case 35:
        return startUpRSP();

    case 36:
        return endRSP();

    case 37:
        return reStartUpRSP();

    case 38:
        return confirmStartUpRSP();

    case 39:
        return sendTsukutoTime(RTC.get());

    case 40:
        for (int i = 0; i < 3; i++)
        {
        HkData[i] = (RTC.get() >> (8 * (2-i) & 0xFF));
        }
        // NOTE:残りの部分にはHKデータを入れる　インテグレーションではダミーデータ？

        return sendHkDate(HkData);

    case 41:
        // TODO TLEどうしよう
        return sendTle(TLE);

    case 42:
        return sendCameraParameter(cameraParameter);

    case 43:
        return sendAdParamater(adParameter);

    case 44:
        return startPmdMission();

    case 45:
        return startAdMission();

    case 46:
        return confirmMssionEnd();

    case 47:
        return announceMissionEnd();

    case 48:
        return getPmdStartTime();

    case 49:
        return getPmdMissionDate();

    case 50:
        return getAdMissionDate();

    case 51:
        return getCameraTestDate();

    case 52:
        return getCameraDateForPmd();

    case 53:
        return getError();

    case 54:
        return disposal();

    default:
        return false;
    }
}

bool CommunicationWithMissionModule::confirmationAck()
{
    if (Serial2.available() > 0 && Serial2.read() == ACK)
        return true;
    return false;
}

bool CommunicationWithMissionModule::startUpRSP()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(35);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::confirmStartUpPIC()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(34);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true)
    {
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getMissionModuleStatus()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(33);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true)
    {
        // NOTE:ミッションモジュールステータスの受け取り
        missionStatus = Serial2.read();
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::endRSP()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(36);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::reStartUpRSP()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(37);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::confirmStartUpRSP()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(38);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::sendTsukutoTime(uint32_t time)
{
    Serial2.write(39);
    Serial2.flush();
    // TODO 実装待ち このコマンドは地上時刻とTSUKUTO時刻の関係式を渡す？

    if (confirmationAck() == true)
    {
        Serial2.write(time);
        Serial2.flush();
        // Serial.println("sendTsukutoTime!!!");
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::sendHkDate(uint8_t a[31])
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(40);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();

    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true)
    {
        Serial.println("OK!!!");
        digitalWrite(masterSelectPin, HIGH);

        Serial2.write(a, 31);
        Serial2.flush();
        digitalWrite(masterSelectPin, LOW);
        delay(10); // TODO　delay(1000)にしたら下記の処理はいけた、while使うか検討
        if (confirmationAck() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::sendTle(uint32_t TLEdata)
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(41);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        digitalWrite(masterSelectPin, HIGH);
        Serial2.write((TLEdata >> 24) & 0xFF);
        Serial2.write((TLEdata >> 16) & 0xFF);
        Serial2.write((TLEdata >> 8) & 0xFF);
        Serial2.write((TLEdata) & 0xFF);
        Serial2.flush();
        delay(10);
        digitalWrite(masterSelectPin, LOW);
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::sendCameraParameter(uint8_t cameraParameter)
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(42);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();

    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true)
    {
        Serial.println("OK!!!");
        digitalWrite(masterSelectPin, HIGH);

        Serial2.write(cameraParameter);
        Serial2.flush();
        digitalWrite(masterSelectPin, LOW);
        delay(10); // TODO　delay(1000)にしたら下記の処理はいけた、while使うか検討
        if (confirmationAck() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::sendAdParamater(uint8_t adParameter)
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(43);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();

    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    if (confirmationAck() == true)
    {
        Serial.println("OK!!!");
        digitalWrite(masterSelectPin, HIGH);

        Serial2.write(adParameter);
        Serial2.flush();
        digitalWrite(masterSelectPin, LOW);
        delay(10); // TODO　delay(1000)にしたら下記の処理はいけた、while使うか検討
        if (confirmationAck() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::startPmdMission()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(44);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::startAdMission()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(45);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::confirmMssionEnd()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(46);   // subject番号を送る
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // NOTE:subjectNumberの型はこっちに合わせてくれる
    if (confirmationAck() == true) // ACKが返ってきたらtrueを返す
    {
        // Serial.println("OK!");
        if (confirmationAck() == true)
        { // ACK2の確認
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::announceMissionEnd()
{
    Serial2.write(47);
    Serial2.flush();
    if (confirmationAck() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getPmdStartTime()
{
    Serial2.write(48);
    Serial2.flush();
    delay(10);
    if (confirmationAck() == true)
    {
        pmdStartTime = Serial2.read();
        Serial.println(pmdStartTime);
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getPmdMissionDate()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(49);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    // delay(10);  // NOTE：このDelayをいれると動作が安定した
    if (confirmationAck() == true)
    {
        // FIXME 単体テスト行う
        Serial.println("startGetPmdMissionDate1");
        while (Serial2.available() > 0)
        {
            Serial.println("startgetPmdMissionDate2");
            for (int n = 0; n < 9; n++)
            {
                pmdResult[n] = Serial2.read();
                Serial.println(pmdResult[n]);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getAdMissionDate()
{
    Serial2.write(50);
    Serial2.flush();
    if (confirmationAck() == true)
    {
        // TODO ADミッション結果のサイズを聞く
        adResult = Serial2.read();
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getCameraTestDate()
{
    digitalWrite(masterSelectPin, HIGH);
    Serial2.write(51);
    Serial2.flush();
    Serial2.write('\n'); // subject番号は改行付きで送る
    Serial2.flush();
    digitalWrite(masterSelectPin, LOW);
    delay(1000);
    Serial.println("YES!!!");
    int count = 0;
    int n = 0;
    if (confirmationAck() == true)
    {
        while (1)
        {
            digitalWrite(masterSelectPin, LOW);
            // Serial.println("KAAAAAAA!!!!!!");
            while (Serial2.available() > 0)
            {
                uint8_t Data = Serial2.read();
                Serial.println(Data);
                if (Data == 0xd9)
                {
                    Serial.println("AllRight!!!!!");
                    return true;
                }
                count++;
            }
            if (count > 49)
            {
                Serial.println("comon!!!");
                delay(1000);
                digitalWrite(masterSelectPin, HIGH);
                Serial2.write(0x06);
                Serial2.flush();
                count = 0;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getCameraDateForPmd()
{
    Serial2.write(52);
    Serial2.flush();
    if (confirmationAck() == true)
    {
        // TODO 実装待ち
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::getError()
{
    Serial2.write(53);
    Serial2.flush();
    if (confirmationAck() == true)
    {
        // TODO 実装待ち
        return true;
    }
    else
    {
        return false;
    }
}

bool CommunicationWithMissionModule::disposal()
{
    int garvage;
    while (Serial2.available() > 0)
    {
        garvage = Serial2.read();
        Serial.println(garvage);
    }
    Serial.println("endDisposal");
}