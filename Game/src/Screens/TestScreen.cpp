#include <TestScreen.h>
#include <TestScreen2.h>
#include <TransitionScreen.h>
#include <ScreenManager.h>

//cTor
TestScreen::TestScreen() : Screen()
{

}

void TestScreen::Start()
{
    mycircle = new Actor();
    mycircle->ChangeSizeTo(5.0f,0.0f);
    mycircle->SetDrawShape(ADS_Circle);
    x = 0;
    y = 0;
    step = 1;
    timer = 0.0f;
    mycircle->SetPosition(x,y);
	mycircle->SetColor(0,1.0,0);
    mycircle->SetLayer(this->_layer+1);
    this->_objects.push_back(mycircle);

    TextActor* text = new TextActor("Console","Press Right Arrow to load next screen.\nThis screen just shows a circle going up and down :)",TXT_Center);
    text->SetPosition(0,-1);
    text->SetColor(0,0,0);
    text->SetLayer(this->_layer+2);
    this->_objects.push_back(text);

    Screen::Start(); //we should call Screen::Start() last so we set up messages only after we set up the local data
}

void TestScreen::BindMessages()
{
    theSwitchboard.SubscribeTo(this,"Next Screen");
}

void TestScreen::Update(float dt)
    {
    Screen::Update(dt);

    if(this->_isPaused)
        return;

    timer += dt;

    if(timer >= 0.33)
    {
        y += step;
        mycircle->SetPosition(x,y);
        timer = 0.0f;
    }
    if(y > 10)
        step = -1;
    if(y < -10)
        step = 1;
}

void TestScreen::Render()
{
    Screen::Render();
}

void TestScreen::ReceiveMessage(Message *message)
{
    Screen::ReceiveMessage(message);

    if(this->_isPaused)
        return;

    if(message->GetMessageName() == "Next Screen")
	{
		theScreenManager.AddScreen(new TransitionScreen(new TestScreen2()));
	}
		//theScreenManager.AddScreen(new TestScreen2());
		//theScreenManager.SwapScreen(new TestScreen2());

}

void TestScreen::SoundEnded(AngelSoundHandle sound)
{
    Screen::SoundEnded(sound);
}

void TestScreen::Stop()
{
    Screen::Stop();
    mycircle->Destroy();
}
