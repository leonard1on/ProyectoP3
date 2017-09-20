#pragma once
#include "Material.h"
#include <ncurses.h>
#include <string>
using namespace std;

class Stone : public Material{
private:
  string nombre;
  string color;

public:
  Stone (string, string);

  virtual string show();
  virtual string toString();
  virtual string help();
  virtual void printString(int, int);
  virtual void wprintString(WINDOW*, int, int);
  virtual ~Stone ();
};
