#include "IPPool.h"
#include <iostream>
#include <algorithm>

void IPPool::FillPoolFromInput()
{
    for(std::string InputLine; std::getline(std::cin, InputLine);)
    {
        // Move semantics will be used during IP push_back by default, cause GetIPFromString obtains and 
        // returns IPAddress from function (ConvertIPStringToAddress), which return its local IPAddress 
        // variable as result, so it automatically converts to r-value reference. I tested that principle 
        // on provided from source Tracer class, and it worked.
        AddIPToPool(GetIPFromString(InputLine));
    }
}

void IPPool::AddIPToPool(const IPAddress& IP)
{
    PoolIPList.GetIPAddresses().push_back(IP);
}

IPAddress IPPool::GetIPFromString(const std::string& String) const
{
    return ConvertIPStringToAddress(FindIPInString(String));
}

std::string IPPool::FindIPInString(const std::string& String) const
{
    std::string::size_type Start {0};
    std::string::size_type Stop {String.find_first_of("\t")};
    
    if (Stop != std::string::npos)
    {
        return String.substr(Start, Stop - Start);
    }

    return std::string();
}

IPAddress IPPool::ConvertIPStringToAddress(const std::string& IPAsString) const
{
    IPAddress IP;
    int MaxIPBytesNum {static_cast<int>(IP.size())};
    
    std::string::size_type Start {0};
    std::string::size_type Stop {IPAsString.find_first_of(".")};
    
    for (int IPByteNum = 0; IPByteNum < MaxIPBytesNum; ++IPByteNum)
    {
        IP[IPByteNum] = std::stoi(IPAsString.substr(Start, Stop - Start));

        Start = Stop + 1;
        Stop = IPAsString.find_first_of(".", Start);
    }
    
    return IP;   
}
