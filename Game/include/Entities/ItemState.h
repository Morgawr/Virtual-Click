#ifndef ITEMSTATE_H
#define ITEMSTATE_H

#include <LuaManager.h>

#include <map>

class Item; //forward declaration

//This class keeps track of a state of an item. A state is the set of interactions
//an object can do, where it resides, what is its sprite etc etc
class ItemState : public MessageListener
{
public:
	ItemState(std::string name, lua_State *L, Item* parent);
	void Activate();
	void Stop();
	void Use();

	void ReceiveMessage(Message *m);
protected:
private:

	Item* _parent;
	std::string _name;
	std::string _spriteWorld;
	std::string _spriteInventory;
	std::string _messageOnSuccess;
	std::string _messageOnFailure;
	std::string _messageOnExamine;
	std::string _workOnItem;
	std::string _combinedItem;
	std::string _generatedEvent;
	std::map<std::string, std::string> _eventStateMap; //map of event->state transitions
	bool _isPickUpAble;
};

#endif // ITEMSTATE_H
