#include "luaFieldsTest.h"
#include "luaFields.h"

#include <string>

namespace gameBase{
	using namespace std;

	void LuaFieldsTest::setUp(){
	}

	void LuaFieldsTest::tearDown(){
	}

	void LuaFieldsTest::testTableToString(){
		string toStringRes = "table = {a = 1, b = 2.2, c = true, d = \"false\", e = {x = 20, y = {}}}";
		LuaTableField table("table");
		CPPUNIT_ASSERT(table.toString() == toStringRes);
	}
}
