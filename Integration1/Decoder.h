#pragma once
#include "Arduino.h"

class Decoder
{
private:
#define PIN_A 19
#define PIN_B 25
#define PIN_C 22
public:
    Decoder();
    void write(int pin);
};