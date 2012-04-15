
#include <BackgroundScreen.h>



//ctor
BackgroundScreen::BackgroundScreen(Color bg) : Screen(false,false,false)
{
    _background = new FullScreenActor();
    _background->SetColor(bg);
}

BackgroundScreen::BackgroundScreen(FullScreenActor* bg) : Screen(false,false,false)
{
    _background = bg;
}


void BackgroundScreen::Start()
{
    this->_objects.push_back(_background);
    Screen::Start();
}

void BackgroundScreen::BindMessages()
{
    Screen::BindMessages();
}

void BackgroundScreen::Stop()
{
    Screen::Stop();
}

void BackgroundScreen::Update(float dt)
{
    Screen::Update(dt);
}

void BackgroundScreen::Render()
{
    Screen::Render();
}

void BackgroundScreen::ReceiveMessage(Message *message)
{
    Screen::ReceiveMessage(message);
}

void BackgroundScreen::SoundEnded(AngelSoundHandle sound)
{
    Screen::SoundEnded(sound);
}
