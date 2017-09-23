#include "SoundFX.h"
#include <string>

using namespace std;

SoundFX::SoundFX(string pFile){
  file=pFile;
  load();
}

bool SoundFX::loaded(){
  return working;
}

bool SoundFX::play(){
  if (Mix_PlayChannel(-1, sound, 0) == -1) {
    cout<<"Error Not loading" <<endl;
    return false;
  }
  return true;
}

bool SoundFX::load(){
  sound =Mix_LoadWAV(file.c_str());

  if (sound == NULL) {
    cout << "Error Not Loading" <<endl;
  }else{
    working = true;
  }

  return working;
}

SoundFX::~SoundFX(){
  Mix_FreeChunk(sound);
}
