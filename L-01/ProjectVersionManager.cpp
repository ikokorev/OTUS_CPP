#include "ProjectVersionManager.h"
#include "iostream"
#include <string>
#include "ProjectVersion.h"

void UProjectVersionManager::PrintProjectVersion()
{
    std::string ProjectVersion = 
        std::to_string(FProjectVersion::Major) + "." +
        std::to_string(FProjectVersion::Minor) + "." +
        std::to_string(FProjectVersion::Patch);

    std::cout << "Current Project Version: " << ProjectVersion << std::endl;
}