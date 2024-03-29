#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <stdafx.h>

#include <Screen.h>

#include <vector>
#include <string>
#include <deque>


/* Singleton of my ScreenManager, it handles screens and shit in the game */
#define theScreenManager ScreenManager::GetInstance()

/* Offset for the screen layer number */
#define SCREEN_LAYER_OFFSET 1000

class ScreenManager : public GameManager
{
public:

  static ScreenManager &GetInstance();

  Screen* GetCurrentScreen();

  virtual void Render();

  virtual void SoundEnded(AngelSoundHandle sound);
  virtual void ReceiveMessage(Message* message);

  virtual void AddScreen(Screen* screen);
  virtual void RemoveScreen(Screen* screen = NULL); // Removes the screen, if NULL it removes only the top-most, else it recursively remove all screens
  virtual void SwapScreen(Screen* screen, Screen* oldScreen = NULL); //substitutes the selected screen (while removing it) with the new screen passed as parameter

  bool IsScreenActive(Screen* screen); // Check if the screen is active (topmost screen)
  bool IsScreenCovered(Screen* screen); // Check if the screens above this are full screens or just popups (aka not covering)


protected:
  ScreenManager();
  static ScreenManager *s_ScreenManager;

private:

  //Fields
  std::deque<Screen*> _screens;
  std::deque<Screen*> _toRemove;
};


#endif // SCREENMANAGER_H
