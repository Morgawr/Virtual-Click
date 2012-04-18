#include <Item.h>
#include <Angel/Scripting/LuaModule.h>
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

const std::string Item::GetItemName()
{
	if(!_itemName.empty())
		return _itemName;
	else
		return GetName();
}
