#ifndef SOL_UTIL_H
#define SOL_UTIL_H
#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace gameBase{
	sol::state_view generateView();
}

#endif
