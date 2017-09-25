#include "Kopemon.h"
#include "Electric.h"
#include "Water.h"
#include "Grass.h"
#include "Attack.h"
#include "Offensive.h"
#include <stdlib.h>
#include <time.h>
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

string Electric::Special(Kopemon* kopemon){
  string texto = ""+name+" used Thunder Wave. "+kopemon->getNombre()+" is Paralyzed!";
  if (ppEspecial!=0) {
    kopemon->setStatus("Paralyzed");
    ppEspecial--;
  }else{
    texto = ""+name+" failed to use Thunder Wave";
  }
  return texto;
}

string Electric::Normal(Kopemon* kopemon){
  int ataque = normal->getDamage();
  string texto = ""+name+" used "+normal->getName()+".";

  if (typeid(*kopemon) == typeid(Water)) {
    ataque=ataque*2;
    texto+=" Its Super Effective!";
  }else if (typeid(*kopemon) == typeid(Grass)) {
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

bool Electric::Accuracy(int accuracy){
  bool hit=true;
  srand (time(NULL));
  int random=rand() %100 + 1;
  if (accuracy < random) {
    hit=false;
  }
  return hit;
}

bool Electric::Paralyzed(string status){
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

Electric::~Electric(){
  delete normal;
}
