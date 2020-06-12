#pragma once

#include "Interfaces/Controller.h"
#include <string>

/**
 * @brief A controller for work with documents.
 */
class UProjectActionsController : public IController
{
public:
	void BindToProjectPanelEvents(class UProjectActionsPanel& ProjectActionsPanel);
	
private:
    void CreateNewProject();
    void OpenProject();
    void SaveProject();

	std::shared_ptr<class UProjectDialog> CreateProjectDialog(bool bAllowProjectCreate, bool bAllowProjectOpening);
};