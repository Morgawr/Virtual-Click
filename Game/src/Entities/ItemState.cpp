#include <Item.h>
#include <ItemState.h>

#include <Player.h>
#include <PathNames.h>

ItemState::ItemState(std::string name, lua_State *L, Item *parent) :
	_parent(parent),
	_name(name)
{
	_spriteWorld = LuaManager::FromString(L,(_name+"_spriteWorld").c_str());
	_spriteInventory = LuaManager::FromString(L,(_name+"_spriteInventory").c_str());
	_messageOnSuccess = LuaManager::FromString(L,(_name+"_messageOnSuccess").c_str());
	_messageOnFailure = LuaManager::FromString(L,(_name+"_messageOnFailure").c_str());
	_messageOnExamine = LuaManager::FromString(L,(_name+"_messageOnExamine").c_str());
	_workOnItem = LuaManager::FromString(L,(_name+"_workOnItem").c_str());
	_combinedItem = LuaManager::FromString(L,(_name+"_combinedItem").c_str());
	_generatedEvent = LuaManager::FromString(L,(_name+"_generatedEvent").c_str());
	std::vector<std::string> events = LuaManager::FromStringList(L,(_name+"_events").c_str());
	for(std::vector<std::string>::iterator it = events.begin(); it != events.end(); it++)
	{
		_eventStateMap[(*it)] = LuaManager::FromString(L,(_name+"_"+(*it)).c_str());
	}
	_isPickUpAble = LuaManager::FromBoolean(L,(_name+"_pickUpAble").c_str());
}

void ItemState::Activate()
{
	for(std::map<std::string, std::string>::iterator it = _eventStateMap.begin(); it != _eventStateMap.end(); it++)
	{
		theSwitchboard.SubscribeTo(this,(*it).first);
	}

	std::vector<Item*> inv;
	thePlayer.GetInventory(inv);
	std::vector<Item*>::iterator it = std::find(inv.begin(),inv.end(),_parent);
	if(it == inv.end()) //not in inventory
	{
		_parent->SetSprite(PATH_IMAGE+_spriteWorld);
	}
	else
	{
		_parent->SetSprite(PATH_IMAGE+_spriteInventory);
	}

	std::vector<std::string> ev;
	thePlayer.GetEvents(ev);
	for(std::vector<std::string>::iterator it = ev.begin(); it != ev.end(); it++)
	{
		std::map<std::string, std::string>::iterator found = _eventStateMap.find(*it);
		if(found != _eventStateMap.end())
		{
			_parent->ChangeState(_eventStateMap[*it]);
			return;
		}
	}
}


void ItemState::Stop()
{
	for(std::map<std::string, std::string>::iterator it = _eventStateMap.begin(); it != _eventStateMap.end(); it++)
	{
		theSwitchboard.UnsubscribeFrom(this,(*it).first);
	}
}


void ItemState::ReceiveMessage(Message *m)
{
	std::map<std::string, std::string>::iterator find = _eventStateMap.find(m->GetMessageName());
	if(find != _eventStateMap.end())
	{
		_parent->ChangeState(_eventStateMap[m->GetMessageName()]);
		return;
	}
}

void ItemState::Use()
{
	theSwitchboard.Broadcast(new Message(_generatedEvent,this));
}
