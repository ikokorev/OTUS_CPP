#include "ProjectActionsController.h"

#include "Misc/Paths.h"
#include "Projects/Project.h"
#include "Delegates/MulticastDelegate.h"
#include "Widgets/Project/ProjectActionsPanel.h"
#include "Widgets/Project/ProjectDialog.h"

#include <cassert>

void UProjectActionsController::BindToProjectPanelEvents(UProjectActionsPanel& ProjectActionsPanel)
{
	ProjectActionsPanel.GetCreateNewProjectButton().GetOnButtonClicked().AddFunction([this] { CreateNewProject(); });
	ProjectActionsPanel.GetOpenProjectButton().GetOnButtonClicked().AddFunction([this] {OpenProject(); });
	ProjectActionsPanel.GetSaveProjectButton().GetOnButtonClicked().AddFunction([this] {SaveProject(); });
}

void UProjectActionsController::CreateNewProject() const
{
	const std::shared_ptr<UProjectDialog> NewProjectDialog = CreateProjectDialog(true, true);

	// let's assume for now, that we obtained selected project path & file name
	const auto ProjectPath = NewProjectDialog->GetCurrentProjectFilePath();
	const auto ProjectName = NewProjectDialog->GetCurrentProjectFileName();

	FPaths::SetProjectFilePath(ProjectPath);
	FProject::SetProjectName(ProjectName);
}

std::shared_ptr<UProjectDialog> UProjectActionsController::CreateProjectDialog(bool bAllowProjectCreate, bool bAllowProjectOpening) const
{
	assert((bAllowProjectCreate || bAllowProjectOpening)
		&& "UProjectActionsController::CreateProjectDialog: new project dialog must be allowed to create or open a project, both must not be forbidden.");

	EProjectDialogMode Mode = EProjectDialogMode::Both;

	if (bAllowProjectOpening && !bAllowProjectCreate)
	{
		Mode = EProjectDialogMode::OpenProject;
	}
	else if (bAllowProjectCreate && !bAllowProjectOpening)
	{
		Mode = EProjectDialogMode::CreateProject;
	}

	return std::make_shared<UProjectDialog>(Mode);
}

void UProjectActionsController::OpenProject() const
{
	std::shared_ptr<UProjectDialog> NewProjectDialog = CreateProjectDialog(false, true);
}

void UProjectActionsController::SaveProject() const
{
}


