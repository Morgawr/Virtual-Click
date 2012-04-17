#include <DialogueScreen.h>
#include <ScreenManager.h>
#include <Angel/Scripting/LuaModule.h>
#include <assert.h>

//cTor
 //= Color(0,0,0,0.5f)
DialogueScreen::DialogueScreen(const std::string dialogueScript, Color bgColor) : Screen(true),
	_timer(0),
	_letterCountPerLine(0),
	_letterCounter(0),
	_lineCounter(0),
	_blockedText(false),
	_scriptFile(dialogueScript)
{
	_backgroundColor = new Actor();
	_backgroundColor->SetColor(bgColor);
}

void DialogueScreen::Start()
{

	lua_State* L = LuaScriptingModule::GetLuaState();
	assert(luaL_dofile(L, _scriptFile.c_str()) == 0);

	lua_getglobal(L,"dialogue_body"); //load the message
	assert(lua_isstring(L,-1));
	_message = lua_tostring(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L, "dialogue_body");

	lua_getglobal(L,"dialogue_speed"); //load the speed
	assert(lua_isnumber(L,-1));
	_speed = lua_tonumber(L,-1);
	lua_pop(L,1);
	lua_pushnil(L);
	lua_setglobal(L,"dialogue_speed");

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
			if(_letterCounter > _message.size())
				theScreenManager.RemoveScreen(this);
			_UpdateText();
		}
	}

}

void DialogueScreen::_UpdateText()
{
	if(_letterCounter >= _message.size())
	{
		_letterCounter++;
		_blockedText = true;
		return;
	}

	std::string s = this->_messageOnScreen->GetDisplayString();

	if(_letterCountPerLine > theTuning.GetInt("Dialogue_Wrap_Word_Length") &&
	   (_message[_letterCounter] == ' ' || _letterCountPerLine > theTuning.GetInt("Dialogue_Wrap_Message_Length")) ||
	   _message[_letterCounter] == '\n') //we need to go to a new line
	{
		_letterCountPerLine = 0;

		if(_message[_letterCounter] == '\n')
			_letterCounter++;
		if(_message[_letterCounter] == ' ' ) //avoid printing another space in a newline or duplicating newlines
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

	s += _message[_letterCounter];
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
	else if(message->GetMessageName() == "Advance Text" && _lineCounter+1 >= theTuning.GetInt("Dialogue_Max_Lines"))
	{
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
