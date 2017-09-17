#pragma once
#include "Kopemon.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
using namespace std;

class Electric : public Kopemon{
  private:
    int ppEspecial;
    Offensive* normal;

  public:
    Electric(Offensive*, string, int);
    Offensive* getNormal();
    int getEspecial();
    void setNormal(Offensive*);
    void setEspecial(int);

    void Damage(Kopemon*);
    void Special(Kopemon*);
    void Normal(Kopemon*);
    bool Accuracy(int);
};
