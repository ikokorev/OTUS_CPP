#include "IPPool.h"
#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    try
    {
        IPPool IPPool;
        IPPool.FillPoolFromInput();
        
        IPList PoolIPs {IPPool.GetIPAddresses()};
        PoolIPs.SortLexicographically(true);
        PoolIPs.OutputList();
        
        // move ctor will be automatically called here, cause GetIPsWithBytesOrdered returns its local
        // variable as result, which automatically converts to r-value reference. 
        // move assignment operators will be called on further FiltereIPs assignments below, for the
        // same reason.
        IPList FilteredIPs {IPPool.GetIPsWithBytesOrdered(1)};
        FilteredIPs.SortLexicographically(true);
        FilteredIPs.OutputList();

        FilteredIPs = IPPool.GetIPsWithBytesOrdered(46, 70);
        FilteredIPs.SortLexicographically(true);
        FilteredIPs.OutputList();

        FilteredIPs = IPPool.GetIPsWithBytes(46);
        FilteredIPs.SortLexicographically(true);
        FilteredIPs.OutputList();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return RUN_ALL_TESTS();
}