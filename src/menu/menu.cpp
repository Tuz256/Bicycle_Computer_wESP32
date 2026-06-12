#include "menu/menu.h"
#include "button/button.h"
#include "display/display.h"
#include "data/data.h"
#include "sensor/sensor.h"
#include <WiFi.h>
#include <ArduinoOTA.h>

MenuClass &MenuClass::getInstance()
{
    static MenuClass instance;
    return instance;
}

void MenuClass::begin()
{
    DisplayClass::getInstance().drawStaticMenu(currentMenu);
    DisplayClass::getInstance().drawDynamicMenu(currentMenu, 0);
}

bool MenuClass::shouldBypassMenu(MenuState menu)
{
    switch (menu)
    {
    case THEME_DARK:
    case THEME_WHITE:
    case CHANGE_CIRC:
    case TRY_UPT:
    case ERR_UPT:
    case TRY_RST:
        return true;
    default:
        return false;
    }
}

void MenuClass::nextMenu()
{
    do
    {
        currentMenu = static_cast<MenuState>((currentMenu + 1) % MENU_ENUM_COUNT);
    } while ((enter_settings && (currentMenu <= SETTINGS || shouldBypassMenu(currentMenu))) ||
             (!enter_settings && currentMenu > SETTINGS));
}

void MenuClass::previousMenu()
{
    do
    {
        currentMenu = static_cast<MenuState>((currentMenu - 1 + MENU_ENUM_COUNT) % MENU_ENUM_COUNT);
    } while ((enter_settings && (currentMenu <= SETTINGS || shouldBypassMenu(currentMenu))) ||
             (!enter_settings && currentMenu > SETTINGS));
}

void MenuClass::handleLeftButton()
{
    DataClass &data = DataClass::getInstance();
    switch (currentMenu)
    {
    case THEME_WHITE:
        data.setDarkTheme(true);
        DisplayClass::getInstance().updateThemeColors();
        currentMenu = THEME_DARK;
        break;
    case THEME_DARK:
        data.setDarkTheme(false);
        DisplayClass::getInstance().updateThemeColors();
        currentMenu = THEME_WHITE;
        break;
    case CHANGE_CIRC:
        data.setCircumferenceMm(data.getCircumferenceMm() - 1);
        break;
    case TRY_RST:
        currentMenu = RESET;
        break;
    case TRY_UPT:
        currentMenu = UPDATE;
        WiFi.disconnect();
        break;
    default:
        previousMenu();
        break;
    }
}

void MenuClass::handleRightButton()
{
    DataClass &data = DataClass::getInstance();
    switch (currentMenu)
    {
    case THEME_DARK:
        data.setDarkTheme(false);
        DisplayClass::getInstance().updateThemeColors();
        currentMenu = THEME_WHITE;
        break;
    case THEME_WHITE:
        data.setDarkTheme(true);
        DisplayClass::getInstance().updateThemeColors();
        currentMenu = THEME_DARK;
        break;
    case CHANGE_CIRC:
        data.setCircumferenceMm(data.getCircumferenceMm() + 1);
        break;
    case TRY_RST:
        currentMenu = RESET;
        break;
    case TRY_UPT:
        currentMenu = UPDATE;
        WiFi.disconnect();
        break;
    default:
        nextMenu();
        break;
    }
}

void MenuClass::handleMiddleButton()
{
    DataClass &data = DataClass::getInstance();
    switch (currentMenu)
    {
    case SETTINGS:
        enter_settings = true;
        nextMenu();
        break;
    case THEME:
        currentMenu = data.isDarkTheme() ? THEME_DARK : THEME_WHITE;
        break;
    case THEME_DARK:
    case THEME_WHITE:
        currentMenu = THEME;
        break;
    case CIRC:
        currentMenu = CHANGE_CIRC;
        break;
    case CHANGE_CIRC:
        currentMenu = CIRC;
        break;
    case RESET:
        currentMenu = TRY_RST;
        break;
    case TRY_RST:
        data.resetAll();
        enter_settings = false;
        currentMenu = TIME;
        break;
    case UPDATE:
        currentMenu = TRY_UPT;
        DisplayClass::getInstance().drawStaticMenu(currentMenu);
        tryOTAConnection();
        break;
    case ERR_UPT:
    case BACK:
        enter_settings = false;
        currentMenu = TIME;
        break;
    default:
        break;
    }
}

void MenuClass::tryOTAConnection()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_NAME, PASSWORD_KEY);
    unsigned long startAttempt = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - startAttempt > 10000)
        { // 10 saniye timeout
            currentMenu = ERR_UPT;
            return;
        }
        delay(100);
    }
    ArduinoOTA.begin();
}

void MenuClass::update()
{
    ButtonClass &btn = ButtonClass::getInstance();
    bool changed = false;

    if (btn.isLeftPressed())
    {
        handleLeftButton();
        changed = true;
    }
    else if (btn.isRightPressed())
    {
        handleRightButton();
        changed = true;
    }
    else if (btn.isMidPressed())
    {
        handleMiddleButton();
        changed = true;
    }

    if (changed)
    {
        DisplayClass::getInstance().drawStaticMenu(currentMenu);
    }

    if (currentMenu == TRY_UPT)
    {
        ArduinoOTA.handle();
    }

    DisplayClass::getInstance().drawDynamicMenu(currentMenu, SensorClass::getInstance().getCurrentSpeed());
}