#include "Attack.h"
#include "PowerUp.h"
#include <string>
using namespace std;

PowerUp::PowerUp(int pEffect, string pName) : Attack(pName){
  effect=pEffect;
}

int PowerUp::getEffect(){
  return effect;
}

void PowerUp::setEffect(int pEffect){
  effect=pEffect;
}
