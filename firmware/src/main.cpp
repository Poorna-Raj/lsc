#include <Arduino.h>

#include "LSC.h"

LSC tester;

void setup()
{
  tester.init();
}

void loop()
{
  tester.update();
}