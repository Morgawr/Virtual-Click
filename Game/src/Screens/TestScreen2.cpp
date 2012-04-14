#include <TestScreen2.h>


//cTor
TestScreen2::TestScreen2() : Screen()
{

}

void TestScreen2::Start()
{
        Screen::Start();
}

void TestScreen2::Update(float dt)
{
        Screen::Update(dt);
}

void TestScreen2::Render()
{
        Screen::Render();
}

void TestScreen2::ReceiveMessage(Message *message)
{
        Screen::ReceiveMessage(message);
}

void TestScreen2::SoundEnded(AngelSoundHandle sound)
{
        Screen::SoundEnded(sound);
}

void TestScreen2::Stop()
{
        Screen::Stop();
}
