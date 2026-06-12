#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"

class SensorClass
{
public:
    static SensorClass &getInstance();
    void begin();
    void calculate();
    void fakeTrigger();

    float getCurrentSpeed() const { return fSpeed; }

    static void IRAM_ATTR hallInterrupt();

private:
    SensorClass() {}
    static volatile unsigned short counter;
    unsigned long fStartTime = 0;
    float fSpeed = 0.0;
};

#endif