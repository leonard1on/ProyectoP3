#include "Kopemon.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
#include <typeinfo>
using namespace std;

Kopemon::Kopemon(){

}

Kopemon::Kopemon(string pName, int pHp){
  name=pName;
  hp=pHp;
  status="Normal";
}

string Kopemon::getNombre(){
  return name;
}

int Kopemon::getHp(){
  return hp;
}

string Kopemon::getStatus(){
  return status;
}

void Kopemon::setNombre(string pName){
  name=pName;
}

void Kopemon::setHp(int pHp){
  hp=pHp;
}

void Kopemon::setStatus(string pStatus){
  status=pStatus;
}

Offensive* Kopemon::getNormal(){
  return NULL;
}

void Kopemon::setNormal(Offensive* offensive){

}

void Kopemon::Damage(Kopemon* kopemon){
  kopemon->Damage(kopemon);
}

void Kopemon::Special(Kopemon* kopemon){
  kopemon->setHp(kopemon->getHp() - 50);
}

void Kopemon::Normal(Kopemon* kopemon){
  kopemon->setHp(kopemon->getHp() - 50);
}

void Kopemon::Revive(Kopemon* kopemon){
  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }
}

bool Kopemon::Accuracy(int accuracy){
  return true;
}