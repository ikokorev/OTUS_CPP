#include "ProjectVersionManager.h"
#include <iostream>
#include <string>
#include "ProjectVersion.h"

FProjectVersion UProjectVersionManager::GetProjectVersion()
{
    return FProjectVersion();
}

void UProjectVersionManager::PrintProjectVersion()
{
    FProjectVersion ProjectVersion = GetProjectVersion();
    std::string ProjectVersionStr = 
        std::to_string(ProjectVersion.Major) + "." +
        std::to_string(ProjectVersion.Minor) + "." +
        std::to_string(ProjectVersion.Patch);

    std::cout << "Current Project Version: " << ProjectVersionStr << std::endl;
}