#ifndef MENU_H
#define MENU_H

#include "config.h"

class MenuClass
{
public:
    static MenuClass &getInstance();
    void begin();
    void update();

private:
    MenuClass() {}
    MenuState currentMenu = TIME;
    bool enter_settings = false;

    bool shouldBypassMenu(MenuState menu);
    void nextMenu();
    void previousMenu();
    void handleLeftButton();
    void handleRightButton();
    void handleMiddleButton();
    void tryOTAConnection();
};

#endif