#include "ConsoleLogger.h"

#include <iostream>

void ConsoleLogger::LogCommandBatch(const CommandBatch& CommandBatch)
{
	std::cout << FormCommandBatchLogMessage(CommandBatch) << std::endl;
}
