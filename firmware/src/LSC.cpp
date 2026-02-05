#include "LSC.h"

LSC LSCController;

void LSC::init()
{
    Serial.begin(9600);

    for (int i = 0; i < 20; i++)
        lastDigitalValues[i] = -1;
}

void LSC::update()
{
    if (Serial.available())
    {
        String cmd = Serial.readStringUntil('\n');
        proccessCommands(cmd);
    }
}

void LSC::proccessCommands(String cmd)
{
    if (cmd.startsWith("READ_DIGITAL"))
    {
        int pin = cmd.substring(cmd.indexOf(":") + 1).toInt();
        readDigitalPin(pin);
    }
    else if (cmd.startsWith("READ_ANALOG"))
    {
        int pin = cmd.substring(cmd.indexOf(":") + 1).toInt();
        readAnalogPin(pin);
    }
    else if (cmd.startsWith("SET_PIN"))
    {
        int firstColon = cmd.indexOf(":", 0);
        int secondColon = cmd.indexOf(":", firstColon + 1);

        uint8_t pin = cmd.substring(firstColon + 1, secondColon).toInt();
        uint8_t mode = cmd.substring(secondColon + 1).toInt();

        setPinMode(pin, mode);
    }
    else if (cmd.startsWith("WRITE_DIGITAL"))
    {
        int firstColon = cmd.indexOf(":", 0);
        int secondColon = cmd.indexOf(":", firstColon + 1);

        uint8_t pin = cmd.substring(firstColon + 1, secondColon).toInt();
        uint8_t mode = cmd.substring(secondColon + 1).toInt();

        writeDigitalPin(pin, mode);
    }
    else if (cmd.startsWith("WRITE_ANALOG"))
    {
        int firstColon = cmd.indexOf(":", 0);
        int secondColon = cmd.indexOf(":", firstColon + 1);

        uint8_t pin = cmd.substring(firstColon + 1, secondColon).toInt();
        int val = cmd.substring(secondColon + 1).toInt();

        writeAnalogPin(pin, val);
    }
}

void LSC::readDigitalPin(uint8_t pin)
{
    Serial.println(digitalRead(pin));
}

void LSC::readAnalogPin(uint8_t pin)
{
    Serial.println(analogRead(pin));
}

void LSC::attachInterruptPin(uint8_t pin, int mode)
{
    attachInterrupt(digitalPinToInterrupt(pin), []() {}, mode);
}

void LSC::detachInterruptPin(uint8_t pin)
{
    detachInterrupt(digitalPinToInterrupt(pin));
}

void LSC::setPinMode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

void LSC::writeDigitalPin(uint8_t pin, uint8_t mode)
{
    digitalWrite(pin, mode);
}

void LSC::writeAnalogPin(uint8_t pin, int value)
{
    analogWrite(pin, value);
}