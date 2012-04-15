#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include <stdafx.h>

#include <Screen.h>


// This class is a test screen class, it will be to test the game and how it goes :)
class TestScreen : public Screen
{
public:
        TestScreen();

        void Start();
        void BindMessages();
        void Stop();
        void Update(float dt);
        void Render();

        void ReceiveMessage(Message *message);
        void SoundEnded(AngelSoundHandle sound);

protected:

private:

        Actor* mycircle;
        int x;
        int y;
        float timer;
        int step;

};

#endif // TESTSCREEN_H
