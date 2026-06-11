#ifndef MENU_H
#define MENU_H
#include <Arduino.h>

class MenuClass
{
private:
    int lenght(String *arr);

public:
    MenuClass();

    ~MenuClass();

    bool menuDown(String *arr);
    bool menuUp(String *arr);
};

#endif