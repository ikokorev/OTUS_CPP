#include "ProjectVersionManager.h"
#include "iostream"
#include <string>
#include "ProjectVersion.h"

void UProjectVersionManager::PrintProjectVersion()
{
    std::string ProjectVersion = 
        std::to_string(FProjectVerison::Major) + "." +
        std::to_string(FProjectVerison::Minor) + "." +
        std::to_string(FProjectVerison::Patch);

    std::cout << "Current Project Version: " << ProjectVersion << std::endl;
}