#include "IPPool.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    try
    {
        IPPool IPPool;
        IPPool.FillPoolFromInput();
        
        IPList PoolIPs = IPPool.GetIPAddresses();
        PoolIPs.SortLexicographically(true);
        PoolIPs.OutputList();
        
        IPList FilteredIPs = IPPool.GetIPsWithBytesOrdered(1);
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

    return 0;
}