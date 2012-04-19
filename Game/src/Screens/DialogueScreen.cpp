#include <DialogueScreen.h>
#include <ScreenManager.h>
#include <Angel/Scripting/LuaModule.h>
#include <PathNames.h>
#include <assert.h>

//cTor
DialogueScreen::DialogueScreen(const std::string dialogueScript, Color bgColor) : Screen(true),
	_timer(0),
	_letterCountPerLine(0),
	_letterCounter(0),
	_lineCounter(0),
	_blockedText(false),
	_currentMessage(0)
{
	if(dialogueScript.rfind(".lua") == std::string::npos)
	{
		//default speed
		_speed = 0.03;
		_messages.push_back(dialogueScript);
	}
	else
	{
		_scriptFile = PATH_DIALOGUE + dialogueScript;
	}
	_backgroundColor = new Actor();
	_backgroundColor->SetColor(bgColor);
}

void DialogueScreen::Start()
{

	_LoadFromFile();

	_messageOnScreen = new TextActor("Console","");
	_messageOnScreen->SetLayer(this->_layer+2);
	_messageOnScreen->SetColor(Color(1,1,1));
	_messageOnScreen->SetPosition(Vector2(theTuning.GetFloat("Dialogue_Text_X_Pos"),
										  theTuning.GetFloat("Dialogue_Text_Y_Pos")));

	_backgroundColor->SetDrawShape(ADS_Square);
	_backgroundColor->ChangeSizeTo(Vector2(theTuning.GetFloat("Dialogue_Rect_Width"),
										   theTuning.GetFloat("Dialogue_Rect_Height")),0);
	_backgroundColor->MoveTo(Vector2(theTuning.GetFloat("Dialogue_Rect_X_Pos"),
									 theTuning.GetFloat("Dialogue_Rect_Y_Pos")),0);
	_backgroundColor->SetLayer(this->_layer+1);

	this->_objects.push_back(_backgroundColor);
	this->_objects.push_back(_messageOnScreen);

	Screen::Start();
}

void DialogueScreen::_LoadFromFile()
{
	lua_State* L = LuaScriptingModule::GetLuaState();
	assert(luaL_dofile(L, _scriptFile.c_str()) == 0);

	lua_getglobal(L,"dialogue_body"); //load the messages
	size_t sz = lua_objlen(L, -1);
	for (size_t i = 1; i <= sz; i++) {
	   lua_rawgeti(L, -1, i);
	   _messages.push_back(lua_tostring(L, -1));
	   lua_pop(L, 1);
	}

	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L, "dialogue_body");

	lua_getglobal(L,"dialogue_speed"); //load the speed
	assert(lua_isnumber(L,-1));
	_speed = lua_tonumber(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L,"dialogue_speed");
}

void DialogueScreen::BindMessages()
{
	theSwitchboard.SubscribeTo(this,"Previous Screen");
	theSwitchboard.SubscribeTo(this,"Advance Text");
}

void DialogueScreen::Update(float dt)
{
	Screen::Update(dt);

	if(this->_isPaused)
		return;
	_timer += dt;

	if(_timer >= _speed) //let's give ourselves a bit of delay
	{
		_timer = 0;
		if(!_blockedText) //update text only if we're not waiting for a key
		{
			if(_letterCounter > _messages[_currentMessage].size())
			{
				_currentMessage++;
				if(_currentMessage == _messages.size())
				{
					theScreenManager.RemoveScreen(this);
					return;
				}
				_letterCountPerLine = 0;
				_letterCounter = 0;
				_lineCounter = 0;
				_blockedText = false;
				_messageOnScreen->SetDisplayString("");
			}
			_UpdateText();
		}
	}

}

void DialogueScreen::_UpdateText()
{
	if(_letterCounter >= _messages[_currentMessage].size())
	{
		_letterCounter++;
		_blockedText = true;
		return;
	}

	std::string s = this->_messageOnScreen->GetDisplayString();

	if(_letterCountPerLine > theTuning.GetInt("Dialogue_Wrap_Word_Length") &&
	   ( _messages[_currentMessage][_letterCounter] == ' ' || _letterCountPerLine > theTuning.GetInt("Dialogue_Wrap_Message_Length")) ||
		_messages[_currentMessage][_letterCounter] == '\n') //we need to go to a new line
	{
		_letterCountPerLine = 0;

		if( _messages[_currentMessage][_letterCounter] == '\n')
			_letterCounter++;
		if( _messages[_currentMessage][_letterCounter] == ' ' ) //avoid printing another space in a newline or duplicating newlines
			_letterCounter++;

		s += '\n';
		_lineCounter++;

		if(_lineCounter >= theTuning.GetInt("Dialogue_Max_Lines"))
		{
			this->_messageOnScreen->SetDisplayString(s);
			_blockedText = true;
			return;
		}

	}

	s +=  _messages[_currentMessage][_letterCounter];
	_letterCounter++;
	_letterCountPerLine++;
	this->_messageOnScreen->SetDisplayString(s);
}

void DialogueScreen::Render()
{
	Screen::Render();
}

void DialogueScreen::ReceiveMessage(Message *message)
{
	Screen::ReceiveMessage(message);

	if(this->_isPaused)
		return;

	if(message->GetMessageName() == "Previous Screen")
		theScreenManager.RemoveScreen(this);
	else if(message->GetMessageName() == "Advance Text")
	{
		bool inloop = false;
		while(_letterCounter < _messages[_currentMessage].size() && !_blockedText)
		{
			_UpdateText();
			inloop = true;
		}
		if(inloop)
			return;

		_blockedText = false;
		std::string s = _messageOnScreen->GetDisplayString();
		int index = s.find('\n');
		s = s.erase(0,index+1);
		_messageOnScreen->SetDisplayString(s);
		_lineCounter--;
	}

}

void DialogueScreen::SoundEnded(AngelSoundHandle sound)
{
	Screen::SoundEnded(sound);
}

void DialogueScreen::Stop()
{
	Screen::Stop();
}
