#include "Kopemon.h"
#include "Grass.h"
#include "Fire.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <typeinfo>
using namespace std;

Grass::Grass(PowerUp* pEspecial, Offensive* pNormal, string pNombre, int pHp) : Kopemon(pNombre, pHp){
  especial=pEspecial;
  normal=pNormal;
}

PowerUp* Grass::getEspecial(){
  return especial;
}

Offensive* Grass::getNormal(){
  return normal;
}

void Grass::setEspecial(PowerUp* pEspecial){
  especial=pEspecial;
}

void Grass::setNormal(Offensive* pNormal){
  normal=pNormal;
}

void Grass::Damage(Kopemon* kopemon){
  if (kopemon->getHp()<=0) {
    status="Fainted";
    hp=0;
  }
}

string Grass::Special(Kopemon* kopemon){
  int ataque=especial->getEffect();
  string texto = ""+name+" used "+especial->getName()+".";
  hp=hp+especial->getEffect();
  if (hp>150) {
    hp=150;
  }

  if (normal->getDamage()>10) {
    normal->setDamage(normal->getDamage()-20);
  }else{
    ataque=10;
  }

  if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if (typeid(*kopemon) == typeid(Fire)) {
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
  return texto+" It recovered a lot of HP!";
}

string Grass::Normal(Kopemon* kopemon){
  int ataque=normal->getDamage();
  string texto = ""+name+" used "+normal->getName()+".";
  hp=hp+20;
  if (hp>150) {
    hp=150;
  }

  if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque/2;
    texto+=" Its not very Effective!";
  }
  texto+= " It recovered some HP!";

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

bool Grass::Accuracy(int accuracy){
  bool hit=true;
  srand (time(NULL));
  int random=rand() %100 + 1;
  if (accuracy < random) {
    hit=false;
  }
  return hit;
}

bool Grass::Paralyzed(string status){
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

Grass::~Grass(){
  delete normal;
  delete especial;
}
