#include "Material.h"
#include "Stone.h"
#include <string>
#include <ncurses.h>
using namespace std;

Stone::Stone(string pNombre, string pColor) : Material(){
  nombre=pNombre;
  color=pColor;
  if (pNombre=="Thunder Stone") {
    descripcion="Stone used for electric transformations";
  }else if(pNombre=="Water Stone"){
    descripcion="Stone used for acuatic transformations";
  }else if(pNombre=="Fire Stone"){
    descripcion="Stone used for fire transformations";
  }else{
    descripcion="Stone used for grass transformations";
  }
}

string Stone::show(){
  return nombre;
}

string Stone::toString(){
  return "Stone Name: "+nombre+"\nColor: "+color+"\nUse: "+descripcion;
}

string Stone::help(){
  return descripcion;
}

void Stone::printString(int y, int x){
  mvprintw(y,x, "Stone Name: %s", nombre.c_str());
  mvprintw(y+1,x, "Color: %s", color.c_str());
  mvprintw(y+2,x, "Use: %s", descripcion.c_str());
}

void Stone::wprintString(WINDOW* ventana, int y, int x){
  mvwprintw(ventana, y,x, "Stone Name: %s", nombre.c_str());
  mvwprintw(ventana, y+1,x, "Color: %s", color.c_str());
  mvwprintw(ventana, y+2,x, "Use: %s", descripcion.c_str());
}

Stone::~Stone(){
}
