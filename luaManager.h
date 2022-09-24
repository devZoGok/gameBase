#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include <string>
#include <vector>

namespace gameBase{
		class LuaManager{
				public:
						struct Index{
								std::string index;
							 	bool string;

								Index(std::string index){
										this->index = index;
										this->string = true;
								}

								Index(int index){
										this->index = std::to_string(index);
										this->string = false;
								}

								Index(float index){
										this->index = std::to_string(index);
										this->string = false;
								}
						};

						static LuaManager* getSingleton();
						inline lua_State* getState(){return state;}
						void buildScript(std::vector<std::string>);
						int getInt(std::string);
						int getIntFromTable(std::string, std::vector<Index>);
						bool getBoolFromTable(std::string, std::vector<Index>);
						float getFloatFromTable(std::string, std::vector<Index>);
						std::string getStringFromTable(std::string, std::vector<Index>);
						std::string getString(std::string);
				private:
						LuaManager();
						void prepareTableForRetrieval(std::string, std::vector<Index>&);

						lua_State *state = nullptr;
		};

		typedef LuaManager::Index Index;
}

#endif
