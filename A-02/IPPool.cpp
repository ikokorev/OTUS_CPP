#include "IPPool.h"
#include <iostream>
#include <algorithm>

void IPPool::FillPoolFromInput()
{
    IPAddress OutIP;
    for(std::string InputLine; std::getline(std::cin, InputLine);)
    {
        if (GetIPFromString(InputLine, OutIP))
        {
            AddIPToPool(std::move(OutIP));
        }
    }
}

void IPPool::AddIPToPool(const IPAddress&& IP)
{
    PoolIPList.push_back(IP);
}

bool IPPool::GetIPFromString(const std::string& String, IPAddress& OutIP) const
{
    return ConvertIPStringToAddress(FindIPInString(String), OutIP);
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

bool IPPool::ConvertIPStringToAddress(const std::string& IPAsString, IPAddress& OutIP) const
{
    int MaxIPBytesNum {static_cast<int>(OutIP.size())};
    bool bAreAllIPBytesValid = true;

    std::string::size_type Start {0};
    std::string::size_type Stop {IPAsString.find_first_of(".")};
    
    for (int IPByteNum = 0; IPByteNum < MaxIPBytesNum; ++IPByteNum)
    {
        int IPByteValue = std::stoi(IPAsString.substr(Start, Stop - Start));
        
        if (!IsByteValueValid(IPByteValue))
        {
            bAreAllIPBytesValid = false;
            break;
        }
        
        OutIP[IPByteNum] = IPByteValue;

        Start = Stop + 1;
        Stop = IPAsString.find_first_of(".", Start);
    }
    
    return bAreAllIPBytesValid;   
}

bool IPPool::IsByteValueValid(int ByteValue) const
{
    return ByteValue >= 0 && ByteValue <= 255;
}
