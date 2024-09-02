// NOTE プレインテグレーションで使用したコード
#include "Command.h"
#include "IoExpander.h"
Command command;
IoExpander expander;
int subject;
void setup()
{
    Serial.begin(115200);
    Serial2.begin(57600, SERIAL_8E1);
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    expander.write(6,LOW);

}

void loop()
{

    if (Serial.available() > 0)
    {
        String receivedString = Serial.readStringUntil('\n');
        receivedString.trim();
        if (receivedString.length() > 2)
        {
            String receivedSubject = receivedString.substring(0, 2); // 2桁の値を取得する
            subject = receivedSubject.toInt();                 // int型に変換
        }
        else
        {
            subject = receivedString.toInt();
        }
    }

    Serial.print("Subject = ");
    Serial.println(subject);
    if (command.execute(subject) == true)
    {
        Serial.println("Hello");
    }
    delay(1000);
}