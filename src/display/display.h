#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include "config.h"

class DisplayClass
{
public:
    static DisplayClass &getInstance();
    void begin();

    void clearScreen();
    void updateThemeColors();
    void drawStaticMenu(MenuState state);
    void drawDynamicMenu(MenuState state, float speed);
    void drawGearIcon();

    uint16_t getBgColor() const { return backgroundColor; }
    uint16_t getTextColor() const { return textColor; }

private:
    DisplayClass() {}
    TFT_eSPI tft = TFT_eSPI();
    unsigned short txtFont = 2;
    unsigned short rotation = 2;
    unsigned long lastShowGearChange = 0;
    bool draw_gear_icon = false;

    uint16_t backgroundColor = 0x0000;
    uint16_t textColor = 0xFFFF;

    void drawFloat(float value, int digits, int x, int y, int datum = TL_DATUM);
    void drawInt(int value, int x, int y, int datum = TR_DATUM, const char *paddingText = "999");
    void drawTime(int x, int y, float totalMs);
    void settingsStaticText(String t1, String t2, String t3, String t4, byte size);
    void settingsDynamicRect(int selected);
    void menuStaticLayout(int spd_x, int spd_y, int max_x, int max_y, int time_x, int time_y, int dist_x, int dist_y, int avg_x, int avg_y);
    void menuDynamicValues(int spd_x, int spd_y, int max_x, int max_y, int time_x, int time_y, int dist_x, int dist_y, int avg_x, int avg_y, float speed);
};

#endif