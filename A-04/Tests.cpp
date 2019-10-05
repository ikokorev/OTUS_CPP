#include "gtest/gtest.h"
#include "IPConversionFunctions.h"

TEST(PrintIPTests, IntegerTest) 
{
    EXPECT_EQ(ConvertIPToString(short(0)), std::string("0.0"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}