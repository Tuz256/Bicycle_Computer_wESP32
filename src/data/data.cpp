#include "data.h"
#include <EEPROM.h>

DataClass &DataClass::getInstance()
{
    static DataClass instance;
    return instance;
}

void DataClass::begin()
{
    EEPROM.begin(EEPROM_SIZE);
    readAll();
}

void DataClass::readAll()
{
    float dataFloat;
    int dataInt;
    uint8_t themeTemp;

    EEPROM.get(eeMaxSpeedAddress, dataFloat);
    if ((int)dataFloat != 0 && !isnan(dataFloat))
        fMaxSpeed = dataFloat;

    EEPROM.get(eeAvgSpeedAddress, dataFloat);
    if ((int)dataFloat != 0 && !isnan(dataFloat))
        fAvgSpeed = dataFloat;

    EEPROM.get(eeDistAddress, dataFloat);
    if ((int)dataFloat != 0 && !isnan(dataFloat))
        fTotalDistanceKm = dataFloat;

    EEPROM.get(eeDistHundredAddress, dataInt);
    if ((int)dataFloat != 0 && !isnan(dataInt))
        distanceHundredKm = dataInt;

    EEPROM.get(eeElapsedTotalTimeAddress, dataFloat);
    if ((int)dataFloat != 0 && !isnan(dataFloat))
        fElapsedTotalTime = dataFloat;

    EEPROM.get(eeDarkThemeAddress, themeTemp);
    if (themeTemp != 0xFF)
        darkTheme = themeTemp;

    EEPROM.get(eeCircumferenceAddress, dataInt);
    if (dataInt != 0 && !isnan(dataInt))
        currentCircumferenceMm = dataInt;
}

void DataClass::writeAll()
{
    float dataFloat;
    int dataInt;
    uint8_t themeTemp;

    EEPROM.get(eeMaxSpeedAddress, dataFloat);
    if (dataFloat != fMaxSpeed)
        EEPROM.put(eeMaxSpeedAddress, fMaxSpeed);

    EEPROM.get(eeAvgSpeedAddress, dataFloat);
    if (dataFloat != fAvgSpeed)
        EEPROM.put(eeAvgSpeedAddress, fAvgSpeed);

    EEPROM.get(eeDistAddress, dataFloat);
    if (dataFloat != fTotalDistanceKm)
        EEPROM.put(eeDistAddress, fTotalDistanceKm);

    EEPROM.get(eeDistHundredAddress, dataInt);
    if (dataInt != distanceHundredKm)
        EEPROM.put(eeDistHundredAddress, distanceHundredKm);

    EEPROM.get(eeElapsedTotalTimeAddress, dataFloat);
    if (dataFloat != fElapsedTotalTime)
        EEPROM.put(eeElapsedTotalTimeAddress, fElapsedTotalTime);

    EEPROM.get(eeDarkThemeAddress, themeTemp);
    if (themeTemp != darkTheme)
        EEPROM.put(eeDarkThemeAddress, darkTheme);

    EEPROM.get(eeCircumferenceAddress, dataInt);
    if (dataInt != currentCircumferenceMm)
        EEPROM.put(eeCircumferenceAddress, currentCircumferenceMm);

    EEPROM.commit();
}

void DataClass::resetAll()
{
    fMaxSpeed = 0;
    fElapsedTotalTime = 0;
    fAvgSpeed = 0;
    fTotalDistanceKm = 0;
    distanceHundredKm = 0;
    currentCircumferenceMm = 2078;
    darkTheme = true;
    writeAll();
    esp_restart();
}