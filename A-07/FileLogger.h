#pragma once

#include "CommandBatchLogger.h"

class FileLogger : public CommandBatchLogger
{
public:
	virtual void LogCommandBatch(const CommandBatch& CommandBatch) override;
};
