#include "Animal.h"
#include "Object.h"
#include <string>
using namespace std;

Animal::Animal(string pName, string pTipo) : Object(){
  name=pName;
  tipo=pTipo;
}

string Animal::getNombre(){
  return name;
}

string Animal::getTipo(){
  return tipo;
}

void Animal::setNombre(string pNombre){
  name=pNombre;
}

void Animal::setTipo(string pTipo){
  tipo=pTipo;
}

Animal::~Animal(){

}
