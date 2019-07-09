#define BOOST_TEST_MODULE BTestProjectVersion

#include "ProjectVersion.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BTestProjectVersion)

BOOST_AUTO_TEST_CASE(IsProjectVersionCorrect)
{
    BOOST_CHECK(FProjectVerison::Major >= 0);
    BOOST_CHECK(FProjectVerison::Minor >= 0);
    BOOST_CHECK(FProjectVerison::Patch > 0);
}

}

