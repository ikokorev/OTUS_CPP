#include <type_traits>
#include <vector>
#include <iostream>
#include <tuple>
#include <stack>

// integral
template<typename T>
typename std::enable_if<std::is_integral_v<T>>::type PrintIP(const T& IP)
{
    for (int i = sizeof(IP) - 1; i > 0; --i)
    {
        std::cout << (( IP >> ((i)*8) ) & 0xFF) << ".";
    }

    std::cout << (IP & 0xFF) << std::endl;
}

// container 
// explain dummy template arg and !equation
template<typename ContainerType, typename = typename ContainerType::value_type>
typename std::enable_if<!std::is_same_v<ContainerType, std::string>, void>::type PrintIP(const ContainerType& IP)
{
    for (auto iter = IP.cbegin(), last = --IP.end(); iter != last; ++iter)
    {
        std::cout << *iter << "..";
    }
    
    std::cout << *--IP.end() << std::endl;
}

// string
template<typename T>
typename std::enable_if<std::is_same_v<T, std::string>>::type PrintIP(const T& IP)
{
    std::cout << IP << std::endl;
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

// tuple
template<typename... Args>
typename std::enable_if<are_homogeneous_types<Args...>()>::type PrintIP(const std::tuple<Args...>& Tuple) 
{
    PrintTuple(Tuple);
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex < (std::tuple_size_v<std::tuple<Args...>> - 1)> PrintTuple(const std::tuple<Args...>& Tuple)
{
    std::cout << std::get<ElementIndex>(Tuple) << "..";
    PrintTuple<ElementIndex + 1, Args...>(Tuple);
}

template <std::size_t ElementIndex = 0, typename... Args>
typename std::enable_if_t<ElementIndex == std::tuple_size_v<std::tuple<Args...>> - 1> PrintTuple(const std::tuple<Args...>& Tuple)
{
    std::cout << std::get<ElementIndex>(Tuple) << std::endl;
}