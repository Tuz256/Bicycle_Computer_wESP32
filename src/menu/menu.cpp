#include "menu.h"

MenuClass::MenuClass()
{
}

MenuClass::~MenuClass()
{
}

// Private funcs.
//. . . . . . . . . . . . . . . . . . . . . . . . . . .

int MenuClass::lenght(String *arr)
{
    if (arr->isEmpty())
    {
        return -1;
    }

    return (sizeof(arr) / sizeof(String));
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . .

// Public funcs.
//. . . . . . . . . . . . . . . . . . . . . . . . . . .

bool MenuClass::menuDown(String *arr)
{
    if (arr->length() < 2)
    {
        return false;
    }

    String temp = arr[0];

    for (int i = 0; i < lenght(arr) - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    arr[lenght(arr) - 1] = temp;

    return true;
}

bool MenuClass::menuUp(String *arr)

{
    if (arr->length() < 2)
    {
        return false;
    }

    String temp = arr[lenght(arr) - 1];

    for (int i = lenght(arr) - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[0] = temp;

    return true;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . .
