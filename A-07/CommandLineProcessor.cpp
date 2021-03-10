#include "CommandLineProcessor.h"

const auto DynamicSizeCommandBatchStartSymbol = "{";
const auto DynamicSizeCommandBatchEndSymbol = "}";

FOnCommandBatchProcessedDelegate& CommandLineProcessor::GetOnCommandBatchProcessedDelegate()
{
	return OnCommandBatchProcessedDelegate;
}

void CommandLineProcessor::ProcessSingleCommand(const std::string& Command)
{
	if (Command == DynamicSizeCommandBatchStartSymbol)
	{
		if (HasPartiallyFormedRegularCommandBatch())
		{
			NotifyCommandBatchProcessed();
		}
		
		++ProcessedBatchState.DynamicSizeCommandBatchIndicatorLevel;
	}
	else if (Command == DynamicSizeCommandBatchEndSymbol)
	{
		--ProcessedBatchState.DynamicSizeCommandBatchIndicatorLevel;

		if (ProcessedBatchState.DynamicSizeCommandBatchIndicatorLevel <= 0)
		{
			NotifyCommandBatchProcessed();
		}
	}
	else
	{
		++ProcessedBatchState.CommandsCount;
		CurrentCommandBatch << Command;

		if (HasFormedCommandBatch())
		{
			NotifyCommandBatchProcessed();
		}
	}
}

bool CommandLineProcessor::HasPartiallyFormedRegularCommandBatch() const
{
	return !IsProcessingDynamicSizeCommandBatch() && ProcessedBatchState.CommandsCount > 0;
}

bool CommandLineProcessor::IsProcessingDynamicSizeCommandBatch() const
{
	return ProcessedBatchState.DynamicSizeCommandBatchIndicatorLevel > 0;
}

void CommandLineProcessor::NotifyCommandBatchProcessed()
{
	OnCommandBatchProcessedDelegate.Broadcast(CurrentCommandBatch);
	CurrentCommandBatch.Clear();
	ProcessedBatchState.Reset();
}

bool CommandLineProcessor::HasFormedCommandBatch() const
{
	return !IsProcessingDynamicSizeCommandBatch() && ProcessedBatchState.CommandsCount >= CommandBatchSize;
}

void CommandLineProcessor::Flush()
{
	if (!IsProcessingDynamicSizeCommandBatch())
	{
		NotifyCommandBatchProcessed();
	}
}
