#ifndef SCREEN_H
#define SCREEN_H

#include <stdafx.h>
#include <vector>

/* This is the screen with all the stuff needed to render shit */
class Screen : public Renderable, public MessageListener
{
public:
  Screen(bool isPopup = false,
         bool isPausable = true,
         bool isHideable = true);

  virtual void Start();
  virtual void BindMessages(); //function that binds messages
  virtual void Stop(); //calls remove on all _objects and deletes them
  virtual void Update(float dt);
  virtual void Render();

  virtual void ReceiveMessage(Message *message);
  virtual void SoundEnded(AngelSoundHandle sound);

  void MarkForDeletion();

  inline bool IsPopup() { return _isPopup; }

private:
  void _Pause(bool value); //pass "true" to stop updating, "false" to resume
  void _Show(bool value); //pass "true" to show stuff, "false" to hide the screen
  void _HandleScreens();
  void _StartObjects(); //connects all the _objects to theWorld

protected:
  std::vector<Renderable*> _objects; //list of objects we draw on screen
  bool _isPopup; //if the screen is a popup screen or not
  bool _isPausable; //if the screen can be paused or not
  bool _isHideable; //if the screen can be hidden (remove all objects from world) or not
  bool _isPaused; //if the screen is paused (aka not updating)
  bool _isHidden; //if the screen is hidden (aka not drawing)
  bool _isActive; //if the screen is the topmost
  bool _isCovered; //if the screen is covered (by a popup = not covered)
  bool _isGettingDeleted; //if the screen is getting removed by the ScreenManager
};

#endif // SCREEN_H
