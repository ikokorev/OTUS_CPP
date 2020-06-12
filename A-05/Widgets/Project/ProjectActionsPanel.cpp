#include "ProjectActionsPanel.h"

UProjectActionsPanel::UProjectActionsPanel()
{
	CreateNewProjectButton.GetButtonText().SetText("New project...");
	OpenProjectButton.GetButtonText().SetText("Open project...");
	SaveProjectButton.GetButtonText().SetText("Save current project");
}


