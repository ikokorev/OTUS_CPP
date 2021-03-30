#pragma once

#include "CommandBatch.h"

class CommandBatchLogger
{
public:
	virtual void LogCommandBatch(const CommandBatch& CommandBatch) = 0;
	virtual ~CommandBatchLogger() = default;
};