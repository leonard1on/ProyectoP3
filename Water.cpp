#include "Kopemon.h"
#include "Water.h"
#include "Fire.h"
#include "Grass.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <string>
#include <typeinfo>
#include <iostream>
using namespace std;

Water::Water(PowerUp* pEspecial, Offensive* pNormal, string pNombre, int pHp) : Kopemon(pNombre, pHp){
  especial=pEspecial;
  normal=pNormal;
}

PowerUp* Water::getEspecial(){
  return especial;
}

Offensive* Water::getNormal(){
  return normal;
}

int Water::getHp2(){
  return hp2;
}
void Water::setEspecial(PowerUp* pEspecial){
  especial=pEspecial;
}

void Water::setNormal(Offensive* pNormal){
  normal=pNormal;
}

void Water::setHp2(int pHp2){
  hp2=pHp2;
}

void Water::Damage(Kopemon* kopemon){
  if (kopemon->getHp()<=0) {
    status="Fainted";
    hp=0;
  }
}

void Water::Special(Kopemon* kopemon){
  int ataque=especial->getEffect();
  hp2=especial->getEffect();
  if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque*2;
  }else if(typeid(*kopemon) == typeid(Grass)){
    ataque=ataque/2;
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
}

void Water::Normal(Kopemon* kopemon){
  int ataque = normal->getDamage();

  if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque*2;
  }else if(typeid(*kopemon) == typeid(Grass)){
    ataque=ataque/2;
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
}

void Water::Revive(Kopemon* kopemon){
  Water* agua=dynamic_cast<Water*>(kopemon);
  if(agua->getHp() <=0 ){
    int extraHp=agua->getHp()+agua->getHp2();
      agua->setHp(extraHp);
      agua->setHp2(0);
  }
}

bool Water::Accuracy(int accuracy){
  bool hit=true;
  srand (time(NULL));
  int random=rand() %100 + 1;
  if (accuracy < random) {
    hit=false;
  }
  return hit;
}

Water::~Water(){
  delete normal;
  delete especial;
}
