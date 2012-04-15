#ifndef BACKGROUNDSCREEN_H
#define BACKGROUNDSCREEN_H

#include <stdafx.h>

#include <Screen.h>



// This is a background screen. It should be added as the first element of the ScreenManager, under everything else
class BackgroundScreen : public Screen
{
public:
    BackgroundScreen(Color bg);
    BackgroundScreen(FullScreenActor* bg);

    void Start();
    void BindMessages();
    void Stop();
    void Update(float dt);
    void Render();

    void ReceiveMessage(Message *message);
    void SoundEnded(AngelSoundHandle sound);

protected:

private:
    FullScreenActor* _background;

};

#endif // BACKGROUNDSCREEN_H
