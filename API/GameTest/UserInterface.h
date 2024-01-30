#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "App/app.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class UserInterface {
public:
    static void PrintFloatVariableValue(float x, float y, const std::string& labelText, float variableValue);
    static void PrintIntVariableValue(float x, float y, const std::string& labelText, int variableValue);
   
};

#endif // USERINTERFACE_H