#pragma once

#include <string>

#include "Widget.h"

/**
 * @brief General class for all widgets
 */
class UTextBlock : public UWidget
{
public:
	std::string GetText()
	{
		return Text;
	}

	void SetText(std::string InText)
	{
		Text = InText;
	}
	
private:
	std::string Text;
};