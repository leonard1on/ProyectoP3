#include "Attack.h"
#include "Offensive.h"
#include <string>
using namespace std;

Offensive::Offensive(int pDamage, int pAccuracy, string pName) : Attack(pName){
  damage=pDamage;
  accuracy=pAccuracy;
}

int Offensive::getDamage(){
  return damage;
}

int Offensive::getAccuracy(){
  return accuracy;
}

void Offensive::setDamage(int pDamage){
  damage=pDamage;
}

void Offensive::setAccuracy(int pAccuracy){
  accuracy=pAccuracy;
}
