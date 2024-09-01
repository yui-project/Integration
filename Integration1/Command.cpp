#include "Command.h"
#include "Arduino.h"

Command::Command()
{
    // TODO 実装待ち
}

bool Command::execute(int subject)
{ // メインマイコンが受信側になった時のためのクラス
    switch (subject)
    { // 手打ちなの地味に間違えそうで怖い ★こっちがマスターで、後から下にコピペする
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        break;
    case 33:
        sendToMission(subject);
        break;
    case 34:
        sendToMission(subject);
        break;
    case 35:
        sendToMission(subject);
        break;
    case 36:
        sendToMission(subject);
        break;
    case 37:
        sendToMission(subject);
        break;
    case 38:
        sendToMission(subject);
        break;
    case 39:
        sendToMission(subject);
        break;
    case 40:
        sendToMission(subject);
        break;
    case 41:
        sendToMission(subject);
        break;
    case 42:
        sendToMission(subject);
        break;
    case 43:
        sendToMission(subject);
        break;
    case 44:
        sendToMission(subject);
        break;
    case 45:
        sendToMission(subject);
        break;
    case 46:
        sendToMission(subject);
        break;
    case 47:
        sendToMission(subject);
        break;
    case 48:
        sendToMission(subject);
        break;
    case 49:
        sendToMission(subject);
        break;
    case 50:
        sendToMission(subject);
        break;
    case 51:
        sendToMission(subject);
        break;
    case 52:
        sendToMission(subject);
        break;
    case 53:
        sendToMission(subject);
        break;
    default:
        mission.disposal();
        break;
    }
    Serial2.write(ACK); // コマンド終わったらACKを送る？←受信側としてやること確認
}

bool Command::sendToPowerMC(int subject)
{ // メインマイコンが送信側になった時のためのクラス
    // subjectをPowerMCに送って、ACKが返ってきたらtrue、それ以外が返ってきたらfalseを返す。
    pinMode(masterSelectPin, OUTPUT);
    digitalWrite(masterSelectPin, HIGH); // mainMCをマスターに設定
    bool communicationStatus1;
    bool communicationStatus2;
    Serial2.write(subject);                   // Serial2でコマンド番号を送信
    Serial2.flush();                          // 送信完了待ち
    delay(1);                                 // 一応のdelay
    communicationStatus1 = confirmationAck(); // ACK1の状態確認
    if (communicationStatus1 == ACK)
    { // ACK1がACKやった時
        int packetSizeValue = packetSize(subject);
        if (packetSizeValue > 0 && packetSizeValue < 999999)
        {
            // ここにパケットの送信作業を入れる（★分割してpacketNo割り振る作業はどこでする？←誤り検出訂正やパケットNoを載せないといけない？←受信するのも合わせなきゃだし大変そう　分割されたcontentsをそれぞれ送る作業とかはpacketSizeValueを元にfor文とか組めばいい）
            return confirmationAck(); // ACK2の状態確認
        }
        else if (packetSizeValue == 999999)
        {
            return false; // packetSize()からエラーコードが吐かれた時（多分未決定コマンドが入った時や未登録の時）はfalseを返す　★これでいい？
        }
        else
        {                // packetSize(subject)==0の時
            return true; // ACK1のみのやつは、ACK2を問答無用でtrueにする
        }
    }
    else
    { // ACK1がNAKやった時
        return false;
    }
}

bool Command::sendToMission(int subject)
{
    return mission.execute(subject);
}

bool Command::confirmationAck()
{ // ACKが返ってきたらtrue,それ以外だとfalse
    if (Serial2.available() > 0 && Serial2.read() == ACK)
        return true;
    return false;
}

int Command::packetSize(int subject)
{ // パケットの送受信サイズを返す関数
    int pSVal = 0;
    switch (subject)
    { // 手打ちなの地味に間違えそうで怖い
    case 1:
        pSVal = 0;
        break;
    case 2:
        pSVal = 0;
        break;
    case 3:
        pSVal = 3;
        break;
    case 4:
        pSVal = 3;
        break;
    case 5:
        pSVal = 0;
        break;
    case 6:
        pSVal = 0;
        break;
    case 7:
        pSVal = 0;
        break;
    case 8:
        pSVal = 0;
        break;
    case 9:
        pSVal = 0;
        break;
    case 10:
        pSVal = 0;
        break;
    case 11:
        pSVal = 0;
        break;
    case 12:
        pSVal = 0;
        break;
    case 13:
        pSVal = 0;
        break;
    case 14:
        pSVal = 0;
        break;
    case 15:
        pSVal = 0;
        break;
    case 16:
        pSVal = 0;
        break;
    case 17:
        pSVal = 0;
        break;
    case 18:
        pSVal = 0;
        break;
    case 19:
        pSVal = 35;
        break;
    case 20:
        pSVal = 43;
        break;
    case 21:
        pSVal = 27;
        break;
    case 22:
        pSVal = 26;
        break;
    case 23:
        pSVal = 26;
        break;
    case 24:
        pSVal = 0;
        break;
    case 25:
        pSVal = 0;
        break;
    case 33:
        pSVal = 1;
        break;
    case 34:
        pSVal = 0;
        break;
    case 35:
        pSVal = 0;
        break;
    case 36:
        pSVal = 0;
        break;
    case 37:
        pSVal = 0;
        break;
    case 38:
        pSVal = 0;
        break;
    case 39:
        pSVal = 999999; // 不明（未定？）
        break;
    case 40:
        pSVal = 35;
        break;
    case 41:
        pSVal = 27;
        break;
    case 42:
        pSVal = 1;
        break;
    case 43:
        pSVal = 1;
        break;
    case 44:
        pSVal = 0;
        break;
    case 45:
        pSVal = 0;
        break;
    case 46:
        pSVal = 0;
        break;
    case 47:
        pSVal = 0;
        break;
    case 48:
        pSVal = 999999; // 不明（未定？）
        break;
    case 49:
        pSVal = 7;
        break;
    case 50:
        pSVal = 999999; // 不明（未定？）
        break;
    case 51:
        pSVal = 999999; // 不明（未定？）
        break;
    case 52:
        pSVal = 999999; // 不明（未定？）
        break;
    case 53:
        pSVal = 999999; // 不明（未定？）
        break;
    default:
        pSVal = 999999; // エラーコード的な感じで「999999」を使っていく！（ここでは未登録コマンドが入った時）
        break;
    }
    return pSVal;
}

/*
[Kurokawa's MEMO]
1.データ送信を行わない、ほとんどのコマンドがACK1のみでPacketを伴わない。それ故に流れは「SubjectNumを送信→ACK1を受信→Receiver側で処理」で終了。
*/