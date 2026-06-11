// /==================================================================================================\
// ||                                                                                                ||
// ||         ____  _                 _         ____                            _                    ||
// ||        | __ )(_) ___ _   _  ___| | ___   / ___|___  _ __ ___  _ __  _   _| |_ ___ _ __         ||
// ||        |  _ \| |/ __| | | |/ __| |/ _ \ | |   / _ \| '_ ` _ \| '_ \| | | | __/ _ \ '__|        ||
// ||        | |_) | | (__| |_| | (__| |  __/ | |__| (_) | | | | | | |_) | |_| | ||  __/ |           ||
// ||        |____/|_|\___|\__, |\___|_|\___|  \____\___/|_| |_| |_| .__/ \__,_|\__\___|_|           ||
// ||                      |___/                                   |_|                               ||
// ||                                     _______ ____  ____ _________                               ||
// ||                          __      __/ / ____/ ___||  _ \___ /___ \                              ||
// ||                          \ \ /\ / / /|  _| \___ \| |_) ||_ \ __) |                             ||
// ||                           \ V  V / / | |___ ___) |  __/___) / __/                              ||
// ||                            \_/\_/_/  |_____|____/|_|  |____/_____|                             ||
// ||                                                                                                ||
// ||         _ _   _           _       ___               _                     _    ____  _____ _   ||
// ||    __ _(_) |_| |__  _   _| |__   / / |__   ___  ___| |_ _ __   ___   ___ | |__|___ \|___ // |  ||
// ||   / _` | | __| '_ \| | | | '_ \ / /| '_ \ / _ \/ __| __| '_ \ / _ \ / _ \| '_ \ __) | |_ \| |  ||
// ||  | (_| | | |_| | | | |_| | |_) / / | |_) |  __/\__ \ |_| | | | (_) | (_) | |_) / __/ ___) | |  ||
// ||   \__, |_|\__|_| |_|\__,_|_.__/_/  |_.__/ \___||___/\__|_| |_|\___/ \___/|_.__/_____|____/|_|  ||
// ||   |___/                                                                                        ||
// ||                                                                                                ||
// \==================================================================================================/

#include "button/button.h"
#include "menu/menu.h"
#include "screen/screen.h"
#include <images/images.h>

#include <EEPROM.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

// Object definitions
//. . . . . . . . . . . . . . . . . . . . . . . . . . .
TFT_eSPI tft = TFT_eSPI();
MenuClass menu = MenuClass();

//. . . . . . . . . . . . . . . . . . . . . . . . . . .

// EEPROM variables
//. . . . . . . . . . . . . . . . . . . . . . . . . . .
#define EEPROM_SIZE 64 // EEPROM size that will be used
// const int eeMaxSpeedAddress = 0;          // 0-3
// const int eeAvgSpeedAddress = 4;          // 4-7
// const int eeDistAddress = 8;              // 8-11
// const int eeDistHundredAddress = 12;      // 12-15
// const int eeElapsedTotalTimeAddress = 16; // 16-19
// const int eeDarkThemeAddress = 20;        // 19
// const int eeCircumferenceAddress = 24;    // 24-27
//. . . . . . . . . . . . . . . . . . . . . . . . . . .

// TFT screen variables
//. . . . . . . . . . . . . . . . . . . . . . . . . . .
unsigned short txtFont = 1;           // Selecting font. For more information search for TFT_eSPI Library
unsigned short rotation = 2;          // Set screen rotation. (normal: 0, upside down: 2)
unsigned long lastShowGearChange = 0; // For tracking of when was last change of state
bool draw_gear_icon = false;          // default "false". For tracking whether the gear icon is drawn or not
bool darkTheme = true;                // dark = true, white = false. For rendering screen theme
uint16_t backgroundColor = 0x0000;    // Default "0x0000" (black). Background color hex value
uint16_t textColor = 0xFFFF;          // Default "0xFFFF" (white). Text rendering color hex value
//. . . . . . . . . . . . . . . . . . . . . . . . . . .

// TFT screen object and variables
//. . . . . . . . . . . . . . . . . . . . . . . . . . .

String Menus[3] = {"Time", "Avg", "Settings"};
String SubMenus[5] = {"Reset", "Back", "Theme", "Set-up", "Update"};

//. . . . . . . . . . . . . . . . . . . . . . . . . . .

void setup()
{

    Serial.begin(115200); // Initialize Serial connection
    Serial.println("Starting booting sequence...");
    // EEPROM.begin(EEPROM_SIZE);

    // pinMode(HallEffectSensor, INPUT_PULLUP); // Set pin mode for hall effect sensor
    // pinMode(buttonRight, INPUT_PULLUP);      // Set pin mode for right button
    // pinMode(buttonLeft, INPUT_PULLUP);       // Set pin mode for left button
    // pinMode(buttonMid, INPUT_PULLUP);        // Set pin mode for middle button
    // delay(100);

    // eepromRead();

    tft.init();
    tft.fillScreen(backgroundColor); // Clear the screen
    tft.setRotation(rotation);
    Serial.println("TFT Screen Initialized!"); // Write "TFT Screen Initialized!"
    delay(50);

    // attachInterrupt(HallEffectSensor, hallInterrupt, FALLING);
    // attachInterrupt(buttonLeft, buttonInterrupt, FALLING);
    // attachInterrupt(buttonMid, buttonInterrupt, FALLING);
    // attachInterrupt(buttonRight, buttonInterrupt, FALLING);

    // displayMenuStatic(in_settings);
    // displayMenuDynamic();
}

void loop()
{

    // changeMenu();

    // changeTheme();

    // displayMenuDynamic();

    // if (debug)
    // {
    //     Serial.println(currentMenu);

    //     Serial.println(currentSubMenu);

    //     Serial.println(in_settings);

    //     Serial.println("------------------------------");
    // }

    delay(150);
}
