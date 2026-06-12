#include "display.h"
#include "data/data.h"
#include <image/image.h>

DisplayClass &DisplayClass::getInstance()
{
    static DisplayClass instance;
    return instance;
}

void DisplayClass::begin()
{
    tft.init();
    tft.setRotation(rotation);
    updateThemeColors();
    clearScreen();
}

void DisplayClass::clearScreen()
{
    tft.fillScreen(backgroundColor);
}

void DisplayClass::updateThemeColors()
{
    if (DataClass::getInstance().isDarkTheme())
    {
        textColor = 0xFFFF;
        backgroundColor = 0x0000;
    }
    else
    {
        textColor = 0x0000;
        backgroundColor = 0xFFFF;
    }
}

void DisplayClass::drawGearIcon()
{
    unsigned long now = millis();
    if (now - lastShowGearChange > 500)
    {
        tft.setTextSize(4);
        tft.setTextDatum(BL_DATUM);
        if (!draw_gear_icon)
        {
            tft.drawBitmap(tft.width() - (gearW + 5), tft.height() - (gearH + 5), gear_icon, gearW, gearH, textColor);
            draw_gear_icon = true;
        }
        else
        {
            tft.drawBitmap(tft.width() - (gearW + 5), tft.height() - (gearH + 5), gear_icon, gearW, gearH, backgroundColor);
            draw_gear_icon = false;
        }
        lastShowGearChange = millis();
    }
}

// ... Diğer tüm tft.draw işlevleri (menuStatic, menuDynamic, settingsStatic, settingsDynamic vb.)
// Orijinal kodunuzdaki tft mantığı korunarak buraya taşındı. Örnek uygulama aşağıdadır:

void DisplayClass::drawFloat(float value, int digits, int x, int y, int datum)
{
    tft.setTextPadding(tft.textWidth("99.9", txtFont));
    tft.setTextDatum(datum);
    tft.drawFloat(value, digits, x, y, txtFont);
}

void DisplayClass::drawInt(int value, int x, int y, int datum, const char *paddingText)
{
    tft.setTextPadding(tft.textWidth(paddingText, txtFont));
    tft.setTextDatum(datum);
    tft.drawNumber(value, x, y, txtFont);
}

void DisplayClass::drawTime(int x, int y, float totalMs)
{
    unsigned long totalSeconds = totalMs / 1000;
    char timeStr[9];
    sprintf(timeStr, "%02lu:%02lu:%02lu", totalSeconds / 3600, (totalSeconds % 3600) / 60, totalSeconds % 60);
    tft.setTextPadding(tft.textWidth("99.99.99", txtFont));
    tft.setTextDatum(TL_DATUM);
    tft.drawString(timeStr, x, y, txtFont);
}

void DisplayClass::settingsStaticText(String t1, String t2, String t3, String t4, byte size)
{
    tft.setTextSize(size);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(textColor, backgroundColor);
    if (!t1.isEmpty())
        tft.drawString(t1, tft.width() / 2, 35, txtFont);
    if (!t2.isEmpty())
        tft.drawString(t2, tft.width() / 2, 65, txtFont);
    if (!t3.isEmpty())
        tft.drawString(t3, tft.width() / 2, 95, txtFont);
    if (!t4.isEmpty())
        tft.drawString(t4, tft.width() / 2, 125, txtFont);
    draw_gear_icon = false;
    drawGearIcon();
}

void DisplayClass::settingsDynamicRect(int selected)
{
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    int step = 20 + (selected * 30);
    tft.drawRect(3, step, tft.width() - 6, 30, TFT_ORANGE);
}

void DisplayClass::menuStaticLayout(int spd_x, int spd_y, int max_x, int max_y, int time_x, int time_y, int dist_x, int dist_y, int avg_x, int avg_y)
{
    tft.setTextSize(1);
    tft.drawFastHLine(0, 45, tft.width(), TFT_ORANGE);
    tft.drawFastVLine(64, 0, 45, TFT_ORANGE);
    tft.drawFastHLine(0, 115, tft.width(), TFT_ORANGE);
    tft.drawFastVLine(64, 115, 45, TFT_ORANGE);
    tft.setTextColor(TFT_MAGENTA);
    tft.drawString("TIME", time_x, time_y, txtFont);
    tft.drawString("SPD", spd_x, spd_y, txtFont);
    tft.drawString("DIST", dist_x, dist_y, txtFont);
    tft.drawString("MAX", max_x, max_y, txtFont);
    tft.drawString("AVG", avg_x, avg_y, txtFont);
}

