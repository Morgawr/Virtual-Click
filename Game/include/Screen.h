#ifndef SCREEN_H
#define SCREEN_H

#include <stdafx.h>
#include <vector>

/* This is the screen with all the stuff needed to render shit */
class Screen : public Renderable
{
public:
  Screen(bool isPopup = false);

  virtual void Start();
  virtual void Stop(); //calls remove on all _objects and deletes them
  virtual void Update(float dt);
  virtual void Render();

  virtual void ReceiveMessage(Message *message);
  virtual void SoundEnded(AngelSoundHandle sound);

  inline bool IsPopup() { return _isPopup; }

protected:
  std::vector<Renderable*> _objects;
  bool _isPopup;

};

#endif // SCREEN_H
