#include <TestScreen2.h>
#include <ScreenManager.h>

//cTor
TestScreen2::TestScreen2() : Screen(true)
{

}

void TestScreen2::Start()
{
    mysquare = new Actor();
    mysquare->ChangeSizeTo(5.0f,0.0f);
    mysquare->SetDrawShape(ADS_Square);
    x = 0;
    y = 0;
    step = 1;
    timer = 0.0f;
    mysquare->SetPosition(x,y);
    mysquare->SetColor(0,100,0);
    this->_objects.push_back(mysquare);

    Screen::Start();
}

void TestScreen2::BindMessages()
{
    theSwitchboard.SubscribeTo(this,"Next Screen");
}

void TestScreen2::Update(float dt)
{
        Screen::Update(dt);

        if(this->_isPaused)
            return;

        timer += dt;

        if(timer >= 0.33)
        {
            x += step;
            mysquare->SetPosition(x,y);
            timer = 0.0f;
        }
        if(x > 10)
            step = -1;
        if(x < -10)
            step = 1;
}

void TestScreen2::Render()
{
        Screen::Render();
}

void TestScreen2::ReceiveMessage(Message *message)
{
    Screen::ReceiveMessage(message);

    if(this->_isPaused)
        return;

    if(message->GetMessageName() == "Next Screen")
        theScreenManager.RemoveScreen(this);
}

void TestScreen2::SoundEnded(AngelSoundHandle sound)
{
        Screen::SoundEnded(sound);
}

void TestScreen2::Stop()
{
        Screen::Stop();
}
