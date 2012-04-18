#ifndef PLAYER_H
#define PLAYER_H

#include <stdafx.h>
#include <vector>
#include <string>

#include <Item.h>

#define thePlayer Player::GetInstance();

//This class holds all the data for our player. Inventory and all that stuff
//it communicates through messaging and normal functions, it delegates all the drawing to the screen
class Player : public MessageListener
{
public:

	static Player &GetInstance();

	void AddItem(std::string name); //adds an item to the player inventory, the name is the script name .lua
	void RemoveItem(std::string name);
	Item* GetItem(std::string name);
	bool HasItem(std::string name); //checks if the player has said item in the inventory
	const std::vector<Item*> GetInventory();

	void ReceiveMessage(Message *message);

protected:
	Player();
	static Player *s_Player;

private:
	std::vector<Item*> _inventory;
};

#endif // PLAYER_H
