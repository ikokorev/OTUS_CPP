#include "gtest/gtest.h"
#include "ProjectVersion.h"

TEST(TestProjectVersion, IsProjectVersionCorrect) {
  EXPECT_GE(FProjectVerison::Major, 0);
  EXPECT_GE(FProjectVerison::Minor, 0);
  EXPECT_GT(FProjectVerison::Patch, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}