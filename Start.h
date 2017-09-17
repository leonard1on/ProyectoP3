#pragma once
#include "Kopemon.h"
#include "Fire.h"
#include "Grass.h"
#include "Electric.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <string>
#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

class Start {
public:
  void run();
  vector<Kopemon*> title();
  string inicio();
  void explicacion(string);
};
