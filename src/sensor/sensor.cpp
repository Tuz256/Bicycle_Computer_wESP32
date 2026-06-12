#include "sensor.h"
#include "data/data.h"

volatile unsigned short SensorClass::counter = 0;

SensorClass &SensorClass::getInstance()
{
    static SensorClass instance;
    return instance;
}

void SensorClass::begin()
{
    pinMode(HallEffectSensor, INPUT_PULLUP);
    attachInterrupt(HallEffectSensor, hallInterrupt, FALLING);
    fStartTime = millis();
}

void IRAM_ATTR SensorClass::hallInterrupt()
{
    counter++;
}

void SensorClass::calculate()
{
    DataClass &data = DataClass::getInstance();

    if (counter > 0 && counter <= 20)
    {
        unsigned long fElapsedTime = millis() - fStartTime;
        data.setElapsedTotalTime(data.getElapsedTotalTime() + fElapsedTime);

        float fTakenDistanceCm = (data.getCircumferenceMm() / 10.0) * float(counter);
        data.setTotalDistanceKm(data.getTotalDistanceKm() + (fTakenDistanceCm / 100000.0));

        fSpeed = (fTakenDistanceCm / float(fElapsedTime)) * 36.0;
        data.setMaxSpeed(max(data.getMaxSpeed(), fSpeed));

        float hoursElapsed = data.getElapsedTotalTime() / 3600000.0;
        if (hoursElapsed > 0)
        {
            data.setAvgSpeed(data.getTotalDistanceKm() / hoursElapsed);
        }
    }
    else
    {
        fSpeed = 0.0;
    }
    counter = 0;
    fStartTime = millis();
}

void SensorClass::fakeTrigger()
{
    if (counter <= 10)
    {
        counter += random(0, 4);
    }
}