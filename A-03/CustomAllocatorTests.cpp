#include "gtest/gtest.h"
#include <map>
#include "CustomAllocator.h"

TEST(CustomAllocatorTests, TestAllocatorWithMap) 
{
    std::map<int, int, std::less<int>, CustomAllocator<int, 1>> CustomAllocMap;
    CustomAllocMap.emplace(1, 1);

    EXPECT_EQ(CustomAllocMap.at(1), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}