#include <TestScreen2.h>
#include <TestScreen.h>
#include <ScreenManager.h>
#include <DialogueScreen.h>

//cTor
TestScreen2::TestScreen2() : Screen()
{

}

void TestScreen2::Start()
{
	box = new Item("Box");
	box->SetSize(10.0f,10.0f);
	box->SetPosition(0,0);

	/*mysquare = new Actor();
	mysquare->SetSize(3.0f,3.0f);
	mysquare->SetDrawShape(ADS_Square);

    x = 0;
    y = 0;
    step = 1;
    timer = 0.0f;
	mysquare->SetPosition(x,y);
	mysquare->SetColor(0,1.0,0);
	mysquare->SetLayer(this->_layer+1);
	this->_objects.push_back(mysquare);*/
	this->_objects.push_back(box);

	/*TextActor* text = new TextActor("Console","Press Left Arrow to go back to the previous screen.\nThis screen shows a square moving left and right :D\nPress Right Arrow to open a dialogue screen.",TXT_Center);
	text->SetPosition(0,-1);
	text->SetColor(0,0,0);
	text->SetLayer(this->_layer+2);
	this->_objects.push_back(text);*/

    Screen::Start();
	box->Start();
}

void TestScreen2::BindMessages()
{
    theSwitchboard.SubscribeTo(this,"Previous Screen");
	theSwitchboard.SubscribeTo(this,"Next Screen");
	theSwitchboard.SubscribeTo(this,"UseItem");
}

void TestScreen2::Update(float dt)
{
        Screen::Update(dt);

        if(this->_isPaused)
            return;

		/*timer += dt;

		if(timer >= 0.33)
        {
            x += step;
            mysquare->SetPosition(x,y);
            timer = 0.0f;
        }
        if(x > 10)
            step = -1;
        if(x < -10)
			step = 1;*/
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
		theScreenManager.SwapScreen(new TestScreen());
	else if(message->GetMessageName() == "Next Screen")
		theScreenManager.AddScreen(new DialogueScreen("example_message.lua",Color(0,0,0,0.9)));
	else if(message->GetMessageName() == "UseItem")
	{
		box->Use();
	}
}

void TestScreen2::SoundEnded(AngelSoundHandle sound)
{
        Screen::SoundEnded(sound);
}

void TestScreen2::Stop()
{
        Screen::Stop();
}
