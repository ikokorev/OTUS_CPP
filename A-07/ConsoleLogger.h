#pragma once

#include "CommandBatchLogger.h"

class ConsoleLogger : public CommandBatchLogger
{
public:
	virtual void LogCommandBatch(const CommandBatch& CommandBatch) override;
};
