#include "gtest/gtest.h"
#include "ForwardList.h"
#include "CustomAllocator/CustomAllocator.h"

TEST(ForwardListTests, TestList) 
{
    ForwardList<int> List;
    List.Push(1);

    EXPECT_EQ(*List.begin(), 1);
    EXPECT_EQ(*List.last(), 1);
    EXPECT_EQ(List.GetSize(), 1);

    List.Clear();

    // Tests below are needed to verify, that list is usable after clear
    List.Push(10);
    List.Push(20);

    EXPECT_EQ(*List.begin(), 10);
    EXPECT_EQ(*List.last(), 20);
    EXPECT_EQ(List.GetSize(), 2);
}

TEST(ForwardListTests, TestListWithCustomAlloc) 
{
    ForwardList<int, CustomAllocator<int>> List;
    for (int Value = 0; Value < 5; ++Value)
    {
        List.Push(Value);
    }

    int Value = 0;

    try
    {
        for (ForwardIterator<int> Iter = List.begin(); Iter != List.end(); ++Iter)
        {
            EXPECT_EQ(*Iter, Value++);
        }

        // Testing that list works with range-based foor loop
        Value = 0;
        for (auto Elem : List)
        {
            EXPECT_EQ(Elem, Value++);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }  
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}