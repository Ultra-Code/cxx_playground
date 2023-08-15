#define BOOST_TEST_MODULE Concurrency Test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(First)
{
    auto i = int(1);
    BOOST_TEST(i == 2);
}

