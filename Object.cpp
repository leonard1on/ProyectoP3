#include "Object.h"
#include <typeinfo>
#include "Material.h"
#include "Element.h"
#include "Stone.h"
#include "Kopemon.h"
#include "Electric.h"
#include "Water.h"
#include "Grass.h"
#include "Fire.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include "Animal.h"
#include <iostream>
using namespace std;
Object::Object(){

}

Object* Object::operator+(Object* object){
  Object* creacion=new Object();
  //Stone + Kopemons
  if (typeid(*this)==typeid(Stone)) {
    //Riachu 1
    if (typeid(*object)==typeid(Electric)){
      if (dynamic_cast<Stone*>(this)->show()=="Thunder Stone" && dynamic_cast<Electric*>(object)->getNombre()=="Kipachu") {
        creacion=new Electric(new Offensive(70, 70, "Thunder"), "Riachu", 110);
      }
    }
    //Marchizard 1
    if (typeid(*object)==typeid(Fire)) {
      if (dynamic_cast<Stone*>(this)->show()=="Fire Stone" && dynamic_cast<Fire*>(object)->getNombre()=="Marcheleon") {
        creacion=new Fire(new Offensive(70, 75, "Fireblast"), new Offensive(110, 100, "Blastburn"), "Marchizard", 120);
      }
    }
    //Vlazztois 1
    if (typeid(*object)==typeid(Water)) {
      if (dynamic_cast<Stone*>(this)->show()=="Water Stone" && dynamic_cast<Water*>(object)->getNombre()=="Guarturtol") {
        creacion=new Water(new PowerUp(45, "Brine"), new Offensive(70, 75, "Hydro Pump"), "Vlazztois", 90);
      }
    }
    //Nevabaur 1
    if (typeid(*object)==typeid(Grass)) {
      if (dynamic_cast<Stone*>(this)->show()=="Grass Stone" && dynamic_cast<Grass*>(object)->getNombre()=="Ivybaur") {
        creacion=new Grass(new PowerUp(45, "Ingrain"), new Offensive(70, 75, "Giga Drain"), "Nevabaur", 90);
      }
    }
    //Vineon, Zapeon, Aqueon and Blazeon 1
    if (typeid(*object)==typeid(Kopemon)) {
      if (dynamic_cast<Kopemon*>(object)->getNombre()=="Veev") {

        if (dynamic_cast<Stone*>(this)->show()=="Leaf Stone") {
          creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(65, 80, "Magical Leaf"), "Vineon", 90);
        }

        if (dynamic_cast<Stone*>(this)->show()=="Thunder Stone") {
          creacion=new Electric(new Offensive(65, 80, "Thunderbolt"), "Zapeon", 100);
        }

        if (dynamic_cast<Stone*>(this)->show()=="Water Stone") {
          creacion=new Water(new PowerUp(35, "Water Pulse"), new Offensive(65, 80, "Scald"), "Aqueon", 90);
        }

        if (dynamic_cast<Stone*>(this)->show()=="Fire Stone") {
          creacion=new Fire(new Offensive(65, 80, "Flame Charge"), new Offensive(110, 100, "Fire Blitz"), "Blazeon", 100);
        }

      }

    }


  //Element + Kopemon
  }else if (typeid(*this)==typeid(Element)) {
    //Marcheleon 1
    if (typeid(*object)==typeid(Fire)) {
      if (dynamic_cast<Element*>(this)->show()=="Fire" && dynamic_cast<Fire*>(object)->getNombre()=="Marchander") {
        creacion=new Fire(new Offensive(60, 80, "Fire Spin"), new Offensive(110, 100, "Flamethrower"), "Marcheleon", 100);
      }
    }
    //Guarturtol 1
    if (typeid(*object)==typeid(Water)) {
      if (dynamic_cast<Element*>(this)->show()=="Water" && dynamic_cast<Water*>(object)->getNombre()=="Escuirtol") {
        creacion=new Water(new PowerUp(35, "Bubblebeam"), new Offensive(60, 85, "Surf"), "Guarturtol", 90);
      }
    }
    //Ivybaur 1
    if (typeid(*object)==typeid(Grass)) {
      if (dynamic_cast<Element*>(this)->show()=="Earth" && dynamic_cast<Grass*>(object)->getNombre()=="Sulsabaur") {
        creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(60, 85, "Mega Drain"), "Ivybaur", 90);
      }
    }


    //Element + Element
    if (typeid(*object)==typeid(Element)) {
      //Fire Stone
      if (dynamic_cast<Element*>(this)->show()=="Fire" && dynamic_cast<Element*>(object)->show()=="Earth") {
        creacion=new Stone("Fire Stone", "Red");
      }
      //Water Stone
      if (dynamic_cast<Element*>(this)->show()=="Water" && dynamic_cast<Element*>(object)->show()=="Earth") {
        creacion=new Stone("Water Stone", "Blue");
      }
      //Thunder Stone
      if (dynamic_cast<Element*>(this)->show()=="Air" && dynamic_cast<Element*>(object)->show()=="Earth") {
        creacion=new Stone("Thunder Stone", "Yellow");
      }
      //Leaf Stone
      if (dynamic_cast<Element*>(this)->show()=="Earth" && dynamic_cast<Element*>(object)->show()=="Earth") {
        creacion=new Stone("Leaf Stone", "Green");
      }
    }

    //Element+Animal
    if (typeid(*object)==typeid(Animal)) {
      //Marchander 2
      if (dynamic_cast<Animal*>(object)->getNombre()=="Lizard" && dynamic_cast<Element*>(this)->show()=="Fire"){
        creacion=new Fire(new Offensive(50, 90, "Ember"), new Offensive(100, 100, "Lava Plume"), "Marchander", 90);
      }
      //Kipachu 2
      if (dynamic_cast<Animal*>(object)->getNombre()=="Rat" && dynamic_cast<Element*>(this)->show()=="Air"){
        creacion=new Electric(new Offensive(50, 95, "Thundershock"), "Kipachu", 90);
      }
      //Escuirtol 2
      if (dynamic_cast<Animal*>(object)->getNombre()=="Turtle" && dynamic_cast<Element*>(this)->show()=="Water"){
        creacion=new Water(new PowerUp(30, "Bubble"), new Offensive(50, 90, "Water Gun"), "Escuirtol", 90);
      }
      //Sulsabaur 2
      if (dynamic_cast<Animal*>(object)->getNombre()=="Frog" && dynamic_cast<Element*>(this)->show()=="Earth"){
        creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(50, 90, "Absorb"), "Sulsabaur", 90);
      }
    }


  //Electric + Stone
  }else if(typeid(*this)==typeid(Electric)){
    //Riachu 2
    if (typeid(*object)==typeid(Stone)) {
      if (dynamic_cast<Electric*>(this)->getNombre()=="Kipachu" && dynamic_cast<Stone*>(object)->show()=="Thunder Stone"){
        creacion=new Electric(new Offensive(70, 70, "Thunder"), "Riachu", 110);
      }
    }


  //Fire + Stone   Fire + Element
  }else if(typeid(*this)==typeid(Fire)){
    //Marchizard 2
    if (typeid(*object)==typeid(Stone)) {
      if (dynamic_cast<Fire*>(this)->getNombre()=="Marcheleon" && dynamic_cast<Stone*>(object)->show()=="Fire Stone"){
        creacion=new Fire(new Offensive(70, 75, "Fireblast"), new Offensive(110, 100, "Blastburn"), "Marchizard", 120);
      }
    }
    //Marcheleon 2
    if (typeid(*object)==typeid(Element)) {
      if (dynamic_cast<Fire*>(this)->getNombre()=="Marchander" && dynamic_cast<Element*>(object)->show()=="Fire"){
        creacion=new Fire(new Offensive(60, 80, "Fire Spin"), new Offensive(110, 100, "Flamethrower"), "Marcheleon", 100);
      }
    }


  //Water + Stone  Water + Element
  }else if(typeid(*this)==typeid(Water)){
    //Vlazztois 2
    if (typeid(*object)==typeid(Stone)) {
      if (dynamic_cast<Water*>(this)->getNombre()=="Guarturtol" && dynamic_cast<Stone*>(object)->show()=="Water Stone"){
        creacion=new Water(new PowerUp(45, "Brine"), new Offensive(70, 75, "Hydro Pump"), "Vlazztois", 90);
      }
    }
    //Guarturtol 2
    if (typeid(*object)==typeid(Element)) {
      if (dynamic_cast<Water*>(this)->getNombre()=="Escuirtol" && dynamic_cast<Element*>(object)->show()=="Water"){
        creacion=new Water(new PowerUp(35, "Bubblebeam"), new Offensive(60, 85, "Surf"), "Guarturtol", 90);
      }
    }

  //Grass + Stone   Grass + Element
  }else if(typeid(*this)==typeid(Grass)){
    //Nevabaur 2
    if (typeid(*object)==typeid(Stone)) {
      if (dynamic_cast<Grass*>(this)->getNombre()=="Ivybaur" && dynamic_cast<Stone*>(object)->show()=="Leaf Stone"){
        creacion=new Grass(new PowerUp(45, "Ingrain"), new Offensive(70, 75, "Giga Drain"), "Nevabaur", 90);
      }
    }
    //Ivybaur 2
    if (typeid(*object)==typeid(Element)) {
      if (dynamic_cast<Grass*>(this)->getNombre()=="Sulsabaur" && dynamic_cast<Element*>(object)->show()=="Earth"){
        creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(60, 85, "Mega Drain"), "Ivybaur", 90);
      }
    }

  //Kopemon + Stone
  }else if (typeid(*this)==typeid(Kopemon)) {
    //Vineon, Zapeon, Aqueon and Blazeon 2
    if (typeid(*object)==typeid(Stone)) {
      if (dynamic_cast<Kopemon*>(this)->getNombre()=="Veev") {

        if (dynamic_cast<Stone*>(object)->show()=="Leaf Stone") {
          creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(65, 80, "Magical Leaf"), "Vineon", 90);
        }

        if (dynamic_cast<Stone*>(object)->show()=="Thunder Stone") {
          creacion=new Electric(new Offensive(65, 80, "Thunderbolt"), "Zapeon", 100);
        }

        if (dynamic_cast<Stone*>(object)->show()=="Water Stone") {
          creacion=new Water(new PowerUp(35, "Water Pulse"), new Offensive(65, 80, "Scald"), "Aqueon", 90);
        }

        if (dynamic_cast<Stone*>(object)->show()=="Fire Stone") {
          creacion=new Fire(new Offensive(65, 80, "Flame Charge"), new Offensive(110, 100, "Fire Blitz"), "Blazeon", 100);
        }
      }
    }


  //Animal + Element
  }else if(typeid(*this)==typeid(Animal)){

    if (typeid(*object)==typeid(Element)) {
      //Marchander 1
      if (dynamic_cast<Animal*>(this)->getNombre()=="Lizard" && dynamic_cast<Element*>(object)->show()=="Fire"){
        creacion=new Fire(new Offensive(50, 90, "Ember"), new Offensive(100, 100, "Lava Plume"), "Marchander", 90);
      }
      //Kipachu 1
      if (dynamic_cast<Animal*>(this)->getNombre()=="Rat" && dynamic_cast<Element*>(object)->show()=="Air"){
        creacion=new Electric(new Offensive(50, 95, "Thundershock"), "Kipachu", 90);
      }
      //Escuirtol 1
      if (dynamic_cast<Animal*>(this)->getNombre()=="Turtle" && dynamic_cast<Element*>(object)->show()=="Water"){
        creacion=new Water(new PowerUp(30, "Bubble"), new Offensive(50, 90, "Water Gun"), "Escuirtol", 90);
      }
      //Sulsabaur 1
      if (dynamic_cast<Animal*>(this)->getNombre()=="Frog" && dynamic_cast<Element*>(object)->show()=="Earth"){
        creacion=new Grass(new PowerUp(40, "Synthesis"), new Offensive(50, 90, "Absorb"), "Sulsabaur", 90);
      }
    }

  }

  return creacion;
}
Object::~Object(){

}
