#include "gtest/gtest.h"
#include "ReservingAllocator.h"
#include "ForwardList/ForwardList.h"

TEST(ReservingAllocatorTests, TestAllocByItself) 
{
    ReservingAllocator<int, 1> IntAllocator;
    int* IntPtr = IntAllocator.allocate();
    IntAllocator.construct(IntPtr, 15);

    EXPECT_EQ(*IntPtr, 15);

    IntAllocator.destroy(IntPtr);
    IntAllocator.deallocate(IntPtr, 1);

    // second verification exists to check if allocator can validly allocate again, after deallocation
    IntPtr = IntAllocator.allocate();
    IntAllocator.construct(IntPtr, 10);

    EXPECT_EQ(*IntPtr, 10);
}

TEST(ReservingAllocatorTests, TestAllocExpanding) 
{
    ReservingAllocator<int, 1> IntAllocator;
    
    int* FirstIntPtr = IntAllocator.allocate();
    IntAllocator.construct(FirstIntPtr, 1);
    int* SecondIntPtr = IntAllocator.allocate();
    IntAllocator.construct(SecondIntPtr, 2);
    

    EXPECT_EQ(*FirstIntPtr, 1);
    EXPECT_EQ(*SecondIntPtr, 2);

    IntAllocator.destroy(FirstIntPtr);
    IntAllocator.deallocate(FirstIntPtr, 1);
    IntAllocator.destroy(SecondIntPtr);
    IntAllocator.deallocate(SecondIntPtr, 1);

    // second verification exists to check if expanded allocator can validly allocate again, after deallocation
    FirstIntPtr = IntAllocator.allocate();
    IntAllocator.construct(FirstIntPtr, 10);
    SecondIntPtr = IntAllocator.allocate();
    IntAllocator.construct(SecondIntPtr, 20);

    EXPECT_EQ(*FirstIntPtr, 10);
    EXPECT_EQ(*SecondIntPtr, 20);
}

TEST(ReservingAllocatorTests, TestAllocWithMap) 
{
    std::map<int, int, std::less<int>, ReservingAllocator<std::pair<const int, int>, 5>> Map;

    for (int Value = 0; Value < 5; ++Value)
    {
        Map.emplace(Value, Value);
    }

    int Value = 0;
    for (auto Pair : Map)
    {
        EXPECT_EQ(Pair.second, Value++);
    }
}

TEST(ReservingAllocatorTests, TestAllocExpandingWithMap) 
{
    std::map<int, int, std::less<int>, ReservingAllocator<std::pair<const int, int>, 1>> Map;

    for (int Value = 0; Value < 5; ++Value)
    {
        Map.emplace(Value, Value);
    }

    int Value = 0;
    for (auto Pair : Map)
    {
        EXPECT_EQ(Pair.second, Value++);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}