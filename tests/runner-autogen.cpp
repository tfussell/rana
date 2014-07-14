/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_test_value_init = false;
#include "/Users/thomas/Development/rana/tests/test_value.hpp"

static test_value suite_test_value;

static CxxTest::List Tests_test_value = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_test_value( "../../tests/test_value.hpp", 7, "test_value", suite_test_value, Tests_test_value );

static class TestDescription_suite_test_value_test_default_type : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_default_type() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 10, "test_default_type" ) {}
 void runTest() { suite_test_value.test_default_type(); }
} testDescription_suite_test_value_test_default_type;

static class TestDescription_suite_test_value_test_special_values : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_special_values() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 16, "test_special_values" ) {}
 void runTest() { suite_test_value.test_special_values(); }
} testDescription_suite_test_value_test_special_values;

static class TestDescription_suite_test_value_test_scalar_constructors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_scalar_constructors() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 28, "test_scalar_constructors" ) {}
 void runTest() { suite_test_value.test_scalar_constructors(); }
} testDescription_suite_test_value_test_scalar_constructors;

static class TestDescription_suite_test_value_test_initialization_list_constructors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_initialization_list_constructors() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 42, "test_initialization_list_constructors" ) {}
 void runTest() { suite_test_value.test_initialization_list_constructors(); }
} testDescription_suite_test_value_test_initialization_list_constructors;

static class TestDescription_suite_test_value_test_assignment : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_assignment() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 59, "test_assignment" ) {}
 void runTest() { suite_test_value.test_assignment(); }
} testDescription_suite_test_value_test_assignment;

static class TestDescription_suite_test_value_test_copy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_copy() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 74, "test_copy" ) {}
 void runTest() { suite_test_value.test_copy(); }
} testDescription_suite_test_value_test_copy;

static class TestDescription_suite_test_value_test_types : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_types() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 86, "test_types" ) {}
 void runTest() { suite_test_value.test_types(); }
} testDescription_suite_test_value_test_types;

static class TestDescription_suite_test_value_test_array : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_value_test_array() : CxxTest::RealTestDescription( Tests_test_value, suiteDescription_test_value, 105, "test_array" ) {}
 void runTest() { suite_test_value.test_array(); }
} testDescription_suite_test_value_test_array;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
