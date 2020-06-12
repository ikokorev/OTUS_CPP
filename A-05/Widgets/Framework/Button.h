#pragma once

#include "PanelWidget.h"
#include "TextBlock.h"
#include "Delegates/MulticastDelegate.h"

/**
 * @brief General class for all widgets\
 * // @todo: maybe simple widget?
 */
class UButton : public UPanelWidget
{
public:
	TMulticastDelegate<>& GetOnButtonClicked();
	UTextBlock& GetButtonText();
	
private:
	UTextBlock ButtonText;
    TMulticastDelegate<> OnButtonClicked;
};