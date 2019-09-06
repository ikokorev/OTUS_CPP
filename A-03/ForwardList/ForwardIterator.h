#pragma once

#include "ForwardNode.h"

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

    Type& operator*()
    {
        if (StartNode)
        {
            return StartNode->Value;
        }
        else
        {
            throw std::logic_error("Iterator start node is nullptr, you can't validly obtain value from iterator.");
        } 
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