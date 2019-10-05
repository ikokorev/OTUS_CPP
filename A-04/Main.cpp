#include "IPConversionFunctions.h"
#include <vector>
#include <list>

template<typename T>
void PrintIP(const T& IP)
{
    std::cout << ConvertIPToString(IP) << std::endl;
}

int main()
{
    PrintIP(char(-1));
    PrintIP(short(0));
    PrintIP(int(2130706433));

    // I don't explicitly pass and object of long or long long type, cause it has different size on different compilers.
    // The number passed below will only fit into a 64-bit signed integer, for which compiler will select a necessary type 
    // representation automatically, depending on its specs.
    PrintIP(8875824491850138409);
    
    PrintIP(std::string("115.0.50.66"));

    std::vector<long> IPAsVector {184, 15, 23, 99};
    PrintIP(IPAsVector);

    std::list<short> IPAsList {216, 76, 61, 73};
    PrintIP(IPAsList);

    std::tuple<int, int, int, int> IPAsTuple {196, 20, 34, 77};
    ConvertIPToString(IPAsTuple);

    std::tuple<long, long> IPAsAnotherTuple {255, 0};
    ConvertIPToString(IPAsAnotherTuple); 

    return 0;
}