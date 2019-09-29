#pragma once

#include "ForwardIterator.h"
#include <memory>

template<typename Type, typename AllocType = std::allocator<Type>>
class ForwardList
{

public:

    ForwardList() = default;
    ~ForwardList()
    {
        Clear();
    }

    void Push(const Type& Value)
    {
        ForwardNode<Type>* NewNode = std::allocator_traits<NodeAllocType>::allocate(Allocator, 1);
        std::allocator_traits<NodeAllocType>::construct(Allocator, NewNode, Value);

        if(Head)
        {
			Tail->Next = NewNode;
			Tail = NewNode;
		} 
        else 
        {
			Head = Tail = NewNode;
		}

        ++Size;
    }

    ForwardIterator<Type> begin() const
    {
        return ForwardIterator<Type>(Head);
    }

    ForwardIterator<Type> end() const
    {
        return ForwardIterator<Type>(Tail->Next);
    }

    /// returns last element of a list
    ForwardIterator<Type> last() const
    {
        return ForwardIterator<Type>(Tail);
    }

    size_t GetSize() const { return Size; }

    void Clear()
    {
        while (Head)
        {
            ForwardNode<Type>* DeallocPtr = Head;
            Head = Head->Next;
            
            std::allocator_traits<NodeAllocType>::destroy(Allocator, DeallocPtr);
            std::allocator_traits<NodeAllocType>::deallocate(Allocator, DeallocPtr, 1);
        }

        Size = 0;
    }

private:

    ForwardNode<Type>* Head {nullptr};
    ForwardNode<Type>* Tail {nullptr};
   
    using NodeAllocType = typename std::allocator_traits<AllocType>::template rebind_alloc<ForwardNode<Type>>;
    NodeAllocType Allocator;

    size_t Size = 0;
};