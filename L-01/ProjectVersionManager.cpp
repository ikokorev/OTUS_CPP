#include "ProjectVersionManager.h"
#include "ProjectVersion.h"

std::string UProjectVersionManager::GetProjectVersion()
{
    std::string ProjectVersion = 
        std::to_string(FProjectVerison::Major) + "." +
        std::to_string(FProjectVerison::Minor) + "." +
        std::to_string(FProjectVerison::Patch);

    return ProjectVersion;
}