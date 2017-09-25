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

Fire::Fire(Offensive* pNormal, Offensive* pEspecial, string pNombre, int pHp) : Kopemon(pNombre, pHp){
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

string Fire::Special(Kopemon* kopemon){
  int special=0;
  string texto = ""+name+" used "+especial->getName()+". It was so powerful it hurt itself.";
  hp=hp-20;
  if (hp<=0) {
    status="Fainted";
    texto = ""+name+" fainted when trying to use "+especial->getName();
  }else{
    special=(especial->getDamage() + normal->getDamage())/2;
    if (typeid(*kopemon)==typeid(Grass)){
      special*=2;
      texto+=" Its Super Effective!";
    }else if (typeid(*kopemon)==typeid(Water)) {
      special/=2;
      texto+=" Its not very Effective!";
    }

    kopemon->setHp(kopemon->getHp()-special);

    if (typeid(*kopemon)==typeid(Water)) {
      kopemon->Revive(kopemon);
      if(kopemon->getHp()>kopemon->getOriginalHp()){
        kopemon->setHp(20);
      }
    }

    kopemon->Damage(kopemon);
  }
  return texto;
}

string Fire::Normal(Kopemon* kopemon){
  int ataque=normal->getDamage();
  string texto = ""+name+" used "+normal->getName()+".";

  if (typeid(*kopemon)==typeid(Grass)){
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque/2;
    texto+=" Its not very Effective!";
  }

  if(!Accuracy(normal->getAccuracy())){
    ataque=0;
    texto = ""+name+" used "+normal->getName()+". But it missed the target...";
  }

  if(!Paralyzed(status)){
    ataque=0;
    texto = ""+name+" used "+normal->getName()+". But its paralyzed and cant attack...";
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
    if(kopemon->getHp()>kopemon->getOriginalHp()){
      kopemon->setHp(20);
    }
  }

  kopemon->Damage(kopemon);
  return texto;
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

bool Fire::Paralyzed(string status){
  bool hit=true;
  srand (time(NULL));
  if (status=="Paralyzed") {
    int random=rand() %100 + 1;
    if (random < 25) {
      hit=false;
    }
  }
  return hit;
}

Fire::~Fire(){
  delete normal;
  delete especial;
}
