#pragma once

#include <string>
#include <vector>
#include "Figures/Interfaces/Figure.h"

/**
 * @brief
 */
class FProject
{
public:
    static std::string GetProjectName();
    static void SetProjectName(const std::string& NewProjectName);

private:
    std::string ProjectName;
};