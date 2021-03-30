#include "FileLogger.h"

#include <fstream>
#include <iostream>

void FileLogger::LogCommandBatch(const CommandBatch& CommandBatch)
{
    const std::string logFileName(std::string("bulk") + CommandBatch.GetBatchStartTime() + ".log");
    std::ofstream logFile(logFileName, std::ofstream::out);
    logFile << "bulk: " + CommandBatch.ToString() << std::endl;
}
