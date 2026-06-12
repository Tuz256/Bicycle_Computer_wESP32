#include "button.h"

volatile unsigned long ButtonClass::lastButtonPressTime = 0;
volatile bool ButtonClass::leftPressed = false;
volatile bool ButtonClass::rightPressed = false;
volatile bool ButtonClass::midPressed = false;

ButtonClass &ButtonClass::getInstance()
{
    static ButtonClass instance;
    return instance;
}

void ButtonClass::begin()
{
    pinMode(buttonLeft, INPUT_PULLUP);
    pinMode(buttonMid, INPUT_PULLUP);
    pinMode(buttonRight, INPUT_PULLUP);

    attachInterrupt(buttonLeft, buttonInterrupt, FALLING);
    attachInterrupt(buttonMid, buttonInterrupt, FALLING);
    attachInterrupt(buttonRight, buttonInterrupt, FALLING);
}

void IRAM_ATTR ButtonClass::buttonInterrupt()
{
    unsigned long currentTime = millis();
    if ((currentTime - lastButtonPressTime) > DEBOUNCE_TIME)
    {
        if (digitalRead(buttonLeft) == LOW)
            leftPressed = true;
        else if (digitalRead(buttonRight) == LOW)
            rightPressed = true;
        else if (digitalRead(buttonMid) == LOW)
            midPressed = true;
        lastButtonPressTime = currentTime;
    }
}

bool ButtonClass::isLeftPressed()
{
    if (leftPressed)
    {
        leftPressed = false;
        return true;
    }
    return false;
}
bool ButtonClass::isRightPressed()
{
    if (rightPressed)
    {
        rightPressed = false;
        return true;
    }
    return false;
}
bool ButtonClass::isMidPressed()
{
    if (midPressed)
    {
        midPressed = false;
        return true;
    }
    return false;
}