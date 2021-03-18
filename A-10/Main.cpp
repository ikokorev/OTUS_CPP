#include "CommandLineProcessor.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

#include <algorithm>
#include <future>
#include <iostream>

bool IsNaturalNumber(const std::string&& String)
{
	return !String.empty() &&
         std::count_if(String.begin(), String.end(), [](auto character) 
		 {
           return character >= '0' && character <= '9';
         }) == static_cast<long long>(String.size());
}

void ConsoleLoggerThread(CommandLineProcessor& CmdProcessor)
{
	CmdProcessor.GetOnCommandBatchProcessedDelegate().AddCallback([](const CommandBatch& CommandBatch)
	{
		std::cout << "MT Log called" << std::endl;
	});
}

void FileLoggerThread1(CommandLineProcessor& CmdProcessor)
{
	CmdProcessor.GetOnCommandBatchProcessedDelegate().AddCallback([](const CommandBatch& CommandBatch)
	{
		std::cout << "MT FT1 called" << std::endl;
	});
}

void FileLoggerThread2(CommandLineProcessor& CmdProcessor)
{
	CmdProcessor.GetOnCommandBatchProcessedDelegate().AddCallback([](const CommandBatch& CommandBatch)
	{
		std::cout << "MT FT2 called" << std::endl;
	});

	//std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main(int argc, char *argv[])
{
	try
	{
		if (argc > 1)
		{
			auto* const givenCommandBatchSize = argv[1];
			if (IsNaturalNumber(givenCommandBatchSize))
			{
				CommandLineProcessor cmdProcessor{ std::stol(givenCommandBatchSize) };

				FileLogger fileLogger;
				ConsoleLogger consoleLogger;

				auto& commandBatchProcessedDelegate = cmdProcessor.GetOnCommandBatchProcessedDelegate();
				/*commandBatchProcessedDelegate.AddCallback([FileLoggerPtr = &fileLogger](const CommandBatch& CommandBatch)
				{
					FileLoggerPtr->LogCommandBatch(CommandBatch);
				});*/
				
				commandBatchProcessedDelegate.AddCallback([ConsoleLoggerPtr = &consoleLogger](const CommandBatch& CommandBatch)
				{
					ConsoleLoggerPtr->LogCommandBatch(CommandBatch);
				});

				std::thread t1{ ConsoleLoggerThread, std::ref(cmdProcessor) };
				std::thread t2{ FileLoggerThread1, std::ref(cmdProcessor) };
				std::thread t3{ FileLoggerThread2, std::ref(cmdProcessor) };

				
				t1.join();
				t2.join();
				t3.join();
				
				std::string commandLine;
				while (std::cin >> commandLine)
				{
					cmdProcessor.ProcessSingleCommand(commandLine);
				}

				cmdProcessor.Flush();
			}
			else
			{
				std::cerr << "Given command batch size isn't a natural number" << std::endl;
			}
		}
		else
		{
			std::cout << "Specify command bulk size as the only argument when running this program (it should be a natural number)." << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
