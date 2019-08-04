#include "IPPool.h"
#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"

bool IPPool::bAreAllIPsValid = true;
TEST(CheckIPs, AreAllIPsValid) {
    EXPECT_TRUE(IPPool::bAreAllIPsValid);
}

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
    
    bool bIsIPByteValid = true;
    for (int IPByteNum = 0; IPByteNum < MaxIPBytesNum; ++IPByteNum)
    {
        int IPByteValue = std::stoi(IPAsString.substr(Start, Stop - Start));
        
        // Validating IP byte value via google test. If some byte of ip isn't valid
        EXPECT_GE(IPByteValue, 0) << (bIsIPByteValid = false);
        EXPECT_LE(IPByteValue, 255) << (bIsIPByteValid = false);

        // If any IP byte of any IP isn't valid, all IPs no longer considere valid
        if (!bIsIPByteValid)
        {
            bAreAllIPsValid = false;
        }
        
        IP[IPByteNum] = IPByteValue;

        Start = Stop + 1;
        Stop = IPAsString.find_first_of(".", Start);
    }
    
    return IP;   
}


