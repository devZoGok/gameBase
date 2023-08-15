#ifndef LUA_FIELDS_TEST_H
#define LUA_FIELDS_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace gameBase{
	class LuaFieldsTest : public CppUnit::TestFixture{
		CPPUNIT_TEST_SUITE(LuaFieldsTest);
		CPPUNIT_TEST(testTableToString);
		CPPUNIT_TEST_SUITE_END();

		public:
			LuaFieldsTest(){}
			void setUp();
			void tearDown();
		private:
			void testTableToString();
	};
}

#endif
