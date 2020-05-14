#pragma once

#include "PanelWidget.h"
#include "Delegates/MulticastDelegate.h"

/**
 * @brief General class for all widgets\
 * // @todo: maybe simple widget?
 */
class UButton : public UPanelWidget
{

public:

    TMulticastDelegate<> OnButtonClicked;
};