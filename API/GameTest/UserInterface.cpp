#include "stdafx.h"
#include "UserInterface.h"

/// <summary>
/// Functionality to concatenate a float value along with an inputted string value and set the float precision to 0.00
/// Uses App::Print to print the result.
/// </summary>
void UserInterface::PrintFloatVariableValue(float x, float y, const std::string& labelText, float variableValue)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << variableValue;
	
	std::string text = labelText + ss.str();

	const char* result_cstr = text.c_str();
	
	App::Print(x, y, result_cstr);
}

/// <summary>
/// Functionality to concatenate a int value along with an inputted string value and set the float precision to (0) precision
/// Uses App::Print to print the result.
/// </summary>
void UserInterface::PrintIntVariableValue(float x, float y, const std::string& labelText, int variableValue)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(0) << variableValue;

	std::string text = labelText + ss.str();

	const char* result_cstr = text.c_str();

	App::Print(x, y, result_cstr);

}
