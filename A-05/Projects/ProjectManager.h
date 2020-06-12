#pragma once

#include <memory>
#include "Project.h"
#include <string>

/**
 * @brief Class which handles currently running project
 */
class FProjectManager
{
public:

    static FProjectManager& GetInstance();
	bool LoadProjectFromFile(const std::string& ProjectFile) { return true; };
    bool HasLoadedProject() const;
private:
    /** The project that is currently loaded in the editor */
	std::shared_ptr<FProject> CurrentProject;
};