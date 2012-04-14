
#include "stdafx.h"

#include <ScreenManager.h>
#include <TestScreen.h>

#include <iostream>


int main(int argc, char* argv[])
{
  //        get things going
  //        optional parameters:
  //		int windowWidth			default: 1024
  //		int windowHeight		default: 768
  //		std::string windowName	default: "Angel Engine"
  //		bool antiAliasing		default: false
  //		bool fullScreen			default: false

  theWorld.Initialize(800,600,"Game");

  // CREATING LOGS

  //adds the default grid so you can more easily place Actors
  theWorld.Add(new GridActor(), -1);
  theWorld.SetGameManager(&theScreenManager);
  theScreenManager.AddScreen(new TestScreen());

  // do all your setup first, because this function won't return until you're exiting
  theWorld.StartGame();

  // any cleanup can go here
  theWorld.Destroy();

  return 0;
}

