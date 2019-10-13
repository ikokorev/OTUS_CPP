/**
 * @file 
 * @brief Function library to work with IP addresses. Implemented via templates to practice metaprogramming. 
 * @details The library currently contains conversion functions of different IP representations to string, and printing function
 * of the result of such conversion.
 */

#include <type_traits>
#include <string>
#include <tuple>
#include <iostream>

/**
 * @brief Converts IP address represented as an arbitrary integer type to corresponding string.
 * @details IP bytes are added to result string starting with the most significant byte of given integer, with "." as separator.
 * @tparam T Arbitrary integer type, representing IP address.
 * @param IP An integer representation of IP address to convert.
 * @return The result of conversion as std::string.
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

/**
 * @brief Converts IP address represented as container to string. std::string isn't supported - it has it's own conversion func specialization.
 * @details IP bytes are added to result string from container elements, starting from the beginning to the end, with ".." as separator.
 * Container elements type should be supported by std::to_string conversion. Use default supported types or define std::to_string specialization for your custom type.
 * @tparam ContainerType Container type, representing IP address.
 * @param IP Container of IP address bytes.
 * @return The result of conversion as std::string.
 */
template<typename ContainerType, typename = typename ContainerType::value_type> // @todo: maybe detect container another way?
typename std::enable_if<!std::is_same_v<ContainerType, std::string>, std::string>::type 
ConvertIPToString(const ContainerType& IP)
{
    std::string Result;
    auto LastElement = std::prev(IP.end());

    for (auto Iter = IP.begin(); Iter != LastElement; ++Iter)
    {
        Result += std::to_string(*Iter);
        Result += "..";
    }
    
    // adds last element separetely, to avoid "if" statement inside the cycle, to decide if we need to add double dot.
    Result += std::to_string(*LastElement);
    return Result;
}

/**
 * @brief "Converts" IP address represented as string, to a string.
 * @details That's a dummy "conversion", to practice metaprogramming. The case is that std::string can be managed as container,
 * and I should segregate std::string from other containers, for my IP conversion method.
 * @tparam T Dummy type, which validates to be std::string, to take advantage of SFINAE.
 * @param IP std::string, representing IP address.
 * @return Simply returns given IP.
 */
template<typename T>
typename std::enable_if<std::is_same_v<T, std::string>, std::string>::type 
ConvertIPToString(const T& IP)
{
    return IP;
}

/**
 * @brief One type is considered to be homogeneous to himself, which is logical.
 */
template<typename T>
constexpr bool AreHomogeneousTypes()
{
    return true;
}

/**
 * @brief Validates any number of types to be homogeneous, at compile time.
 * @return Returns corresponding bool value, if types are homogeneous or not.
 */
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
    // stops recursion and adds last element to result.
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

/**
 * @brief Converts IP address, represented as tuple of homogeneous types, to a string.
 * @details Tuple types should be homogeneous, and be supported by std::to_string conversion. Use default supported types for tuple elements type,
 * or define std::to_string specialization for your custom type. IP bytes are added to result string from tuple elements, with ".." as separator.
 * @tparam ElementIndex Internal non-templated template parameter, for iterating through tuple elements at complie time. You can specify from which element 
 * to start, if you want.
 * @tparam Args Parameter pack of tuple elements types.
 * @param Tuple Acutal tuple, representing IP address.
 * @return The result of conversion as std::string.
 */
template<std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if<AreHomogeneousTypes<Args...>(), std::string>::type 
ConvertIPToString(const std::tuple<Args...>& Tuple) 
{
    std::string Result;
    ConvertTupleToString(Tuple, Result);

    return Result;
}

/**
 * @brief Outputs via cout the result of IP to string conversion, with line break at the end.
 * @tparam T Type, representing IP address.
 * @param IP Actual IP address to be converted and outputted.
 */
template<typename T>
void PrintIP(const T& IP)
{
    std::cout << ConvertIPToString(IP) << std::endl;
}

