#ifndef TRANSITIONSCREEN_H
#define TRANSITIONSCREEN_H

#include <stdafx.h>
#include <Screen.h>

// This is a transition screen, it performs a transparent transition (fade to color) from one screen to the next (removing the old one)
class TransitionScreen : public Screen
{
public:
	TransitionScreen(Screen *newScreen, Color bg = Color(0,0,0));

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
	Color _color;
	Screen* _swappedScreen;
	Screen* _oldScreen;
	bool _inTransition;

};

#endif // TRANSITIONSCREEN_H
