#pragma once
#include "Object.h"
#include <string>
using namespace std;

class Animal : public Object{
private:
  string name;
  string tipo;

public:
  Animal (string, string);
  string getNombre();
  string getTipo();
  void setNombre(string);
  void setTipo(string);
  virtual ~Animal ();
};
