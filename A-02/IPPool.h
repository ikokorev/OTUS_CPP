#pragma once

#include "IPList.h"
#include <string>

class IPPool
{

public:

    void FillPoolFromInput();

    void AddIPToPool(const IPAddress&& IP);

    IPList GetIPAddresses() const { return PoolIPList; }

    /**  
     * Returns all IP addresses from pool whose byte(s), in order from first one, 
     * matches the required byte(s). 
     */
    template<typename... Args>
    IPList GetIPsWithBytesOrdered(Args... RequiredBytesOrdered)
    {
        IPList ListToFilter {PoolIPList};
        IPList CurrByteFilteredIPs;
        
        // Just playing with move semantics here. I understand it makes no sense to use it with
        // few ints, but with really big object it could be reasonable.
        std::vector<int> RequiredBytesVec{std::move(RequiredBytesOrdered)...};        
        int RequiredBytesNum {static_cast<int>(RequiredBytesVec.size())};
        int MaxIPBytesNum {4};

        for 
        (
            int ByteNum {0}; 
            ByteNum < RequiredBytesNum && ByteNum < MaxIPBytesNum; 
            ++ByteNum, ListToFilter = CurrByteFilteredIPs
        )
        {
            CurrByteFilteredIPs.clear();
            
            for (auto& IPAddress : ListToFilter)
            {
                if (IPAddress[ByteNum] == RequiredBytesVec[ByteNum])
                {
                    CurrByteFilteredIPs.push_back(std::move(IPAddress));
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
        
        std::vector<int> RequiredBytesVec{std::move(RequiredBytes)...};        
        int RequiredBytesNum {static_cast<int>(RequiredBytesVec.size())};
        int MaxIPBytesNum {4};

        for 
        (
            int ByteNum {0}; 
            ByteNum < RequiredBytesNum && ByteNum < MaxIPBytesNum; 
            ++ByteNum, ListToFilter = CurrByteFilteredIPs
        )
        {
            CurrByteFilteredIPs.clear();
            
            for (auto& IPAddress : ListToFilter)
            {
                for (auto& IPByte : IPAddress)
                {
                    if (IPByte == RequiredBytesVec[ByteNum])
                    {
                        CurrByteFilteredIPs.push_back(std::move(IPAddress));                        
                        break; // we don't need IP address to be added several times, if it has required byte at several positions
                    }
                }
            }
        }

        return ListToFilter;
    }

private:

    /* Returns true if managed to obtain valid IP from string. The result is written in out IPAddress parameter. */
    bool GetIPFromString(const std::string& String, IPAddress& OutIP) const;

    std::string FindIPInString(const std::string& String) const;

    /* 
     * Returns true if all ip bytes from string of valid value, false if any byte value isn't valid. 
     * The result is written in out IPAddress parameter. 
     */
    bool ConvertIPStringToAddress(const std::string& IPAsString, IPAddress& OutIP) const;

    bool IsByteValueValid(int ByteValue) const;

    IPList PoolIPList;
};