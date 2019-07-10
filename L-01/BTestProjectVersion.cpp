#define BOOST_TEST_MODULE BTestProjectVersion

#include "ProjectVersionManager.cpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BTestProjectVersion)

FProjectVersion ProjectVersion = UProjectVersionManager::GetProjectVersion();

BOOST_AUTO_TEST_CASE(IsProjectVersionCorrect)
{
    BOOST_CHECK(ProjectVersion.Major >= 0);
    BOOST_CHECK(ProjectVersion.Minor >= 0);
    BOOST_CHECK(ProjectVersion.Patch > 0);
}

}