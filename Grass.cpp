#include "Kopemon.h"
#include "Grass.h"
#include "Fire.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
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

void Grass::Special(Kopemon* kopemon){
  int ataque=especial->getEffect();
  hp=hp+especial->getEffect();
  if (hp>120) {
    hp=120;
  }

  if (normal->getDamage()>10) {
    normal->setDamage(normal->getDamage()-20);
  }else{
    ataque=10;
  }

  if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque*2;
  }else if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque/2;
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
}

void Grass::Normal(Kopemon* kopemon){
  int ataque=normal->getDamage();
  hp=hp+20;
  if (hp>120) {
    hp=120;
  }

  if (typeid(*kopemon)==typeid(Water)) {
    ataque=ataque*2;
  }else if (typeid(*kopemon) == typeid(Fire)) {
    ataque=ataque/2;
  }

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
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
