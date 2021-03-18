#include "CommandBatchLogger.h"

std::string CommandBatchLogger::FormCommandBatchLogMessage(const CommandBatch& CommandBatch) const
{
    std::string message {};
	
    const auto& commands = CommandBatch.GetCommands();
    if (!commands.empty())
    {
        message += "bulk: ";
        const auto lastCommand = std::prev(commands.end());

        for (auto it = commands.begin(); it != lastCommand; ++it)
        {
            message += *it;
            message += ", ";
        }

        message += *lastCommand;
    }

    return message;
}
