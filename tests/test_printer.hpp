#pragma once

#include <cxxtest/TestSuite.h>

#include "parser.hpp"

class test_printer : public CxxTest::TestSuite
{
public:
    void test_to_file()
    {
	auto temp_filename = make_temp_filename();
	rana::value v = {rana::null(), false, true, -3.14, "str"};
	rana::printer().to_file(v, temp_filename);
	auto contents = read_file_contents(temp_filename);
	static const auto expected = "{null,false,true,-3.14,\"str\"}";
	TS_ASSERT(contents == expected);
	std::remove(temp_filename);
    }

    void test_to_string()
    {

    }

    void test_to_stream()
    {

    }
};
