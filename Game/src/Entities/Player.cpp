#include <Player.h>

Player* Player::s_Player = NULL;

Player& Player::GetInstance()
{
	if (s_Player == NULL)
	{
		s_Player = new Player();
	}
	return *s_Player;
}

Player::Player()
{
}

void Player::AddItem(std::string name)
{
	Item* item = new Item(name);
	_inventory.push_back(item);
}

void Player::RemoveItem(std::string name)
{
	for(std::vector<Item*>::iterator it = _inventory.begin(); it != _inventory.end(); it++)
	{
		if((*it)->GetItemName() == name)
		{
			_inventory.erase(it);
			return;
		}
	}
}


const std::vector<Item*> Player::GetInventory()
{
	return _inventory;
}

void Player::ReceiveMessage(Message *message)
{

}
