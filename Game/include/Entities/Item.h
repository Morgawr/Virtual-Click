#ifndef ITEM_H
#define ITEM_H

#include <stdafx.h>
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

protected:

private:
	void _LoadFromFile();

	std::string _itemName;

};



#endif // ITEM_H
