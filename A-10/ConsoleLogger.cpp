#include "ConsoleLogger.h"

#include <iostream>

void ConsoleLogger::LogCommandBatch(const CommandBatch& CommandBatch)
{
	std::cout << "bulk: " + CommandBatch.ToString() << std::endl;
}
