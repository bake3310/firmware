/*
* Copyright 2015 BrewPi/Elco Jacobs.
*
* This file is part of BrewPi.
*
* BrewPi is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* BrewPi is distributed in the hope that it will be useful,
+
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <boost/test/unit_test.hpp>

#include "runner.h"

#include <iostream>
#include <string>

#include <msgpack.hpp>
#include <stdio.h>

#include <boost/fusion/adapted/struct/define_struct_inline.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>


class Demo {
public:
    Demo(){}
    ~Demo(){}

    BOOST_FUSION_DEFINE_STRUCT_INLINE(
        settings,
        (int, s1)
        (char, s2)
    )

    BOOST_FUSION_DEFINE_STRUCT_INLINE(
        variables,
        (int, v1)
        (char, v2)
    )
};

BOOST_FUSION_DEFINE_STRUCT_INLINE(
    TestStruct,
    (int, v1)
    (char, v2)
    (int32_t, v3)
)

std::string as_hex(std::string str_in) {
    std::ostringstream out;
    for(char& c : str_in)
    {
       out << std::hex << std::setfill('0') << std::setw(2) << (int)(unsigned char) c;
       out << ' ';
    }
    return out.str();
}


BOOST_AUTO_TEST_SUITE(msgpack_test)

BOOST_AUTO_TEST_CASE(dummy) {
    std::stringstream ss;
    TestStruct val1;
    val1.v1 = 42;
    val1.v2 = 'a';
    val1.v3 = 1235;

    msgpack::pack(ss, val1);
    msgpack::object_handle oh = msgpack::unpack(ss.str().data(), ss.str().size());



    BOOST_TEST_MESSAGE("Packed message: " << as_hex(ss.str()));
    BOOST_TEST_MESSAGE("Packed size: " << ss.str().size());

    TestStruct val2 = oh.get().as<TestStruct>();
    BOOST_CHECK_EQUAL(val1.v1, val2.v1);
    BOOST_CHECK_EQUAL(val1.v2, val2.v2);
    BOOST_CHECK_EQUAL(val1.v3, val2.v3);
}

BOOST_AUTO_TEST_SUITE_END()

