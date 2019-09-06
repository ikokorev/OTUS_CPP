#pragma once

#include <memory>
#include <cmath>

template<typename T, size_t Size = 10>
struct CustomAllocator 
{
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename RebindedAllocType>
    struct rebind 
    {
        using other = CustomAllocator<RebindedAllocType, Size>;
    };

    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template<typename NewAllocType> 
    CustomAllocator(const CustomAllocator<NewAllocType, Size>&) 
    {
    }

    pointer allocate(std::size_t ElementsNum) 
    {
        if (!IsMemoryAllocated())
        {
            AllocateMemory();
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

    template<typename ObjectType, typename... ConstructorArgs>
    void construct(ObjectType* MemoryPtr, ConstructorArgs&&... args) 
    {
        new(MemoryPtr) ObjectType(std::forward<ConstructorArgs>(args)...);
    }

    template<typename ObjectType>
    void destroy(ObjectType* Object) 
    {
        Object->~ObjectType();
    }

private:

    bool IsMemoryAllocated() const { return MemoryStartPtr; }

    void AllocateMemory() 
    {
        MemoryStartPtr = std::malloc(AllocSize * sizeof(value_type));
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

    bool IsMemoryEmpty() const
    {
        return Offset <= 0;
    }

    void FreeMemory()
    {
        std::free(MemoryStartPtr);
        MemoryStartPtr = nullptr;
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

