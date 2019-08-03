#pragma once

#include "IPAddress.h"
#include <vector>

class IPList
{

public:

    std::vector<IPAddress>& GetIPAddresses() { return IPAddresses; }

    void SortLexicographically(bool bShouldReverse = false);
    
    void OutputList();

private:
    
    std::vector<IPAddress> IPAddresses;
};