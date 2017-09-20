#include "Attack.h"

Attack::Attack(string pName){
  name=pName;
}

string Attack::getName(){
  return name;
}

void Attack::setName(string pName){
  name=pName;
}

Attack::~Attack(){

}
