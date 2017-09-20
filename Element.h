#pragma once
#include "Object.h"
#include "Material.h"
#include <ncurses.h>
#include <string>
using namespace std;

class Element : public Material{
private:
  string tipo;
  int heatness;
public:
  Element (string, int);

  virtual string show();
  virtual string toString();
  virtual string help();
  virtual void printString(int, int);
  virtual void wprintString(WINDOW*, int, int);
  virtual ~Element ();
};
