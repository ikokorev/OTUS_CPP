#pragma once

#include <memory>

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
        if (MemoryStartPtr == nullptr)
        {
            MemoryStartPtr = std::malloc(n * AllocSize * sizeof(value_type));
        }
        
        if (Offset < AllocSize)
        {
            return reinterpret_cast<pointer>(MemoryStartPtr) + Offset++ * n;
        }
        else
        {
            throw std::bad_alloc();            
        }
    }

    void deallocate([[maybe_unused]] pointer p, [[maybe_unused]] std::size_t n) 
    {
        if (--Offset <= 0)
        {
            std::free(MemoryStartPtr);
        }
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) 
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) 
    {
        p->~T();
    }

private:

    void* MemoryStartPtr = nullptr;
    size_t Offset = 0;
    
    // MSVC STL containers implementations calls allocator allocate method on container construction.
    // So I have to extend allocator size for that one extra allocation (allocator implementation hardly depends on alloc size).
    // I'm using internal variable, cause I can't affect template parameter.
    #ifdef _MSC_VER 
        size_t AllocSize = Size + 1; 
    #else
        size_t AllocSize = Size; 
    #endif

};

