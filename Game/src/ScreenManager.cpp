#include <ScreenManager.h>

ScreenManager* ScreenManager::s_ScreenManager = NULL;

ScreenManager::ScreenManager()
{

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
    //We check if we have some screens to remove
    while(!_toRemove.empty())
    {
        Screen* screen = _toRemove.front();
        _toRemove.pop_front();
        screen->Stop();
    }

    _toRemove.clear();

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
    screen->SetLayer(_screens.size()*SCREEN_LAYER_OFFSET); //we multiply the screen position with the screen layer offset for rendering purposes (so we don't overlap)
    screen->Start();
}

void ScreenManager::RemoveScreen(Screen *screen)
{
    Screen* del_screen;
    if(screen == NULL)
    {
        del_screen = _screens.front();
        del_screen->MarkForDeletion();
        _toRemove.push_back(del_screen);
        _screens.pop_front();
        return;
    }

    std::deque<Screen*>::iterator it = std::find(_screens.begin(),_screens.end(), screen);
    if(it == _screens.end())
        throw "Screen is not inside list of screens";

    do
    {
        del_screen = *it;
        del_screen->MarkForDeletion();
        _toRemove.push_front(del_screen);
        /* we don't increment the counter here because we want to remove
          all the screens from our screen till begin() and not till end().
          This means we will go backwards through the list */
        it = _screens.erase(it);
    }while(_screens.begin() != it);

}

void ScreenManager::SwapScreen(Screen *screen, Screen *oldScreen)
{
	if(oldScreen == NULL)
	{
		this->RemoveScreen();
		this->AddScreen(screen);
	}
	else
	{
		std::deque<Screen*>::iterator it = std::find(_screens.begin(),_screens.end(), oldScreen);
		if(it == _screens.end())
			throw "Screen is not inside list of screens";

		oldScreen->MarkForDeletion();
		_toRemove.push_front(oldScreen);
		it = _screens.erase(it);
		_screens.insert(it,screen);
		theWorld.Add(screen);
		screen->SetLayer(oldScreen->GetLayer());
		screen->Start();
	}
}

