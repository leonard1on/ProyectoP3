#include "Material.h"
#include "Element.h"
#include <string>
#include <ncurses.h>
using namespace std;

Element::Element(string pTipo, int temp) : Material(){
  tipo=pTipo;
  heatness=temp;
  descripcion="With "+tipo+" you can create certain stones or Kopemons";
}

string Element::show(){
  return tipo;
}

string Element::toString(){
  return "Element type:"+tipo+" Element\nHeatness: "+to_string(heatness)+"°C\nUse: "+descripcion;
}

string Element::help(){
  return descripcion;
}

void Element::printString(int y, int x){
  mvprintw(y,x, "Stone Name: %s", tipo.c_str());
  mvprintw(y+1,x, "Heatness: %d", heatness);
  mvprintw(y+2,x, "Use: %s", descripcion.c_str());
}

void Element::wprintString(WINDOW* ventana, int y, int x){
  mvwprintw(ventana,y,x, "Stone Name: %s", tipo.c_str());
  mvwprintw(ventana,y+1,x, "Heatness: %d", heatness);
  mvwprintw(ventana,y+2,x, "Use: %s", descripcion.c_str());
}

Element::~Element(){
}
