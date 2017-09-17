#include "Kopemon.h"
#include "Fire.h"
#include "Water.h"
#include "Grass.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

Fire::Fire(Offensive* pEspecial, Offensive* pNormal, string pNombre, int pHp) : Kopemon(pNombre, pHp){
  especial=pEspecial;
  normal=pNormal;
}

Offensive* Fire::getEspecial(){
  return especial;
}

Offensive* Fire::getNormal(){
  return normal;
}

void Fire::setEspecial(Offensive* pEspecial){
  especial=pEspecial;
}

void Fire::setNormal(Offensive* pNormal){
  normal=pNormal;
}

void Fire::Damage(Kopemon* kopemon){
  if (kopemon->getHp()<=0) {
    status="Fainted";
    hp=0;
  }
}

void Fire::Special(Kopemon* kopemon){
  int special=0;
  hp=hp-20;
  if (hp<=0) {
    status="Fainted";
  }else{
    special=(especial->getDamage() + normal->getDamage())/2;
    if (typeid(*kopemon)==typeid(Grass)){
      special*=2;
    }else if (typeid(*kopemon)==typeid(Water)) {
      special/=2;
    }
    kopemon->setHp(kopemon->getHp()-special);

    if (typeid(*kopemon)==typeid(Water)) {
      kopemon->Revive(kopemon);
    }

    kopemon->Damage(kopemon);
  }
}

void Fire::Normal(Kopemon* kopemon){

  int ataque=normal->getDamage();
  if (typeid(*kopemon)==typeid(Grass)){
    ataque=ataque*2;
  }else if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque/2;
  }

  if(!Accuracy(normal->getAccuracy())){
    ataque=0;
  }

  cout<<ataque;

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);

}

bool Fire::Accuracy(int accuracy){
  bool hit=true;
  srand (time(NULL));
  int random=rand() %100 + 1;
  if (accuracy < random) {
    hit=false;
  }
  return hit;
}
