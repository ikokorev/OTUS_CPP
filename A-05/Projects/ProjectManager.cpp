#include "ProjectManager.h"

FProjectManager& FProjectManager::GetInstance()
{
    static FProjectManager* ProjectManager = new FProjectManager();
    return *ProjectManager;
}

bool FProjectManager::HasLoadedProject() const
{
	return CurrentProject.get() != nullptr;
}