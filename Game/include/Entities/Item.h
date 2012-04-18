#ifndef ITEM_H
#define ITEM_H

#include <stdafx.h>
#include <Angel/Scripting/LuaModule.h>
#include <string>


// This class holds data for interactable items in the game
class Item : public Actor
{

public:
	Item(std::string name);
	Item(Item &ref);

	void Update(float dt);
	void Render();
	void PreDestroy();
	const std::string GetItemName();
	Item* CombineWith(Item* item);

protected:

private:
	void _LoadFromFile();
	void _LuaFromString(lua_State* L, const std::string luaName, std::string &property);

	std::string _itemName;
	std::string _spriteWorld;
	std::string _spriteInventory;
	std::string _messageOnSuccess;
	std::string _messageOnFailure;
	std::string _workOnItem;
	std::string _combinedItem;

};



#endif // ITEM_H
