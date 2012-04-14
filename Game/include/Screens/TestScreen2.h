#ifndef TESTSCREEN2_H
#define TESTSCREEN2_H

#include <stdafx.h>

#include <Screen.h>


// This class is a test screen class, it will be to test the game and how it goes (part 2)
class TestScreen2 : public Screen
{
public:
        TestScreen2();

        void Start();
        void Stop();
        void Update(float dt);
        void Render();

        void ReceiveMessage(Message *message);
        void SoundEnded(AngelSoundHandle sound);

protected:

private:


};



#endif // TESTSCREEN2_H
