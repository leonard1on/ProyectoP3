#include "Kopemon.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include <string>
#include <typeinfo>
#include <fstream>
using namespace std;

Kopemon::Kopemon() : Object(){

}

Kopemon::Kopemon(string pName, int pHp){
  name=pName;
  hp=pHp;
  status="Normal";
  originalhp=pHp;
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

int Kopemon::getOriginalHp(){
  return originalhp;
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
  if (kopemon->getHp()<=0) {
    status="Fainted";
    hp=0;
  }
}

string Kopemon::Special(Kopemon* kopemon){
  int ataque=50;
  string texto = ""+name+" used special attack.";

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
  return texto;
}

string Kopemon::Normal(Kopemon* kopemon){
  int ataque=50;
  string texto = ""+name+" used normal attack.";

  kopemon->setHp(kopemon->getHp()-ataque);

  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }

  kopemon->Damage(kopemon);
  return texto;
}

void Kopemon::Revive(Kopemon* kopemon){
  if (typeid(*kopemon)==typeid(Water)) {
    kopemon->Revive(kopemon);
  }
}

bool Kopemon::Accuracy(int accuracy){
  return true;
}

bool Kopemon::Paralyzed(string status){
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

ostream& operator<<(ostream& out, const Kopemon kopemon){
  out<<kopemon.name<<"\n";
}



Kopemon::~Kopemon(){

}
