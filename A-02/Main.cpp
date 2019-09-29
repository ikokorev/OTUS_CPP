#include "IPPool.h"
#include <iostream>
#include "gtest/gtest.h"

void SortListDescending(IPList& List);
void OutputList(const IPList& List);

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    try
    {
        IPPool IPPool;
        IPPool.FillPoolFromInput();
        
        IPList PoolIPs {IPPool.GetIPAddresses()};
        SortListDescending(PoolIPs);
        OutputList(PoolIPs);
        
        // move ctor will be automatically called here, cause GetIPsWithBytesOrdered returns its local
        // variable as result, which automatically converts to r-value reference. 
        // move assignment operators will be called on further FiltereIPs assignments below, for the
        // same reason.
        IPList FilteredIPs {IPPool.GetIPsWithBytesOrdered(1)};
        SortListDescending(FilteredIPs);
        OutputList(FilteredIPs);

        FilteredIPs = IPPool.GetIPsWithBytesOrdered(46, 70);
        SortListDescending(FilteredIPs);
        OutputList(FilteredIPs);

        FilteredIPs = IPPool.GetIPsWithBytes(46);
        SortListDescending(FilteredIPs);
        OutputList(FilteredIPs);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return RUN_ALL_TESTS();
}

void SortListDescending(IPList& List)
{
    std::sort(List.begin(), List.end(), std::greater<IPAddress>{});
}

void OutputList(const IPList& List)
{
    for(auto IPAddress {List.cbegin()}; IPAddress != List.cend(); ++IPAddress)
    {
        for(auto IPByte {IPAddress->cbegin()}; IPByte != IPAddress->cend(); ++IPByte)
        {
            if (IPByte != IPAddress->cbegin())
            {
                std::cout << ".";
            }

            std::cout << *IPByte;
        }

        std::cout << std::endl;
    }
}