#pragma once

#include <string>

/**
 * Helper class to work with paths (directories, files). E.g:
 * - Retrieving editor dir, project dir, etc.
 * - Working with relative & absolute paths
 * - Working with files at path (check if file exsists, get file extension etc)
 */
class FPaths
{
public:
    /* Returns the path to the currently loaded project file. */
    static std::string GetProjectFilePath();

    /* Sets the path to the project file. */
    static void SetProjectFilePath(const std::string& NewProjectFilePath);

private:
    /** Holds the path to the currently loaded project file. */
    static std::string ProjectFilePath;
};