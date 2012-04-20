#include <ItemState.h>
#include <Item.h>
#include <string>
#include <PathNames.h>
#include <LuaManager.h>


Item::Item(std::string name)
{
	this->_itemName = name;
	_LoadFromFile();
	_currentState = NULL;
}

void Item::_LoadFromFile()
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	std::string filename = PATH_ITEM + _itemName + ".lua";
	assert(luaL_dofile(L,filename.c_str()) == 0);
	std::vector<std::string> statelist = LuaManager::FromStringList(L,"states");
	_states["default"] = new ItemState("default",L,this);
	for(std::vector<std::string>::iterator it = statelist.begin(); it != statelist.end(); it++)
	{
		_states[*it] = new ItemState(*it,L,this);
	}
}

void Item::Start()
{
	if(_currentState == NULL)
	{
		_currentState = _states["default"];
		_currentState->Activate();
	}
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
	for(std::map<std::string,ItemState*>::iterator it = _states.begin(); it != _states.end(); it++)
	{
		delete (*it).second;
	}

	_states.clear();

	Actor::PreDestroy();
}

Item* Item::CombineWith(Item *item)
{

}

void Item::ReceiveMessage(Message *message)
{

}

const std::string Item::GetItemName()
{
	if(!_itemName.empty())
		return _itemName;
	else
		return GetName();
}

void Item::ChangeState(std::string newState)
{
	_currentState->Stop();
	_currentState = _states[newState];
	_currentState->Activate();
}

void Item::Use()
{
	_currentState->Use();
}
