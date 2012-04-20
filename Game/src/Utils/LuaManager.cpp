#include <LuaManager.h>
#include <assert.h>

std::string LuaManager::FromString(lua_State *L, const std::string luaName)
{
	lua_getglobal(L,luaName.c_str());
	assert(lua_isstring(L,-1));
	std::string data = lua_tostring(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L,luaName.c_str());
	return data;
}

bool LuaManager::FromBoolean(lua_State *L, const std::string luaName)
{
	lua_getglobal(L,luaName.c_str());
	assert(lua_isboolean(L,-1));
	bool data = lua_toboolean(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L,luaName.c_str());
	return data;
}

float LuaManager::FromFloat(lua_State *L, const std::string luaName)
{
	lua_getglobal(L,luaName.c_str());
	assert(lua_isnumber(L,-1));
	float data = lua_tonumber(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L,luaName.c_str());
	return data;
}

std::vector<std::string> LuaManager::FromStringList(lua_State *L, const std::string luaName)
{
	lua_getglobal(L,luaName.c_str());
	size_t sz = lua_objlen(L, -1);
	std::vector<std::string> strings;
	for (size_t i = 1; i <= sz; i++) {
	   lua_rawgeti(L, -1, i);
	   strings.push_back(lua_tostring(L, -1));
	   lua_pop(L, 1);
	}

	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L, luaName.c_str());

	return strings;
}
