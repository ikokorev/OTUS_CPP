#include "IPList.h"
#include <iostream>
#include <algorithm>

void IPList::SortLexicographically(bool bShouldReverse /* = false */)
{
    auto Comparator = [bShouldReverse](const IPAddress& LhsIP, const IPAddress& RhsIP) -> bool 
    {
        int MaxIPBytesNum = static_cast<int>(LhsIP.size());

        for(int IPByteNum = 0; IPByteNum < MaxIPBytesNum; ++IPByteNum)
        {
            if (LhsIP[IPByteNum] > RhsIP[IPByteNum])
            {
                return bShouldReverse ? true : false;
            }
            else if (LhsIP[IPByteNum] < RhsIP[IPByteNum])
            {
                return bShouldReverse ? false : true;
            }
        }

        return LhsIP.size() < RhsIP.size();
    };

    std::sort(IPAddresses.begin(), IPAddresses.end(), Comparator);
}

void IPList::OutputList()
{
    for(auto IPAddress = IPAddresses.cbegin(); IPAddress != IPAddresses.cend(); ++IPAddress)
    {
        for(auto IPByte = IPAddress->cbegin(); IPByte != IPAddress->cend(); ++IPByte)
        {
            std::cout << *IPByte;

            if (IPByte != IPAddress->cend())
            {
                std::cout << ".";
            }
        }

        std::cout << std::endl;
    }
}