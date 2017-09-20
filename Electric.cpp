#include "Kopemon.h"
#include "Electric.h"
#include "Water.h"
#include "Grass.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
#include <typeinfo>
using namespace std;

Electric::Electric(Offensive* pNormal, string pNombre, int pHp) : Kopemon(pNombre, pHp){
  normal=pNormal;
  ppEspecial=3;
}

Offensive* Electric::getNormal(){
  return normal;
}

int Electric::getEspecial(){
  return ppEspecial;
}

void Electric::setNormal(Offensive* pNormal){
  normal=pNormal;
}

void Electric::setEspecial(int pppEspecial){
  ppEspecial=pppEspecial;
}

void Electric::Damage(Kopemon* kopemon){
  if (kopemon->getHp()<=0) {
    status="Fainted";
    hp=0;
  }
}

void Electric::Special(Kopemon* kopemon){
  if (ppEspecial!=0) {
    kopemon->setStatus("Paralyzed");
    ppEspecial--;
  }
}

void Electric::Normal(Kopemon* kopemon){
  int ataque = normal->getDamage();
  if (typeid(*kopemon) == typeid(Water)) {
    ataque=ataque*2;
  }else if (typeid(*kopemon) == typeid(Grass)) {
    ataque=ataque/2;
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
}

bool Electric::Accuracy(int accuracy){
  bool hit=true;
  srand (time(NULL));
  int random=rand() %100 + 1;
  if (accuracy < random) {
    hit=false;
  }
  return hit;
}

Electric::~Electric(){
  delete normal;
}
