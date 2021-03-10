#pragma once
#include <string>
#include <vector>

class CommandBatch
{
public:
	CommandBatch& operator<< (const std::string& Command);
	std::string GetBatchStartTime() const;
	const std::vector<std::string>& GetCommands() const;
	
	void Clear();

private:
	void InitBatchStartTime();

private:
	std::vector<std::string> Commands;
	std::string BatchStartTime;
};
