#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
using namespace std;

class Music {
private:
  string file;
  bool working = false;
  Mix_Music* music;

public:
  Music (string);
  bool loaded();
  bool play();
  bool load();
  void halt();

  virtual ~Music ();
};
