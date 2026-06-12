#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Debug Modu
const bool debug = false;

// WiFi Bilgileri
const char *const SSID_NAME = "K_Andac_2";
const char *const PASSWORD_KEY = "kut769up";

// Pin Tanımlamaları
#define HallEffectSensor 15
#define buttonLeft 12
#define buttonMid 13
#define buttonRight 14

// EEPROM Ayarları
#define EEPROM_SIZE 64
const int eeMaxSpeedAddress = 0;
const int eeAvgSpeedAddress = 4;
const int eeDistAddress = 8;
const int eeDistHundredAddress = 12;
const int eeElapsedTotalTimeAddress = 16;
const int eeDarkThemeAddress = 20;
const int eeCircumferenceAddress = 24;

// Zamanlama Ayarları
const unsigned int waitUntil = 1600;
#define DEBOUNCE_TIME 200

// Menü Durumları
enum MenuState
{
    TIME,
    AVG,
    SETTINGS,
    THEME,
    THEME_DARK,
    THEME_WHITE,
    CIRC,
    CHANGE_CIRC,
    UPDATE,
    TRY_UPT,
    ERR_UPT,
    RESET,
    TRY_RST,
    BACK,
    MENU_ENUM_COUNT
};

#endif