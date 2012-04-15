#include <Screen.h>
#include <ScreenManager.h>

Screen::Screen(bool isPopup, bool isPausable, bool isHideable) :
    _isPopup(isPopup),
    _isPausable(isPausable),
    _isHideable(isHideable)
{

}

void Screen::Start()
{
    this->_isHidden = false;
    this->_isPaused = false;
    this->_isGettingDeleted = false;
    this->BindMessages();
    this->_StartObjects();
}

void Screen::_StartObjects()
{
    for(std::vector<Renderable*>::iterator it = _objects.begin();
        it != _objects.end(); it++)
    {
        theWorld.Add(*it);
    }
}

void Screen::BindMessages()
{
    //Do global message binding for keyboard and stuff here
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

void Screen::MarkForDeletion()
{
    this->_isGettingDeleted = true;
}

void Screen::Update(float dt)
{
    if(this->_isGettingDeleted)
    {
        this->_isPaused = true; //we pause and stop drawing the screen
        this->_isHidden = true;
        return;
    }

    this->_HandleScreens();
}

void Screen::_HandleScreens()
{
    this->_isActive = theScreenManager.IsScreenActive(this);
    this->_isCovered = theScreenManager.IsScreenCovered(this);

    //Should we pause the screen?
    if(!this->_isActive &&
       this->_isPausable &&
       !this->_isPaused)
    {
        _Pause(true);
    }
    else if(this->_isActive && this->_isPaused)
    {
        _Pause(false); //resume
    }

    //Should we stop drawing?
    if(this->_isCovered &&
        this->_isHideable &&
        !this->_isHidden)
    {
        _Show(false);
    }
    else if(!this->_isCovered && this->_isHidden)
    {
        _Show(true);
    }
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
    //for global message broadcasting
}

void Screen::_Pause(bool value)
{
    this->_isPaused = value;
}

void Screen::_Show(bool value)
{
    if(value) //Put stuff back to theWorld
    {
        std::vector<Renderable*>::iterator it = _objects.begin();

        while(_objects.end() != it)
        {
            theWorld.Add(*it); //TODO add different layers for objects
            it++;
        }
    }
    else
    {
        std::vector<Renderable*>::iterator it = _objects.begin();

        while(_objects.end() != it)
        {
            theWorld.Remove(*it);
            it++;
        }
    }

    this->_isHidden = !value;
}
