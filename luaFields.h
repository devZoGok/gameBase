#ifndef LUA_FIELDS_H
#define LUA_FIELDS_H

#include <string>
#include <vector>

namespace gameBase{
	class AbstractLuaField{
		public:
			std::string name = "";
		protected:
			AbstractLuaField(std::string n) : name(n){}
			virtual std::string toString(){return "";}
	};

	class LuaTableField : public AbstractLuaField{
		public:
			LuaTableField(std::string name) : AbstractLuaField(name){}
			std::string toString();
			AbstractLuaField operator[](std::string);
		private:
			std::vector<AbstractLuaField> fields;
	};
}

#endif
