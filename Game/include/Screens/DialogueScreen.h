#ifndef DIALOGUESCREEN_H
#define DIALOGUESCREEN_H

#include <stdafx.h>

#include <string>

#include <Screen.h>


// This class is a test screen class, it will be to test the game and how it goes :)
class DialogueScreen : public Screen
{
public:
	DialogueScreen(std::string dialogueScript, Color bgColor = Color(0,0,0,0.9));

	void Start();
	void BindMessages();
	void Stop();
	void Update(float dt);
	void Render();

	void ReceiveMessage(Message *message);
	void SoundEnded(AngelSoundHandle sound);

protected:

private:
	void _UpdateText(); //Function that updates the text at a desired speed adding letters all the time
	void _LoadFromFile(); //Function that loads all the data from the lua file

	std::vector<std::string> _messages;
	TextActor* _messageOnScreen;
	Actor* _backgroundColor;
	float _timer;
	int _currentMessage;
	float _speed; //interval at which we update the text
	int	_letterCountPerLine; //number of letters already printed on screen (reset every newline)
	int _letterCounter; //number of letters already printed (total) on screen
	int _lineCounter; //number of lines shown on screen
	bool _blockedText; //check if the text is blocked waiting to advance
	std::string _scriptFile; //the .lua file that holds all the data for the dialogue
};


#endif // DIALOGUESCREEN_H
