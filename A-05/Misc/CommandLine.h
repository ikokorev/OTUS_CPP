#pragma once

#include <string>

/**
 * Command line helper. Stores actual command line and provides functionallity to work with it.
 */
class FCommandLine
{
public:
    static void Set(std::string InCmdLine) { CmdLine = InCmdLine; }
    static std::string Get() { return CmdLine; }

private:
    static std::string CmdLine;
};

