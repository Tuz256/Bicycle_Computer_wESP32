#ifndef BUTTON_H
#define BUTTON_H

#include "config.h"

class ButtonClass
{
public:
    static ButtonClass &getInstance();
    void begin();

    bool isLeftPressed();
    bool isRightPressed();
    bool isMidPressed();

    static void IRAM_ATTR buttonInterrupt();

private:
    ButtonClass() {}
    static volatile unsigned long lastButtonPressTime;
    static volatile bool leftPressed;
    static volatile bool rightPressed;
    static volatile bool midPressed;
};

#endif