void DisplayClass::menuDynamicValues(int spd_x, int spd_y, int max_x, int max_y, int time_x, int time_y, int dist_x, int dist_y, int avg_x, int avg_y, float speed)
{
    DataClass &data = DataClass::getInstance();
    tft.setTextColor(textColor, backgroundColor);
    tft.setTextSize(2);

    drawFloat(speed, 1, spd_x, spd_y);

    if (data.getTotalDistanceKm() >= 100.0)
    {
        data.setDistanceHundredKm(data.getDistanceHundredKm() + static_cast<int>(data.getTotalDistanceKm() / 100.0));
        data.setTotalDistanceKm(fmod(data.getTotalDistanceKm(), 100.0));
    }
    if (data.getDistanceHundredKm() > 0)
    {
        tft.setTextSize(1);
        drawInt(data.getDistanceHundredKm(), (tft.width() / 2) - 2, dist_y - 14);
        tft.setTextSize(2);
    }

    drawFloat(data.getTotalDistanceKm(), 1, dist_x, dist_y);
    drawFloat(data.getMaxSpeed(), 1, max_x, max_y, TR_DATUM);
    drawFloat(data.getAvgSpeed(), 1, avg_x, avg_y, TR_DATUM);

    // Menüye göre saat yazı boyutu (State kontrolü MenuManager üzerinden dolaylı gelebilir veya global basitleştirilebilir)
    drawTime(time_x, time_y, data.getElapsedTotalTime());
}

void DisplayClass::drawStaticMenu(MenuState state)
{
    clearScreen();
    switch (state)
    {
    case TIME:
        menuStaticLayout(5, 0, 70, 0, 50, 50, 5, 115, 70, 115);
        break;
    case AVG:
        menuStaticLayout(5, 0, 70, 0, 70, 115, 5, 115, 53, 50);
        break;
    case SETTINGS:
        settingsStaticText("ENTER", "SETTINGS", "", "", 2);
        break;
    case THEME:
        settingsStaticText("CHANGE", "THEME", "", "", 2);
        break;
    case THEME_DARK:
    case THEME_WHITE:
        settingsStaticText("", "DARK", "WHITE", "", 2);
        break;
    case CIRC:
        settingsStaticText("CHANGE", "WHEEL", "DIAMETER", "", 2);
        break;
    case CHANGE_CIRC:
        settingsStaticText("", String(DataClass::getInstance().getCircumferenceMm()), "", "", 2);
        break;
    case RESET:
        settingsStaticText("RESET", "ALL", "", "", 2);
        break;
    case TRY_RST:
        settingsStaticText("", "CONFIRM", "RESET", "", 2);
        break;
    case UPDATE:
        settingsStaticText("TRY", "CONNECT", "", "", 2);
        break;
    case TRY_UPT:
        settingsStaticText("TRYING", "TO", "CONNECT", "", 2);
        break;
    case ERR_UPT:
        settingsStaticText("ERROR", "OCCURED!", "", "", 2);
        break;
    case BACK:
        settingsStaticText("BACK", "", "", "", 2);
        break;
    }
}

void DisplayClass::drawDynamicMenu(MenuState state, float speed)
{
    switch (state)
    {
    case TIME:
        menuDynamicValues(5, 13, 126, 13, 10, 70, 5, 130, 125, 130, speed);
        break;
    case AVG:
        menuDynamicValues(5, 13, 126, 13, 70, 140, 5, 130, 96, 70, speed);
        break;
    case THEME_DARK:
    case THEME_WHITE:
        drawGearIcon();
        settingsDynamicRect(state == THEME_DARK ? 1 : 2);
        break;
    default:
        drawGearIcon();
        break;
    }
}