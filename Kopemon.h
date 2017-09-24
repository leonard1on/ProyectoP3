#pragma once
#include <string>
#include "Attack.h"
#include "Offensive.h"
#include "Object.h"
using namespace std;

class Kopemon : public Object{
protected:
  string name;
  int hp;
  string status;
  int originalhp;

public:
  Kopemon();
  Kopemon (string, int);
  virtual ~Kopemon();
  //Mutadores
  virtual string getNombre();
  virtual int getHp();
  virtual string getStatus();
  int getOriginalHp();
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
  void curar();
};
