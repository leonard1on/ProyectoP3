#pragma once
#include "Attack.h"
#include <string>
using namespace std;

class Offensive : public Attack{
  private:
    int damage;
    int accuracy;
  public:
    Offensive (int, int, string);
    int getDamage();
    int getAccuracy();
    void setDamage(int);
    void setAccuracy(int);
};
