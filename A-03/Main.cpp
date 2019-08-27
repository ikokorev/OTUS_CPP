#include <iostream>
#include "CustomAllocator.h"
#include <map>
#include <list>
#include <vector>

int Factorial(int Number)
{
    if(Number < 0)
    {
        return 0;
    } 
        
    if (Number == 0)
    {
        return 1;
    }
        
    return Number * Factorial(Number - 1);
}

int main()
{
    const size_t AllocSize = 10; 
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, AllocSize>> FactorialValues;
    
    // Full filling of the allocator by its size causes bad allocation exception, e.g to fill allocator with
    // 10 elements I have to use CustomAllocator with size equals to 11. So here I substract 1 from AllocSize,
    // cause its temporarly irrelevant (I have to figure out, how to create a valid allocator with reserve first).
    for (size_t i = 0; i < AllocSize - 1; ++i) 
    {
        FactorialValues.emplace(i, Factorial(i));
        std::cout << "\nAdded element to map, its value - " << FactorialValues.at(i) << std::endl;
    }

    for (auto Elem : FactorialValues)
    {
        std::cout << Elem.second << std::endl;
    }

    return 0;
}