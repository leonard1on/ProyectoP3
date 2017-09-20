#pragma once
#include "Attack.h"
#include <string>
using namespace std;

class PowerUp : public Attack{
  private:
    int effect;
  public:
    PowerUp (int, string);
    int getEffect();
    void setEffect(int);
    ~PowerUp();
};
