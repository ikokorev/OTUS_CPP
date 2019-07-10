#include "ProjectVersion.h"
#include "gtest/gtest.h"

TEST(TestProjectVersion, IsProjectVersionCorrect) {
  EXPECT_GE(FProjectVersion::Major, 0);
  EXPECT_GE(FProjectVersion::Minor, 0);
  EXPECT_GT(FProjectVersion::Patch, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}