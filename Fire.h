#pragma once
#include "Kopemon.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
using namespace std;

class Fire : public Kopemon{
private:
  Offensive* especial;
  Offensive* normal;

public:
  Fire (Offensive*, Offensive*, string, int);
  Offensive* getEspecial();
  Offensive* getNormal();
  void setEspecial(Offensive*);
  void setNormal(Offensive*);

  void Damage(Kopemon*);
  void Special(Kopemon*);
  void Normal(Kopemon*);
  bool Accuracy(int);
  ~Fire();
};
