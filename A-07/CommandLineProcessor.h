#pragma once

#include <string>
#include "MulticastDelegate.h"
#include "CommandBatch.h"

using FOnCommandBatchProcessedDelegate = TMulticastDelegate<const CommandBatch&>;

class CommandLineProcessor
{
public:
	CommandLineProcessor(int CommandBatchSize) : CommandBatchSize(CommandBatchSize) {}
	FOnCommandBatchProcessedDelegate& GetOnCommandBatchProcessedDelegate();

	void ProcessSingleCommand(const std::string& Command);
	void Flush();

private:
	bool HasPartiallyFormedRegularCommandBatch() const;
	bool IsProcessingDynamicSizeCommandBatch() const;
	void NotifyCommandBatchProcessed();
	bool HasFormedCommandBatch() const;

private:
	int CommandBatchSize = 0;
	CommandBatch CurrentCommandBatch {};
	
	FOnCommandBatchProcessedDelegate OnCommandBatchProcessedDelegate {};

	struct ProcessedBatchState
	{
		void Reset()
		{
			CommandsCount = 0;
			DynamicSizeCommandBatchIndicatorLevel = 0;
		}
		
		int CommandsCount = 0;
		int DynamicSizeCommandBatchIndicatorLevel = 0;
	};
	ProcessedBatchState ProcessedBatchState;
};


