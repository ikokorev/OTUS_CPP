#pragma once

#include <string>

#include "Widgets/Framework/PanelWidget.h"

//@todo comment this
enum class EProjectDialogMode
{
	CreateProject,
	OpenProject,
	Both
};

/*
 * @brief
 */
class UProjectDialog : public UPanelWidget
{
public:
	UProjectDialog(EProjectDialogMode InMode = EProjectDialogMode::Both) : Mode(InMode)
	{
		// Handles project creation and/or opening during its lifetime
		// Probably should use some helpers for new project opening, cause there's a lot of processes involved in it
	}
	
	std::string GetCurrentProjectFileName() const
	{
		return CurrentProjectFileName;
	}

	std::string GetCurrentProjectFilePath() const
	{
		return CurrentProjectFilePath;
	}
	
private:
	std::string CurrentProjectFileName;
	std::string CurrentProjectFilePath;
	EProjectDialogMode Mode;
};