#include "FileLogger.h"

#include <fstream>
#include <iostream>

void FileLogger::LogCommandBatch(const CommandBatch& CommandBatch)
{
    const std::string logFileName(std::string("bulk") + CommandBatch.GetBatchStartTime() + ".log");
    std::ofstream logFile(logFileName, std::ofstream::out);
    logFile << FormCommandBatchLogMessage(CommandBatch) << std::endl;
}
