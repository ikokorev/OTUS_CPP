#include "Button.h"

TMulticastDelegate<>& UButton::GetOnButtonClicked()
{
	return OnButtonClicked;
}

UTextBlock& UButton::GetButtonText()
{
	return ButtonText;
}
