#include "solUtil.h"

namespace gameBase{
	static lua_State *state = nullptr;

	sol::state_view generateView(){
		if(!state){
			state = luaL_newstate();
			luaL_openlibs(state);
		}

		sol::state_view view(state);
		return view;
	}
}

