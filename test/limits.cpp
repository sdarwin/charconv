// Copyright 2023 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/charconv/limits.hpp>
#include <boost/charconv/to_chars.hpp>
#include <boost/charconv/from_chars.hpp>
#include <boost/core/lightweight_test.hpp>
#include <limits>

template<typename T> void test_integral( T value )
{
    // no base
    {
        char buffer[ boost::charconv::limits<T>::max_chars10 ];
        auto r = boost::charconv::to_chars( buffer, buffer + sizeof( buffer ), value );
        BOOST_TEST_EQ( r.ec, 0 );

        T v2 = 0;
        auto r2 = boost::charconv::from_chars( buffer, r.ptr, v2 );

        BOOST_TEST_EQ( r2.ec, 0 ) && BOOST_TEST_EQ( v2, value );
    }

    // base 10
    {
        char buffer[ boost::charconv::limits<T>::max_chars10 ];
        auto r = boost::charconv::to_chars( buffer, buffer + sizeof( buffer ), value, 10 );
        BOOST_TEST_EQ( r.ec, 0 );

        T v2 = 0;
        auto r2 = boost::charconv::from_chars( buffer, r.ptr, v2, 10 );

        BOOST_TEST_EQ( r2.ec, 0 ) && BOOST_TEST_EQ( v2, value );
    }

    // any base
    for( int base = 2; base <= 36; ++base )
    {
        char buffer[ boost::charconv::limits<T>::max_chars ];
        auto r = boost::charconv::to_chars( buffer, buffer + sizeof( buffer ), value, base );
        BOOST_TEST_EQ( r.ec, 0 );

        T v2 = 0;
        auto r2 = boost::charconv::from_chars( buffer, r.ptr, v2, base );

        BOOST_TEST_EQ( r2.ec, 0 ) && BOOST_TEST_EQ( v2, value );
    }
}

template<typename T> void test_integral()
{
    BOOST_TEST_GE( boost::charconv::limits<T>::max_chars10, std::numeric_limits<T>::digits10 );
    BOOST_TEST_GE( boost::charconv::limits<T>::max_chars, std::numeric_limits<T>::digits );

    test_integral( std::numeric_limits<T>::min() );
    test_integral( std::numeric_limits<T>::max() );
}

template<typename T> void test_floating_point( T value )
{
    // no base, max_chars10
    {
        char buffer[ boost::charconv::limits<T>::max_chars10 ];
        auto r = boost::charconv::to_chars( buffer, buffer + sizeof( buffer ), value );
        BOOST_TEST_EQ( r.ec, 0 );

        T v2 = 0;
        auto r2 = boost::charconv::from_chars( buffer, r.ptr, v2 );

        BOOST_TEST_EQ( r2.ec, 0 ) && BOOST_TEST_EQ( v2, value );
    }

    // no base, max_chars
    {
        char buffer[ boost::charconv::limits<T>::max_chars ];
        auto r = boost::charconv::to_chars( buffer, buffer + sizeof( buffer ), value );
        BOOST_TEST_EQ( r.ec, 0 );

        T v2 = 0;
        auto r2 = boost::charconv::from_chars( buffer, r.ptr, v2 );

        BOOST_TEST_EQ( r2.ec, 0 ) && BOOST_TEST_EQ( v2, value );
    }
}

template<typename T> void test_floating_point()
{
    BOOST_TEST_GE( boost::charconv::limits<T>::max_chars10, std::numeric_limits<T>::max_digits10 );
    BOOST_TEST_GE( boost::charconv::limits<T>::max_chars, std::numeric_limits<T>::max_digits10 );

    test_floating_point( std::numeric_limits<T>::min() );
    test_floating_point( -std::numeric_limits<T>::min() );
    test_floating_point( std::numeric_limits<T>::max() );
    test_floating_point( -std::numeric_limits<T>::max() );
}

int main()
{
    test_integral<char>();
    test_integral<signed char>();
    test_integral<unsigned char>();
    test_integral<short>();
    test_integral<unsigned short>();
    test_integral<int>();
    test_integral<unsigned>();
    test_integral<long>();
    test_integral<unsigned long>();
    test_integral<long long>();
    test_integral<unsigned long long>();

    test_floating_point<float>();
    test_floating_point<double>();

    return boost::report_errors();
}
