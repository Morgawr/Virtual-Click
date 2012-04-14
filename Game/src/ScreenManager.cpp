#include <ScreenManager.h>

ScreenManager* ScreenManager::s_ScreenManager = NULL;

ScreenManager::ScreenManager()
{

	/*unsigned int startingIndex = 0;
	if (_screens.size() > startingIndex)
	{
		theWorld.Add(_screens[startingIndex]);
		_screens[startingIndex]->Start();
		_current = startingIndex;
	}
	else
	{
		_current = -1;
	}*/

	// We must set the sound callback method.  Although, I'm wondering if we should
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);
}

ScreenManager& ScreenManager::GetInstance()
{
  if (s_ScreenManager == NULL)
  {
			 s_ScreenManager = new ScreenManager();
  }
  return *s_ScreenManager;
}

Screen* ScreenManager::GetCurrentScreen()
{
  if(_screens.empty())
	 return NULL;

  return _screens.front();
}

void ScreenManager::Render()
{

}

void ScreenManager::ReceiveMessage(Message* message)
{
	// Handle messages for the screen manager
}

void ScreenManager::SoundEnded(AngelSoundHandle sound)
{
	this->GetCurrentScreen()->SoundEnded(sound);
}

bool ScreenManager::IsScreenActive(Screen *screen)
{
	std::deque<Screen*>::iterator it = std::find(_screens.begin(),_screens.end(), screen);
	if(it == _screens.end())
        throw "Screen is not inside list of screens"; //TODO maybe use std::exception
    return (_screens.front() == screen);
}

bool ScreenManager::IsScreenCovered(Screen *screen)
{
	std::deque<Screen*>::iterator it = std::find(_screens.begin(),_screens.end(), screen);
	if(it == _screens.end())
        throw "Screen is not inside list of screens";

	bool notPopup = false;
    while(it-- != _screens.begin())
	{
		if(!(*it)->IsPopup())
		{
            notPopup = true;
			break;
		}
	}
	return notPopup;
}

void ScreenManager::AddScreen(Screen *screen)
{
    _screens.push_front(screen);
	theWorld.Add(screen);
    screen->Start();
}

void ScreenManager::RemoveScreen(Screen *screen)
{
	if(screen == NULL)
	{
		this->_removeScreen();
		return;
	}

	std::deque<Screen*>::iterator it = std::find(_screens.begin(),_screens.end(), screen);
	if(it == _screens.end())
		throw "Screen is not inside list of screens";

	while(_screens.front() != screen)
	{
		this->_removeScreen();
	}

	this->_removeScreen();
}

void ScreenManager::_removeScreen()
{
	Screen* toRemove = _screens.front();
	_screens.pop_front();
	toRemove->Stop();
}
