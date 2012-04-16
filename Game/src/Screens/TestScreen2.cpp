#include <TestScreen2.h>
#include <ScreenManager.h>

//cTor
TestScreen2::TestScreen2() : Screen()
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
    mysquare->SetLayer(this->_layer+1);
    this->_objects.push_back(mysquare);

    TextActor* text = new TextActor("Console","Press Left Arrow to go back to the previous screen.\nThis screen shows a square moving left and right :D",TXT_Center);
    text->SetPosition(0,-1);
    text->SetColor(0,0,0);
    text->SetLayer(this->_layer+2);
    this->_objects.push_back(text);

    Screen::Start();
}

void TestScreen2::BindMessages()
{
    theSwitchboard.SubscribeTo(this,"Previous Screen");
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

    if(message->GetMessageName() == "Previous Screen")
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
