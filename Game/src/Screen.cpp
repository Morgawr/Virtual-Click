#include <Screen.h>

Screen::Screen(bool isPopup)
{
	this->_isPopup = isPopup;
}

void Screen::Start()
{
	//nothing to be done here yet
}

void Screen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();

	while(_objects.end() != it)
	{
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if(pa != NULL && pa->GetBody() != NULL)
		{
			pa->GetBody()->SetUserData(NULL);
			theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
			pa->ResetBody();
		}

		(*it)->Destroy();
		it++;
	}
	_objects.clear();
	this->Destroy();
}

void Screen::Update(float dt)
{
	//nothing here yet, might want to add a stopwatch/counter or something for achievements??
}

void Screen::Render()
{
	//nothing here either, might be useful for debugging purposes but who knows...
}

void Screen::SoundEnded(AngelSoundHandle sound)
{
	//detect when sound ended
}

void Screen::ReceiveMessage(Message* message)
{
	//in case we need global message handling for all screens
}
