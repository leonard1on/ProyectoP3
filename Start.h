#pragma once
#include "Kopemon.h"
#include "Fire.h"
#include "Grass.h"
#include "Electric.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include "Animal.h"
#include "Element.h"
#include <string>
#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

class Start {
public:
  void run();
  vector<Kopemon*> title(); //Title Screen
  string inicio(); //Professor Maple
  void explicacion(string); // Tutorial
  vector<Kopemon*> load(); //Load kopemons
  vector<Element*> fillElements(); //Create elements
  vector<Animal*> fillAnimals(); //Create Animals
  int battle(vector<Kopemon*>); //Battle
  vector<Kopemon*> Enemy();
  ~Start();
};
