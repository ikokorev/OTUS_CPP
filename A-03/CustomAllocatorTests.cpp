#include "gtest/gtest.h"
#include <map>
#include "CustomAllocator.h"
#include "ForwardList.h"

TEST(CustomAllocatorTests, TestAllocWithMap) 
{
    std::map<int, int, std::less<int>, CustomAllocator<int, 1>> Map;
    Map.emplace(1, 1);

    EXPECT_EQ(Map.at(1), 1);
}

TEST(CustomAllocatorTests, TestAllocWithForwardList) 
{
    ForwardList<int, CustomAllocator<int, 1>> List;
    List.Push(1);

    EXPECT_EQ(*List.begin(), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}