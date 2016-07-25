/*
  tangible.h - Library for .
  Created by Alexander Neumann, 2016.
*/
#ifndef Tangible_h
#define Tangible_h
#include "Arduino.h"
#include "SoftwareSerial.h"
class Tangible
{
  public:
    Tangible(int rx, int tx, int pin);
    void init();
    void update();
    void checkTable();
    unsigned long currentTime;
    unsigned long old_time;
    bool onTable;
    int lightsensor;
    char msg[256];
    int lightsensorThreshold;
    SoftwareSerial* tangibleSerial;
};

#endif
