#pragma once
#include "Kopemon.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <string>
using namespace std;

class Grass : public Kopemon{
  private:
    PowerUp* especial;
    Offensive* normal;

  public:
    Grass(PowerUp*, Offensive*, string, int);
    PowerUp* getEspecial();
    Offensive* getNormal();
    void setEspecial(PowerUp*);
    void setNormal(Offensive*);

    void Damage(Kopemon*);
    string Special(Kopemon*);
    string Normal(Kopemon*);
    bool Accuracy(int);
    bool Paralyzed(string);
    ~Grass();
};
