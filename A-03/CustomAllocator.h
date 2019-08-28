#include <memory>
#include <iostream>
#include <type_traits>
#include <array>
#include <stack>

template<typename T, size_t Size>
struct CustomAllocator 
{
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind 
    {
        using other = CustomAllocator<U, Size>;
    };

    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template<typename U> 
    CustomAllocator(const CustomAllocator<U, Size>&) 
    {
    }

    pointer allocate(std::size_t n) 
    {
        std::cout << "\nAllocating " << n << " element(s)." << std::endl;

        if (!IsMemoryReserved)
        {
            std::cout << "Reserving memory for " << Size << " elements. " 
            << "Value type sizeof is - " << sizeof(value_type) << std::endl;
            
            IsMemoryReserved = true;
            MemoryStartPtr = std::malloc(n * Size * sizeof(value_type));
        }
        
        if (Offset < Size)
        {
            std::cout << "Correct allocation with offset - " << Offset << std::endl;
            auto MemoryPtrForNextObject = reinterpret_cast<pointer>(MemoryStartPtr) + Offset++ * n;
            
            std::cout << MemoryPtrForNextObject << std::endl;
            return MemoryPtrForNextObject;
        }
        else
        {
            std::cout << "Bad Allocation, allocator reserved memory for " << Size << " element(s), " 
            << "you trying to add element No - " << Offset + 1 << std::endl;
            throw std::bad_alloc();            
        }
    }

    void deallocate(pointer p, std::size_t n) 
    {
        std::cout << "Deallocating " << n << " element(s). Pointer address - " << p << std::endl;
        std::free(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) 
    {
        std::cout << "Construct" << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) 
    {
        std::cout << "Destroy" << std::endl;
        p->~T();
    }

private:

    void* MemoryStartPtr;
    bool IsMemoryReserved = false;
    size_t Offset = 0;
};

