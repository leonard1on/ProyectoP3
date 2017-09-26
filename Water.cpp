#include "Kopemon.h"
#include "Water.h"
#include "Fire.h"
#include "Grass.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <time.h>
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

string Water::Special(Kopemon* kopemon){
  int ataque=especial->getEffect();
  string texto = ""+name+" used "+especial->getName()+".";
  hp2=especial->getEffect();
  if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if(typeid(*kopemon) == typeid(Grass)){
    ataque=ataque/2;
    texto+=" Its not very Effective!";
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
    if(kopemon->getHp()>kopemon->getOriginalHp()){
      kopemon->setHp(20);
    }
  }
  
  kopemon->Damage(kopemon);
  return texto + " It can now revive";
}

string Water::Normal(Kopemon* kopemon){
  int ataque = normal->getDamage();
  string texto = ""+name+" used "+normal->getName()+".";

  if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if(typeid(*kopemon) == typeid(Grass)){
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

bool Water::Paralyzed(string status){
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

Water::~Water(){
  delete normal;
  delete especial;
}
