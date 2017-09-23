#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
using namespace std;

class SoundFX {
private:
  string file;
  bool working = false;
  Mix_Chunk* sound;

public:
  SoundFX (string);
  bool loaded();
  bool play();
  bool load();

  virtual ~SoundFX ();
};
