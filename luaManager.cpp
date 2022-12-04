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

		int LuaManager::getInt(string varName){
				lua_getglobal(state, varName.c_str());
				int isNum;
				int var = (int)lua_tointegerx(state, -1, &isNum);
				lua_pop(state, 1);
				return var;
		}

		float LuaManager::getFloat(string varName){
				lua_getglobal(state, varName.c_str());
				int isNum;
				float var = (int)lua_tonumberx(state, -1, &isNum);
				lua_pop(state, 1);
				return var;
		}

		string LuaManager::getString(string varName){
			lua_getglobal(state, varName.c_str());
			string result = lua_tostring(state, -1);
			lua_pop(state, 1);

			return result;
		}

		void LuaManager::prepareTableForRetrieval(string table, vector<Index> &indices){
				lua_getglobal(state, table.c_str());

				if(!lua_istable(state, -1))
						cout << table << " is not a table\n";

				for(int i = 0; i < indices.size(); i++){
						if(indices[i].string)
								lua_pushstring(state, indices[i].index.c_str());
						else
								lua_pushnumber(state, atoi(indices[i].index.c_str()));

						lua_gettable(state, -2);
				}
		}

		int LuaManager::getIntFromTable(string table, vector<Index> indices){
				prepareTableForRetrieval(table, indices);

				int isNum;
				int result = lua_tointegerx(state, -1, &isNum);

				lua_pop(state, 1 + indices.size());

				return result;
		}

		float LuaManager::getFloatFromTable(string table, vector<Index> indices){
				prepareTableForRetrieval(table, indices);

				int isNum;
				float result = lua_tonumberx(state, -1, &isNum);

				lua_pop(state, 1 + indices.size());

				return result;
		}

		bool LuaManager::getBoolFromTable(string table, vector<Index> indices){
				prepareTableForRetrieval(table, indices);
				bool result = lua_toboolean(state, -1);
				lua_pop(state, 1 + indices.size());

				return result;
		}

		string LuaManager::getStringFromTable(string table, vector<Index> indices){
				prepareTableForRetrieval(table, indices);
				string result = lua_tostring(state, -1);
				lua_pop(state, 1 + indices.size());

				return result;
		}
}
