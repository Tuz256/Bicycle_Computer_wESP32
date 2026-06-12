#ifndef DATA_H
#define DATA_H

#include "config.h"

class DataClass
{
public:
    static DataClass &getInstance();

    void begin();
    void readAll();
    void writeAll();
    void resetAll();

    // Getters & Setters
    float getMaxSpeed() const { return fMaxSpeed; }
    void setMaxSpeed(float val) { fMaxSpeed = val; }

    float getAvgSpeed() const { return fAvgSpeed; }
    void setAvgSpeed(float val) { fAvgSpeed = val; }

    float getTotalDistanceKm() const { return fTotalDistanceKm; }
    void setTotalDistanceKm(float val) { fTotalDistanceKm = val; }

    int getDistanceHundredKm() const { return distanceHundredKm; }
    void setDistanceHundredKm(int val) { distanceHundredKm = val; }

    float getElapsedTotalTime() const { return fElapsedTotalTime; }
    void setElapsedTotalTime(float val) { fElapsedTotalTime = val; }

    bool isDarkTheme() const { return darkTheme; }
    void setDarkTheme(bool val) { darkTheme = val; }

    int getCircumferenceMm() const { return currentCircumferenceMm; }
    void setCircumferenceMm(int val) { currentCircumferenceMm = val; }

private:
    DataClass() {} // Singleton

    float fMaxSpeed = 0.0;
    float fAvgSpeed = 0.0;
    float fTotalDistanceKm = 0.0;
    int distanceHundredKm = 0;
    float fElapsedTotalTime = 0.0;
    bool darkTheme = true;
    int currentCircumferenceMm = 2078;
};

#endif