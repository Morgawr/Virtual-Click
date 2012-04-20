
#include "stdafx.h"

#include <ScreenManager.h>
#include <TestScreen.h>
#include <BackgroundScreen.h>

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

  theWorld.Initialize(1024,768,"Game");

  theWorld.SetGameManager(&theScreenManager);
  FullScreenActor* fs = new FullScreenActor();
  fs->SetColor(Color(0,0,0));
  theScreenManager.AddScreen(new BackgroundScreen(fs));
  theScreenManager.AddScreen(new TestScreen());

  // do all your setup first, because this function won't return until you're exiting
  theWorld.StartGame();

  // any cleanup can go here
  theWorld.Destroy();

  return 0;
}

