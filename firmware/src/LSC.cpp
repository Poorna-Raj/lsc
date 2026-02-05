#include "LSC.h"

LSC LSCController;

void LSC::init()
{
    Serial.begin(9600);

    for (int i = 0; i < MAX_PINS; i++)
    {
        lastDigitalValues[i] = -1;
        watchDigital[i] = false;
    }
}

void LSC::update()
{
    if (Serial.available())
    {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        proccessCommands(cmd);
    }

    for (uint8_t pin = 0; pin < MAX_PINS; pin++)
    {
        if (!watchDigital[pin])
            continue;

        int current = digitalRead(pin);

        if (lastDigitalValues[pin] == -1)
        {
            lastDigitalValues[pin] = current;
            continue;
        }

        if (current != lastDigitalValues[pin])
        {
            if (lastDigitalValues[pin] == LOW && current == HIGH)
            {
                Serial.print("EDGE:RISING:");
                Serial.println(pin);
            }
            else if (lastDigitalValues[pin] == HIGH && current == LOW)
            {
                Serial.print("EDGE:FALLING:");
                Serial.println(pin);
            }

            lastDigitalValues[pin] = current;
        }
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
    else if (cmd.startsWith("WATCH_DIGITAL"))
    {
        uint8_t pin = cmd.substring(cmd.indexOf(":") + 1).toInt();
        watchDigitalPin(pin);
    }
    else if (cmd.startsWith("UNWATCH_DIGITAL"))
    {
        uint8_t pin = cmd.substring(cmd.indexOf(":") + 1).toInt();
        unwatchDigitalPin(pin);
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

void LSC::watchDigitalPin(uint8_t pin)
{
    watchDigital[pin] = true;
    lastDigitalValues[pin] = -1;
}

void LSC::unwatchDigitalPin(uint8_t pin)
{
    watchDigital[pin] = false;
    lastDigitalValues[pin] = -1;
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