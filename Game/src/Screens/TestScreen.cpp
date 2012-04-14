#include <TestScreen.h>
#include <TestScreen2.h>
#include <ScreenManager.h>

//cTor
TestScreen::TestScreen() : Screen()
{

}

void TestScreen::Start()
{
        Screen::Start();
        mycircle = new Actor();
        mycircle->ChangeSizeTo(5.0f,0.0f);
        mycircle->SetDrawShape(ADS_Circle);
        x = 0;
        y = 0;
        step = 1;
        timer = 0.0f;
        mycircle->SetPosition(x,y);
        mycircle->SetColor(0,100,0);
        this->_objects.push_back(mycircle);
        theWorld.Add(mycircle);
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
            theScreenManager.AddScreen(new TestScreen2()); //we add a screen to demonstrate that this screen stops updating
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
