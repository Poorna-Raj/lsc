#pragma once

#include <Arduino.h>

class LSC
{
public:
    void init();
    void update();

    void readDigitalPin(uint8_t pin);
    void readAnalogPin(uint8_t pin);

    void attachInterruptPin(uint8_t pin, int mode);
    void detachInterruptPin(uint8_t pin);

    void setPinMode(uint8_t pin, uint8_t mode);

    void writeDigitalPin(uint8_t pin, uint8_t mode);
    void writeAnalogPin(uint8_t pin, int value);

private:
    int lastDigitalValues[20];

    void proccessCommands(String cmd);
};

extern LSC LSCController;