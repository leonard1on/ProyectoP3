#pragma once
#include <string>
#include "Attack.h"
#include "Offensive.h"
#include "Object.h"
#include <fstream>
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
  virtual string Special(Kopemon*);
  virtual string Normal(Kopemon*);
  virtual void Revive(Kopemon*);
  virtual bool Accuracy(int);
  virtual bool Paralyzed(string);
  friend ostream& operator<<(ostream&, const Kopemon);
};
