#include "Music.h"
#include <string>

using namespace std;

Music::Music(string pFile){
  file=pFile;
  load();
}

bool Music::loaded(){
  return working;
}

bool Music::play(){
  if (Mix_PlayMusic(music, -1) == -1) {
    cout<<"Error Not loading" <<endl;
    return false;
  }
  return true;
}

bool Music::load(){
  music = Mix_LoadMUS(file.c_str());

  if (music == NULL) {
    cout << "Error Not Loading" <<endl;
  }else{
    working = true;
  }

  return working;
}

void Music::halt(){
  Mix_HaltMusic();
}

Music::~Music(){
  Mix_FreeMusic(music);
}
