#define BOOST_TEST_MODULE TestMain
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../bin/version.h"
#include "sparse_matrix.h"

BOOST_AUTO_TEST_SUITE( test_suite )

BOOST_AUTO_TEST_CASE( test_version )
{
    BOOST_CHECK_GT(build_version(), 0);
}

BOOST_AUTO_TEST_CASE( test_1d )
{
    sparse_matrix<1, uint8_t, 0x00> sm;

    sm[5] = 0x01;
    sm[3] = 0x01;
    sm[1] = 0x01;

    BOOST_CHECK_EQUAL(sm.size(), 3);
    BOOST_CHECK_EQUAL(sm[0], 0x00);
    BOOST_CHECK_EQUAL(sm[1], 0x01);
    BOOST_CHECK_EQUAL(sm[2], 0x00);
    BOOST_CHECK_EQUAL(sm[3], 0x01);
    BOOST_CHECK_EQUAL(sm[4], 0x00);
    BOOST_CHECK_EQUAL(sm[5], 0x01);
    BOOST_CHECK_EQUAL(sm[6], 0x00);

    auto e = sm.begin();
    BOOST_CHECK(e->first == std::make_tuple(1));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(3));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(5));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e == sm.end());

}

BOOST_AUTO_TEST_CASE( test_2d )
{
    sparse_matrix<2, uint8_t, 0x00> sm;

    sm[5][1] = 0x01;
    sm[3][3] = 0x01;
    sm[1][5] = 0x01;

    BOOST_CHECK_EQUAL(sm.size(), 3);
    BOOST_CHECK_EQUAL(sm[0][0], 0x00);
    BOOST_CHECK_EQUAL(sm[1][5], 0x01);
    BOOST_CHECK_EQUAL(sm[2][2], 0x00);
    BOOST_CHECK_EQUAL(sm[3][3], 0x01);
    BOOST_CHECK_EQUAL(sm[4][4], 0x00);
    BOOST_CHECK_EQUAL(sm[5][1], 0x01);
    BOOST_CHECK_EQUAL(sm[6][6], 0x00);

    auto e = sm.begin();
    BOOST_CHECK(e->first == std::make_tuple(1, 5));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(3, 3));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(5, 1));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e == sm.end());
}

BOOST_AUTO_TEST_CASE( test_3d )
{
    sparse_matrix<3, uint8_t, 0x00> sm;

    sm[5][0][1] = 0x01;
    sm[3][3][3] = 0x01;
    sm[1][0][5] = 0x01;

    BOOST_CHECK_EQUAL(sm.size(), 3);
    BOOST_CHECK_EQUAL(sm[0][0][0], 0x00);
    BOOST_CHECK_EQUAL(sm[1][0][5], 0x01);
    BOOST_CHECK_EQUAL(sm[0][2][2], 0x00);
    BOOST_CHECK_EQUAL(sm[3][3][3], 0x01);
    BOOST_CHECK_EQUAL(sm[4][0][4], 0x00);
    BOOST_CHECK_EQUAL(sm[5][0][1], 0x01);
    BOOST_CHECK_EQUAL(sm[6][6][0], 0x00);

    auto e = sm.begin();

    BOOST_CHECK(e->first == std::make_tuple(1, 0, 5));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(3, 3, 3));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e->first == std::make_tuple(5, 0,1));
    BOOST_CHECK_EQUAL(e->second, 0x01);
    ++e;
    BOOST_CHECK(e == sm.end());
}

BOOST_AUTO_TEST_CASE( test_set_default )
{
    sparse_matrix<3, uint8_t, 0x00> sm;

    sm[1][2][3] = 0x01;
    sm[1][2][2] = 0x01;
    sm[1][1][1] = 0x01;

    sm[2][3][4] = 0x00;
    sm[2][3][3] = 0x00;
    sm[2][2][2] = 0x00;

    BOOST_CHECK_EQUAL(sm.size(), 3);

    sm[1][2][3] = 0x00;
    sm[1][2][2] = 0x00;
    sm[1][1][1] = 0x00;

    BOOST_CHECK_EQUAL(sm.size(), 0);

    BOOST_CHECK(sm.begin() == sm.end());
}

BOOST_AUTO_TEST_SUITE_END()

