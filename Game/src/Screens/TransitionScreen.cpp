
#include <TransitionScreen.h>
#include <ScreenManager.h>
#include <limits>



//ctor
TransitionScreen::TransitionScreen(Screen *newScreen, Color bg) : Screen(true,true,false)
{
	_background = new FullScreenActor();
	bg.A = 0;
	_color = bg;
	_background->SetColor(_color);
	_swappedScreen = newScreen;
	_oldScreen = theScreenManager.GetCurrentScreen(); //we save the current screen (Which is not transitioning yet) so we can swap it out later
	_inTransition = true;
}


void TransitionScreen::Start()
{
	this->_objects.push_back(_background);
	_background->SetLayer(std::numeric_limits<int>::max()); //we make sure the layer is on the top-most possible layer (so it covers everything)
	Screen::Start();
}

void TransitionScreen::BindMessages()
{
	Screen::BindMessages();
}

void TransitionScreen::Stop()
{
	Screen::Stop();
}

void TransitionScreen::Update(float dt)
{
	Screen::Update(dt);

	if(this->_isPaused)
		return;

	if(_inTransition)
	{
		_color.A += 0.02;
		if(_color.A > 1)
		{
			_inTransition = false;
			theScreenManager.SwapScreen(_swappedScreen,_oldScreen);
		}
	}
	else
	{
		_color.A -= 0.02;
		if(_color.A <= 0)
		{
			theScreenManager.RemoveScreen();
		}
	}
	_background->ChangeColorTo(_color,0);
}

void TransitionScreen::Render()
{
	Screen::Render();
}

void TransitionScreen::ReceiveMessage(Message *message)
{
	Screen::ReceiveMessage(message);
}

void TransitionScreen::SoundEnded(AngelSoundHandle sound)
{
	Screen::SoundEnded(sound);
}
