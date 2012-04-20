#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <stdafx.h>
#include <Angel/Scripting/LuaModule.h>
#include <vector>

class LuaManager
{
public:
	static std::string FromString(lua_State* L, const std::string luaName);
	static bool FromBoolean(lua_State* L, const std::string luaName);
	static float FromFloat(lua_State* L, const std::string luaName);
	static std::vector<std::string> FromStringList(lua_State* L, const std::string luaName);

};

#endif // LUAMANAGER_H
