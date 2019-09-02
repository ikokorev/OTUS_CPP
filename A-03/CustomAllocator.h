#pragma once

#include <memory>
#include <cmath>

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

    pointer allocate(std::size_t ElementsNum) 
    {
        if (!IsMemoryAllocated())
        {
            AllocateMemory(ElementsNum);
        }
        
        if (IsMemoryOver())
        {
            AllocateAdditionalMemory(ElementsNum);
        }
        
        return GetPointerForNextElements(ElementsNum);
    }

    void deallocate(pointer, std::size_t ElementsNum) 
    {
        RemoveElements(ElementsNum);

        if (IsMemoryEmpty())
        {
           FreeMemory();
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

    bool IsMemoryAllocated() const { return MemoryStartPtr; }

    void AllocateMemory(size_t ElementsNum) 
    {
        MemoryStartPtr = std::malloc(ElementsNum * AllocSize * sizeof(value_type));
    }

    bool IsMemoryOver() const { return Offset >= AllocSize; }

    void AllocateAdditionalMemory(size_t ElementsNum)
    {
        const double GoldenRatio = 1.62;
        // Note that on MSVC AllocSize will expand a little bit faster, cause it has extra 1 added to its size, 
        // (which will participate in AllocSize multiplication by GoldenRatio), due to STL containers calls allocator's 
        // allocate on their construction.
        // @see AllocSize variable definition.
        AllocSize = static_cast<size_t>(std::round(AllocSize * GoldenRatio));
        
        MemoryStartPtr = std::realloc(MemoryStartPtr, ElementsNum * AllocSize * sizeof(value_type));
        if (!MemoryStartPtr)
        {
            throw std::bad_alloc();
        }
    }

    void RemoveElements(size_t ElementsNum)
    {
        Offset -= ElementsNum;
    }

    bool IsMemoryEmpty() 
    {
        return Offset <= 0;
    }

    void FreeMemory()
    {
        std::free(MemoryStartPtr);
    }

    pointer GetPointerForNextElements(size_t ElementsNum) 
    { 
        return reinterpret_cast<pointer>(MemoryStartPtr) + Offset++ * ElementsNum;
    }

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

