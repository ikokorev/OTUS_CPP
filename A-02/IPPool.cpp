#include "IPPool.h"
#include <iostream>
#include <algorithm>

void IPPool::FillPoolFromInput()
{
    for(std::string InputLine; std::getline(std::cin, InputLine);)
    {
        AddIPToPool(GetIPFromString(InputLine));
    }
}

void IPPool::AddIPToPool(const IPAddress& IP)
{
    PoolIPList.GetIPAddresses().push_back(IP);
}

IPAddress IPPool::GetIPFromString(const std::string& String) const
{
    std::string IPAsString = FindIPInString(String);
    return DigitizeIPString(IPAsString);
}

std::string IPPool::FindIPInString(const std::string& String) const
{
    std::string IP;

    std::string::size_type Start = 0;
    std::string::size_type Stop = String.find_first_of("\t");
    
    if (Stop != std::string::npos)
    {
        IP = String.substr(Start, Stop - Start);
    }

    return IP;
}

IPAddress IPPool::DigitizeIPString(const std::string& IPAsString) const
{
    IPAddress IP;
    int MaxIPBytesNum = static_cast<int>(IP.size());
    
    std::string::size_type Start = 0;
    std::string::size_type Stop = IPAsString.find_first_of(".");
    
    for (int IPByteNum = 0; IPByteNum < MaxIPBytesNum; ++IPByteNum)
    {
        IP[IPByteNum] = std::stoi(IPAsString.substr(Start, Stop - Start));

        Start = Stop + 1;
        Stop = IPAsString.find_first_of(".", Start);
    }
    
    return IP;   
}
