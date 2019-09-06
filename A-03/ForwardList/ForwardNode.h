#pragma once

template<typename Type>
class ForwardNode
{
public:

    ForwardNode() = default;
    ForwardNode(const Type& InValue) : Value{InValue} {}

    Type Value;
    ForwardNode<Type>* Next {nullptr};
};