/**
 * @file
 * @brief Testing doxygen documentation generation.
 */

#include <type_traits>
#include <iostream>
#include <tuple>
#include <string>

/**
 * @brief SomeText
 * @return void
 */
template<typename T>
typename std::enable_if<std::is_integral_v<T>, std::string>::type ConvertIPToString(const T& IP)
{
    std::string Result;

    for (int ByteNum = sizeof(IP) - 1; ByteNum > 0; --ByteNum)
    {
        Result += std::to_string((( IP >> (ByteNum * 8)) & 0xFF));
        Result += ('.');
    }

    Result += std::to_string(IP & 0xFF);
    return Result;
}

// container 
template<typename ContainerType, typename = typename ContainerType::value_type> // @todo: maybe detect container another way?
typename std::enable_if<!std::is_same_v<ContainerType, std::string>, std::string>::type ConvertIPToString(const ContainerType& IP)
{
    std::string Result;

    for (auto Iter = IP.cbegin(), Last = --IP.cend(); Iter != Last; ++Iter)
    {
        Result += std::to_string(*Iter);
        Result += "..";
    }
    
    Result += std::to_string(*--IP.cend());
    return Result;
}

// string
template<typename T>
typename std::enable_if<std::is_same_v<T, std::string>, std::string>::type ConvertIPToString(const T& IP)
{
    return IP;
}

template<typename T, typename T2, typename... Args>
constexpr typename std::enable_if<std::is_same_v<T, T2>, bool>::type are_homogeneous_types()
{
    return are_homogeneous_types<T2, Args...>();
}

template<typename T>
constexpr bool are_homogeneous_types()
{
    return true;
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex == (std::tuple_size_v<std::tuple<Args...>> - 1)> PrintTuple(const std::tuple<Args...>& Tuple)
{
    std::cout << std::get<ElementIndex>(Tuple) << std::endl;
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex < (std::tuple_size_v<std::tuple<Args...>> - 1)> PrintTuple(const std::tuple<Args...>& Tuple)
{
    std::cout << std::get<ElementIndex>(Tuple) << "..";
    PrintTuple<ElementIndex + 1, Args...>(Tuple);
}

// tuple
template<std::size_t ElementIndex = 0, typename... Args>
void ConvertIPToString(const std::tuple<Args...>& Tuple) 
{
    PrintTuple(Tuple);
}

