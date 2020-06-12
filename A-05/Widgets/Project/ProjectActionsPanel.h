#pragma once

#include "Widgets/Framework/Button.h"
#include "Widgets/Framework/VerticalPanel.h"

/**
 * @brief A panel for working with documents.
 */
class UProjectActionsPanel : public UVerticalPanel
{
public:
	UProjectActionsPanel();

	UButton& GetCreateNewProjectButton()
	{
		return CreateNewProjectButton;
	}

	UButton& GetOpenProjectButton()
	{
		return OpenProjectButton;
	}

	UButton& GetSaveProjectButton()
	{
		return SaveProjectButton;
	}
	
private:
    UButton CreateNewProjectButton;
	UButton OpenProjectButton;
	UButton SaveProjectButton;
};