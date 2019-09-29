#pragma once

#include <memory>
#include <cmath>
#include "MemoryBucket.h"

template<typename T, size_t Size = 10>
struct ReservingAllocator 
{
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename RebindedAllocType>
    struct rebind 
    {
        using other = ReservingAllocator<RebindedAllocType, Size>;
    };

    ReservingAllocator() = default;
    ~ReservingAllocator() = default;

    template<typename NewAllocType> 
    ReservingAllocator(const ReservingAllocator<NewAllocType, Size>&) 
    {
    }

    /**
     * Always returns memory for one element, dispite to the value of argument, it just required by standart.
     * You don't have to pass it, it has a default value as logic hint (cause argument isn't used in func body anyway).
     * It is done so, because allocator manages memory reservation via memory buckets internaly by itself, you don't need 
     * to affect it manually by allocating memory for multiply elements.
     */
    pointer allocate(std::size_t = 1) 
    {
        if (!HasValidActiveBucket())
        {
            InitiateActiveBucket();
        }
        
        if (IsOutOfFreeMemory())
        {
            CreateNewBucket();
        }
        
        IncreaseAllocatedElemsNum();
        return GetPointerForNextElement();
    }

    void deallocate(pointer, std::size_t ElementsNum) 
    {
        RemoveElements(ElementsNum);

        if (IsMemoryNoLongerRequired())
        {
           FreeAllocatedMemory();
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

    bool HasValidActiveBucket() const { return ActiveBucket && ActiveBucket->MemoryStorageStartPtr; }

    void InitiateActiveBucket() 
    {
        ActiveBucket = new MemoryBucket(std::malloc(AllocSize * sizeof(value_type)));

        if (ActiveBucket->MemoryStorageStartPtr == nullptr)
        {
            throw std::bad_alloc();
        }
    }

    bool IsOutOfFreeMemory() const 
    { 
        return AllocatedElemsNum >= AllocSize; 
    }

    void CreateNewBucket()
    {
        AllocSize += Size;

        MemoryBucket* NewBucket = new MemoryBucket(std::malloc(Size * sizeof(value_type)));
        
        if (NewBucket->MemoryStorageStartPtr == nullptr)
        {
            throw std::bad_alloc();
        }

        NewBucket->PreviousBucket = ActiveBucket;
        ActiveBucket = NewBucket;

        ResetActiveBucketMemoryOffset();
    }

    void ResetActiveBucketMemoryOffset()
    {
        ActiveBucketMemoryOffset = 0;
    }

    void IncreaseAllocatedElemsNum()
    {
        ++AllocatedElemsNum;
    }

    pointer GetPointerForNextElement() 
    {
        return reinterpret_cast<pointer>(ActiveBucket->MemoryStorageStartPtr) + ActiveBucketMemoryOffset++;
    }

    void RemoveElements(size_t ElementsNum)
    {
        AllocatedElemsNum -= ElementsNum;
    }

    bool IsMemoryNoLongerRequired() const
    {
        return AllocatedElemsNum <= 0;
    }

    void FreeAllocatedMemory()
    {
        while (ActiveBucket)
        {
            MemoryBucket* PrevBucket = ActiveBucket->PreviousBucket;
            delete ActiveBucket;
            ActiveBucket = PrevBucket;
        }
    }

    MemoryBucket* ActiveBucket {nullptr};
    size_t AllocatedElemsNum {0};
    size_t ActiveBucketMemoryOffset {0};
    
    // MSVC STL containers implementations calls allocator allocate method on container construction.
    // So I have to extend allocator size for that one extra allocation (allocator implementation hardly depends on alloc size).
    // I'm using internal variable, cause I can't affect template parameter.
    #ifdef _MSC_VER 
        size_t AllocSize {Size + 1}; 
    #else
        size_t AllocSize {Size}; 
    #endif

};

