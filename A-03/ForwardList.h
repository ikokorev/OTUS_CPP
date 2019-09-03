#pragma once

#include <memory>

template<typename Type>
class ForwardNode
{
public:

    ForwardNode() = default;
    ForwardNode(const Type InValue) : Value{InValue} {}

    const Type Value;
    ForwardNode<Type>* Next {nullptr};
};

template<typename Type>
class ForwardIterator
{

public:
    
    ForwardIterator() = default;
    ForwardIterator(ForwardNode<Type>* InitNode) : StartNode(InitNode) {}

    ForwardIterator& operator++()
    {
        if (StartNode)
        {
            StartNode = StartNode->Next;
        }

        return *this;
    }

    ForwardIterator& operator++(int)
    {
        ForwardIterator Old = *this;

        if (StartNode)
        {
            StartNode = StartNode->Next;
        }

        return Old;
    }

    Type operator*()
    {
        if (StartNode)
        {
            return StartNode->Value;
        }
        
        return 0;
    }

    bool operator==(const ForwardIterator<Type>& rhs) const
    {
        return StartNode == rhs.StartNode;
    }

    bool operator!=(const ForwardIterator<Type>& rhs) const
    {
        return StartNode != rhs.StartNode;
    }

private:

    ForwardNode<Type>* StartNode {nullptr};
};

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

    size_t Size;
};