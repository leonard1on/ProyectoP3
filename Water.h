#pragma once
#include "Kopemon.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <string>
using namespace std;

class Water : public Kopemon{
  private:
    PowerUp* especial;
    Offensive* normal;
    int hp2;

  public:
    Water(PowerUp*, Offensive*, string, int);
    PowerUp* getEspecial();
    Offensive* getNormal();
    int getHp2();
    void setEspecial(PowerUp*);
    void setNormal(Offensive*);
    void setHp2(int);

    void Damage(Kopemon*);
    string Special(Kopemon*);
    string Normal(Kopemon*);
    void Revive(Kopemon*);
    bool Accuracy(int);
    bool Paralyzed(string);
    ~Water();
};
