#include "luaManager.h"

#include <iostream>

using namespace std;

namespace gameBase{
	static LuaManager *luaManager = nullptr;

	LuaManager* LuaManager::getSingleton(){
		if(!luaManager) luaManager = new LuaManager();

		return luaManager;
	}

	LuaManager::LuaManager(){
		state = luaL_newstate();
		luaL_openlibs(state);
	}

	void LuaManager::buildScript(vector<string> files){
		string script = "";

		for(string f : files)
			script += "dofile(\"" + f + "\");";
 
		executeCode(script, "Error building script(s)\n");
	}

	void LuaManager::executeCode(string code, string errMsg){
		if(luaL_dostring(state, code.c_str()) && lua_pcall(state, 0, 0, 0))
			cout << errMsg;
	}

	void LuaManager::prepareTableForRetrieval(vector<Index> &indices){
		lua_getglobal(state, indices[0].index.c_str());

		for(int i = 1; i < indices.size(); i++){
			if(!lua_istable(state, -1))
				cout << indices[i].index << " is not in the " << indices[0].index << " table\n";

			if(indices[i].string)
				lua_pushstring(state, indices[i].index.c_str());
			else
				lua_pushnumber(state, atoi(indices[i].index.c_str()));

			lua_gettable(state, -2);
		}
	}

	int LuaManager::getInt(vector<Index> indices){
		prepareTableForRetrieval(indices);

		int isNum;
		int result = lua_tointegerx(state, -1, &isNum);

		lua_pop(state, indices.size());

		return result;
	}

	float LuaManager::getFloat(vector<Index> indices){
		prepareTableForRetrieval(indices);

		int isNum;
		float result = lua_tonumberx(state, -1, &isNum);

		lua_pop(state, indices.size());

		return result;
	}

	bool LuaManager::getBool(vector<Index> indices){
		prepareTableForRetrieval(indices);

		bool result = lua_toboolean(state, -1);
		lua_pop(state, indices.size());

		return result;
	}

	string LuaManager::getString(vector<Index> indices){
		prepareTableForRetrieval(indices);

		string result = lua_tostring(state, -1);
		lua_pop(state, indices.size());

		return result;
	}
}
