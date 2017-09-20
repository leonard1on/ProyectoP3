#pragma once
#include "Object.h"
#include <string>
#include <ncurses.h>
using namespace std;

class Material : public Object{
protected:
  string descripcion;
public:
  Material();

  virtual string show()=0;
  virtual string toString()=0;
  virtual string help()=0;
  virtual void printString(int, int)=0;
  virtual void wprintString(WINDOW*, int, int)=0;
  virtual ~Material ()=0;
};
