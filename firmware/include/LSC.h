#pragma once

#include <Arduino.h>

#define MAX_PINS 20

class LSC
{
public:
    void init();
    void update();

    void setPinMode(uint8_t pin, uint8_t mode);
    void readDigitalPin(uint8_t pin);
    void readAnalogPin(uint8_t pin);
    void writeDigitalPin(uint8_t pin, uint8_t mode);
    void writeAnalogPin(uint8_t pin, int value);

    void watchDigitalPin(uint8_t pin);
    void unwatchDigitalPin(uint8_t pin);

private:
    int lastDigitalValues[MAX_PINS];
    bool watchDigital[MAX_PINS];

    void proccessCommands(String cmd);
};

extern LSC LSCController;