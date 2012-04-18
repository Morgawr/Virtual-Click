#ifndef DIALOGUESCREEN_H
#define DIALOGUESCREEN_H

#include <stdafx.h>

#include <string>

#include <Screen.h>

/*//Max length of the message for forced wrapping
#define WRAP_MESSAGE_LENGTH 76

//Max length of the message before testing autowrapping around words
#define WRAP_WORD_LENGTH 70

//Max number of lines in the message shown on screen
#define MAX_DIALOGUE_LINES 6*/

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

	std::string _message;
	TextActor* _messageOnScreen;
	Actor* _backgroundColor;
	float _timer;
	float _speed; //interval at which we update the text
	int	_letterCountPerLine; //number of letters already printed on screen (reset every newline)
	int _letterCounter; //number of letters already printed (total) on screen
	int _lineCounter; //number of lines shown on screen
	bool _blockedText; //check if the text is blocked waiting to advance
	std::string _scriptFile; //the .lua file that holds all the data for the dialogue
};


#endif // DIALOGUESCREEN_H
