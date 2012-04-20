#ifndef ITEM_H
#define ITEM_H

#include <stdafx.h>
#include <Angel/Scripting/LuaModule.h>

#include <string>
#include <map>


class ItemState; //forward declaration

// This class holds data for interactable items in the game
class Item : public Actor
{

public:
	Item(std::string name);
	Item(Item &ref);

	void Start(); //this function is called after we add the item to the world so we bind events

	void Update(float dt);
	void Render();
	void PreDestroy();
	const std::string GetItemName();
	Item* CombineWith(Item* item);
	void ChangeState(std::string newState);
	void Use();

	void ReceiveMessage(Message *message);

protected:

private:
	void _LoadFromFile();

	std::string _itemName;
	ItemState* _currentState;
	std::map<std::string,ItemState*> _states;

};



#endif // ITEM_H
