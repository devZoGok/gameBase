#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "luaFieldsTest.h"

using namespace CppUnit;
using namespace gameBase;

int main(){
	TextUi::TestRunner runner;
	runner.addTest(LuaFieldsTest::suite());
	runner.run();
	return 0;
}
