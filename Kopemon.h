#pragma once
#include <string>
#include "Attack.h"
#include "Offensive.h"
using namespace std;

class Kopemon{
protected:
  string name;
  int hp;
  string status;

public:
  Kopemon();
  Kopemon (string, int);

  //Mutadores
  virtual string getNombre();
  virtual int getHp();
  virtual string getStatus();
  virtual void setNombre(string);
  virtual void setHp(int);
  virtual void setStatus(string);
  virtual Offensive* getNormal();
  virtual void setNormal(Offensive*);

  //Metodos de los Kopemon
  virtual void Damage(Kopemon*);
  virtual void Special(Kopemon*);
  virtual void Normal(Kopemon*);
  virtual void Revive(Kopemon*);
  virtual bool Accuracy(int);
};
