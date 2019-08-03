#pragma once

#include "IPList.h"
#include <string>

class IPPool
{

public:

    void FillPoolFromInput();

    void AddIPToPool(const IPAddress& IP);

    IPList GetIPAddresses() const { return PoolIPList; }

    /**  
     * Returns all IP addresses from pool whose byte(s), in order from first one, 
     * matches the required byte(s). 
     */
    template<typename... Args>
    IPList GetIPsWithBytesOrdered(Args... RequiredBytesOrdered)
    {
        IPList ListToFilter = PoolIPList;
        IPList CurrByteFilteredIPs;
        
        std::vector<int> RequiredBytesVec{RequiredBytesOrdered...};        
        int RequiredBytesNum = static_cast<int>(RequiredBytesVec.size());
        int MaxIPBytesNum = 4;

        for 
        (
            int ByteNum = 0; 
            ByteNum < RequiredBytesNum && ByteNum < MaxIPBytesNum; 
            ++ByteNum, ListToFilter = CurrByteFilteredIPs
        )
        {
            CurrByteFilteredIPs.GetIPAddresses().clear();
            
            for (auto IPAddress : ListToFilter.GetIPAddresses())
            {
                if (IPAddress[ByteNum] == RequiredBytesVec[ByteNum])
                {
                    CurrByteFilteredIPs.GetIPAddresses().push_back(IPAddress);
                }
            }
        }

        return ListToFilter;
    }

    /**  Returns all IP addresses from pool which has required byte(s) at any position(s). */
    template<typename... Args>
    IPList GetIPsWithBytes(Args... RequiredBytes)
    {
        IPList ListToFilter = PoolIPList;
        IPList CurrByteFilteredIPs;
        
        std::vector<int> RequiredBytesVec{RequiredBytes...};        
        int RequiredBytesNum = static_cast<int>(RequiredBytesVec.size());
        int MaxIPBytesNum = 4;

        for 
        (
            int ByteNum = 0; 
            ByteNum < RequiredBytesNum && ByteNum < MaxIPBytesNum; 
            ++ByteNum, ListToFilter = CurrByteFilteredIPs
        )
        {
            CurrByteFilteredIPs.GetIPAddresses().clear();
            
            for (auto IPAddress : ListToFilter.GetIPAddresses())
            {
                for (auto IPByte : IPAddress)
                {
                    if (IPByte == RequiredBytesVec[ByteNum])
                    {
                        CurrByteFilteredIPs.GetIPAddresses().push_back(IPAddress);                        
                        break; // we don't need IP address to be added several times, if it has required byte at several positions
                    }
                }
            }
        }

        return ListToFilter;
    }

private:

    IPAddress GetIPFromString(const std::string& String) const;

    std::string FindIPInString(const std::string& String) const;

    IPAddress DigitizeIPString(const std::string& IPAsString) const;

    IPList PoolIPList;
};