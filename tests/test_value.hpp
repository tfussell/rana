#pragma once

#include <cxxtest/TestSuite.h>

#include "value.hpp"

class test_value : public CxxTest::TestSuite
{
public:
    void test_default_type()
    {
        rana::value default_value;
        TS_ASSERT(!default_value.is_valid());
    }
    
    void test_special_values()
    {
        rana::value null = rana::value::null;
        rana::value object = rana::value::object;
        rana::value array = rana::value::array;
        TS_ASSERT(null.is_null());
        TS_ASSERT(object.is_object());
        TS_ASSERT(object.is_container());
        TS_ASSERT(array.is_array());
        TS_ASSERT(array.is_container());
    }
    
    void test_scalar_constructors()
    {
        rana::value boolean_true = true;
        TS_ASSERT(boolean_true.is_true());
        rana::value boolean_false = false;
        TS_ASSERT(boolean_false.is_false());
        rana::value number_int = 1;
        TS_ASSERT(number_int.is_number());
        rana::value number_double = 3.1415926535;
        TS_ASSERT(number_double.is_number());
        rana::value string = "abcdefg";
        TS_ASSERT(string.is_string());
    }
    
    void test_initialization_list_constructors()
    {
        rana::value a = {rana::value::null, true, false};
        TS_ASSERT(a.is_array());
        TS_ASSERT(a.size() == 3);
        TS_ASSERT(a[0] == rana::value::null);
        TS_ASSERT(a[1] == true);
        TS_ASSERT(a[2] == false);
        
        rana::value b = {std::make_pair("a", rana::value::null), {"b", true}, {"c", false}};
        TS_ASSERT(b.is_object());
        TS_ASSERT(b.size() == 3);
        TS_ASSERT(b["a"] == rana::value::null);
        TS_ASSERT(b["b"] == true);
        TS_ASSERT(b["c"] == false);
    }
    
    void test_assignment()
    {
        rana::value a = {rana::value::null, true, false};
        rana::value b = rana::value::null;
        a = b;
        TS_ASSERT(a.is_null());
        
        a = {1, 2, 3};
        TS_ASSERT(a.is_array());
        TS_ASSERT(a.size() == 3);
        TS_ASSERT(a[0] == 1);
        TS_ASSERT(a[1] == 2);
        TS_ASSERT(a[2] == 3);
    }
    
    void test_copy()
    {
        rana::value a = {rana::value::null, true, false};
        rana::value b = a.copy();
        
        TS_ASSERT(b.is_array());
        TS_ASSERT(b.size() == 3);
        TS_ASSERT(b[0] == rana::value::null);
        TS_ASSERT(b[1] == true);
        TS_ASSERT(b[2] == false);
    }
    
    void test_types()
    {
        TS_ASSERT(!rana::value::invalid().is_valid());
        TS_ASSERT(rana::value::null().is_null());
        TS_ASSERT(rana::value::object().is_object());
        TS_ASSERT(rana::value::object().is_container());
        TS_ASSERT(rana::value::array().is_array());
        TS_ASSERT(rana::value::array().is_container());
        TS_ASSERT(rana::value(1).is_number());
        TS_ASSERT(rana::value(1.123).is_number());
        const char *str = "abc";
        TS_ASSERT(rana::value(str).is_string());
        TS_ASSERT(rana::value(std::string("abc")).is_string());
        TS_ASSERT(rana::value(true).is_true());
        TS_ASSERT(rana::value(true).is_boolean());
        TS_ASSERT(rana::value(false).is_false());
        TS_ASSERT(rana::value(false).is_boolean());
    }
    
    void test_array()
    {
        rana::value array = rana::value::array;
        TS_ASSERT(array.is_array());
        TS_ASSERT(array.empty());
        TS_ASSERT(array.size() == 0);
        TS_ASSERT_THROWS_ANYTHING(array.at(0));
        array.append(1);
        TS_ASSERT(!array.empty());
        TS_ASSERT(array.size() == 1);
        TS_ASSERT_THROWS_NOTHING(array.at(0));
        TS_ASSERT(array[0] == 1);
        array.clear();
        TS_ASSERT(array.is_array());
        TS_ASSERT(array.empty());
        TS_ASSERT(array.size() == 0);
        TS_ASSERT_THROWS_ANYTHING(array.at(0));
        for(int i = 0; i < 1000; i++)
        {
            array.append(i);
        }
        std::size_t expected = 0;
        for(const auto &v : array.iter_array())
        {
            TS_ASSERT(v == expected++);
        }
        for(int i = 0; i < 1000; i++)
        {
            TS_ASSERT(array[i] == i);
        }
        for(int i = 0; i < 1000; i++)
        {
            TS_ASSERT(array.at(i) == i);
        }
    }
};
