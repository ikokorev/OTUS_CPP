#include <string>
#include <iostream>

extern int GuardedMain(const std::string& CmdLine);

/* Converting command-line arguments from default representation to result string of desired view, for futher usage. */
std::string ProcessCommandLine(int argc, char* argv[])
{
    std::string Result;

    for (int ArgNum = 0; ArgNum < argc; ++ArgNum)
    {
        // Processing command-line arguments to result string
    }

    // free memory allocated to store cmd argument values, cause we won't need it further anymore
    delete argv; 
    return Result;
}

int main(int argc, char* argv[])
{    
    int ErrorLevel = 0;

    std::string CmdLine = ProcessCommandLine(argc, argv);

    try 
    {
        ErrorLevel = GuardedMain(CmdLine);
    }
    catch (...)
    {
        // Let's assume for now that if we're here, we crashed
        // ReportCrash(GetExceptionInformation());
        // HandleError();
        // RequestExit();
        ErrorLevel = 1;
    }
    
    return ErrorLevel;
}

