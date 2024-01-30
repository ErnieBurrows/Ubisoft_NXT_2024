#pragma once
#include "stdafx.h"
#include <Windows.h>

class KeyBoardInputHandler {
private:
    int keyCode;
    bool wasKeyPressed;

public:
    /*Constructor to create objects that have a specific Key value attached to them*/
    KeyBoardInputHandler(int key) : keyCode(key), wasKeyPressed(false) {}

    /// <summary>
    /// Will Return true only once per key down - Will reset when key is let go
    /// </summary>
    /// <returns></returns>
    bool OnKeyPressed() 
    {
        /*True if currently pressed down*/
        bool isKeyDown = GetAsyncKeyState(keyCode) & 0x8001;

        if (isKeyDown && !wasKeyPressed) 
        {
            wasKeyPressed = true;
            return true;
        }
        else if (!isKeyDown) 
        {   
            /*This will toggle if the KeyState is no longer true*/
            wasKeyPressed = false;
        }
        return false;
    }

    int GetKeyCode() const {
        return keyCode;
    }
};
