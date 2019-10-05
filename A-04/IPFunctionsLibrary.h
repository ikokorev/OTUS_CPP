/**
 * @file
 * @brief Testing doxygen documentation generation.
 */

#include <type_traits>
#include <string>
#include <tuple>
#include <iostream>

/**
 * @brief SomeText
 * @return void
 */
template<typename T>
typename std::enable_if<std::is_integral_v<T>, std::string>::type 
ConvertIPToString(const T& IP)
{
    std::string Result;

    for (int ByteNum = sizeof(IP) - 1; ByteNum > 0; --ByteNum)
    {
        Result += std::to_string((( IP >> (ByteNum * 8)) & 0xFF));
        Result += ('.');
    }

    // adds last byte separetely, to avoid "if" statement inside the cycle, to decide if we need to add dot.
    Result += std::to_string(IP & 0xFF); 
    return Result;
}

// container 
template<typename ContainerType, typename = typename ContainerType::value_type> // @todo: maybe detect container another way?
typename std::enable_if<!std::is_same_v<ContainerType, std::string>, std::string>::type 
ConvertIPToString(const ContainerType& IP)
{
    std::string Result;
    auto LastElement = IP.cend() - 1;

    for (auto Iter = IP.cbegin(); Iter != LastElement; ++Iter)
    {
        Result += std::to_string(*Iter);
        Result += "..";
    }
    
    // adds last element separetely, to avoid "if" statement inside the cycle, to decide if we need to add double dot.
    Result += std::to_string(*LastElement);
    return Result;
}

// string
template<typename T>
typename std::enable_if<std::is_same_v<T, std::string>, std::string>::type 
ConvertIPToString(const T& IP)
{
    return IP;
}

template<typename T>
constexpr bool AreHomogeneousTypes()
{
    return true;
}

template<typename T, typename T2, typename... Args>
constexpr bool AreHomogeneousTypes()
{
    if (std::is_same_v<T, T2>)
    {
        return AreHomogeneousTypes<T2, Args...>();
    }
    
    return false;
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex == (std::tuple_size_v<std::tuple<Args...>> - 1)> 
ConvertTupleToString(const std::tuple<Args...>& Tuple, std::string& OutResult)
{
    // stops recursion and adds last element without double dot at the end
    OutResult += std::to_string(std::get<ElementIndex>(Tuple));
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex < (std::tuple_size_v<std::tuple<Args...>> - 1)> 
ConvertTupleToString(const std::tuple<Args...>& Tuple, std::string& OutResult)
{
    OutResult += std::to_string(std::get<ElementIndex>(Tuple));
    OutResult += "..";
    
    ConvertTupleToString<ElementIndex + 1, Args...>(Tuple, OutResult);
}

// tuple
template<std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if<AreHomogeneousTypes<Args...>(), std::string>::type 
ConvertIPToString(const std::tuple<Args...>& Tuple) 
{
    std::string Result;
    ConvertTupleToString(Tuple, Result);

    return Result;
}

template<typename T>
void PrintIP(const T& IP)
{
    std::cout << ConvertIPToString(IP) << std::endl;
}

