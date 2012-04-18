#include <Item.h>
#include <PathNames.h>
#include <assert.h>

Item::Item(std::string name)
{
	this->_itemName = name;
	_LoadFromFile();
}

void Item::_LoadFromFile()
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	std::string filename = PATH_BASE_ITEM + _itemName + ".lua";
	assert(luaL_dofile(L,filename.c_str()));
	_LuaFromString(L,"spriteWorld",_spriteWorld);
	_LuaFromString(L,"spriteInventory",_spriteInventory);
	_LuaFromString(L,"messageOnSuccess",_messageOnSuccess);
	_LuaFromString(L,"messageOnFailure",_messageOnFailure);
	_LuaFromString(L,"workOnItem",_workOnItem);
	_LuaFromString(L,"combinedItem",_combinedItem);
}

void Item::_LuaFromString(lua_State* L, const std::string luaName, std::string &property)
{
	lua_getglobal(L,luaName.c_str());
	assert(lua_isstring(L,-1));
	property = lua_tostring(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
}

void Item::Update(float dt)
{
	Actor::Update(dt);
}

void Item::Render()
{
	Actor::Render();
}

void Item::PreDestroy()
{
	Actor::PreDestroy();
}

Item* Item::CombineWith(Item *item)
{

}

const std::string Item::GetItemName()
{
	if(!_itemName.empty())
		return _itemName;
	else
		return GetName();
}
