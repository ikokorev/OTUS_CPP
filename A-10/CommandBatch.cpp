#include "CommandBatch.h"
#include <chrono>
#include <ctime>

CommandBatch& CommandBatch::operator<<(const std::string& Command)
{
	if (Commands.empty())
	{
		InitBatchStartTime();
	}

	Commands.push_back(Command);
	
	return *this;
}

std::string CommandBatch::GetBatchStartTime() const
{
	return BatchStartTime;
}

std::string CommandBatch::ToString() const
{
	std::string result;
	
	const auto lastCommand = std::prev(Commands.end());
	for (auto it = Commands.begin(); it != lastCommand; ++it)
	{
		result += *it;
		result += ", ";
	}
	result += *lastCommand;

	return result;
}

const std::vector<std::string>& CommandBatch::GetCommands() const
{
	return Commands;
}

void CommandBatch::Clear()
{
	Commands.clear();
	BatchStartTime.clear();
}

void CommandBatch::InitBatchStartTime()
{
	const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	const std::time_t epochTime = std::chrono::system_clock::to_time_t(now);
	BatchStartTime = std::to_string(epochTime);
}
