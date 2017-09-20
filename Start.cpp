#include "Kopemon.h"
#include "Fire.h"
#include "Grass.h"
#include "Electric.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include "Scanner.h"
#include "Material.h"
#include "Element.h"
#include "Stone.h"
#include "Object.h"
#include "Animal.h"
#include <ncurses.h>
#include "Start.h"
#include <string>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <typeinfo>
#define maxX 150
#define maxY 38

using namespace std;

void Start::run(){
  vector<Kopemon*> kopemons=load();
  vector<Element*> elements=fillElements();
  vector<Animal*> animals=fillAnimals();
  vector<Stone*> stones;
  //stones.push_back(new Stone("Fire Stone", "Red"));
  initscr();
  noecho();
  cbreak();
  start_color();
  kopemons=title();
  string piedra="";
  if (kopemons.size()==0) {
    piedra=inicio();
    Kopemon* veev=new Kopemon("Veev", 60);
    kopemons.push_back(veev);
    explicacion(piedra);
    string nombre="";
    if (piedra=="Water") {
      stones.push_back(new Stone("Water Stone", "Blue"));
    }else if(piedra=="Electric"){
      stones.push_back(new Stone("Thunder Stone", "Yellow"));
    }else{
      stones.push_back(new Stone("Fire Stone", "Red"));
    }
  }


  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_MAGENTA);

  //Fusion Lab
  Scanner fusion("./Dibujos/Fusion.txt");
  attron(COLOR_PAIR(4));
  attron(A_BOLD);
  fusion.print(1,maxX/4);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(4));

  //Create Left Window
  WINDOW* left=newwin(maxY/2+6,55, 12, 2);
  int a=(int)' ';
  wbkgd(left,COLOR_PAIR(5));
  Scanner Material1("./Dibujos/Material1.txt");

  //Create Right Window
  WINDOW* right=newwin(maxY/2+6,55, 12, 93);
  wbkgd(right,COLOR_PAIR(5));
  Scanner Material2("./Dibujos/Material2.txt");
  Material2.wprint(right,1,4);

  //Center Piece
  Scanner Fuse("./Dibujos/Fuse.txt");
  attron(COLOR_PAIR(4));
  Fuse.print(15,63);
  attroff(COLOR_PAIR(4));
  refresh();
  wrefresh(left);
  wrefresh(right);
  keypad(left, true);
  keypad(right, true);

  //Empieza las fusiones
  while(true) {
    Material2.wprint(right,1,4);
    wrefresh(right);
    Material1.wprint(left,1,5);

    Object* izquierda;
    Object* derecha;
    Object* nuevo;

//Elegir Material de la Izquierda-----------------------------------------------
    mvwprintw(left, 8, 5, "Which type of material are you going to use?");
    string choices[4] = {"Element", "Animal", "Kopemon", "Stone"};
    int choice=0;
    int seleccion=0;

    //Seleccion de Material
    while (choice!=10) {
      for (size_t i = 0; i < 4; i++) {
        if (i==seleccion)
          wattron(left, A_REVERSE);
            mvwprintw(left, i+10, 5, choices[i].c_str());
          wattroff(left, A_REVERSE);
        }
      choice=wgetch(left);

      switch (choice) {
        case KEY_UP:{
          seleccion--;
          if (seleccion<0) {
            seleccion=0;
          }
        }break;

        case KEY_DOWN:{
          seleccion++;
          if (seleccion>3) {
            seleccion=3;
          }
        }break;

        default:
          break;
      }
    }

    //seleccion de elements
    if (seleccion==0) {
      choice = 0;
      seleccion=0;
      mvwprintw(left, 15, 5, "Elements");
      while (choice!=10) {
        for (size_t i = 0; i < elements.size(); i++) {
          if (i==seleccion)
            wattron(left, A_REVERSE);
              mvwprintw(left, i+16, 5, elements.at(i)->show().c_str());
            wattroff(left, A_REVERSE);
          }
        choice=wgetch(left);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>elements.size()-1) {
              seleccion=elements.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      izquierda=elements.at(seleccion);

    //seleccion de animals
    }else if(seleccion==1){
      choice = 0;
      seleccion=0;
      mvwprintw(left, 15, 5, "Animals");
      while (choice!=10) {
        for (size_t i = 0; i < animals.size(); i++) {
          if (i==seleccion)
            wattron(left, A_REVERSE);
              mvwprintw(left, i+16, 5, animals.at(i)->getNombre().c_str());
            wattroff(left, A_REVERSE);
          }
        choice=wgetch(left);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>animals.size()-1) {
              seleccion=animals.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      izquierda=animals.at(seleccion);

    //seleccion de Kopemons
    }else if(seleccion==2){
      mvwprintw(left, 15, 5, "Kopemons");
      choice = 0;
      seleccion=0;
      while (choice!=10) {
        for (size_t i = 0; i < kopemons.size(); i++) {
          if (i<8){
            if(i==seleccion)
            wattron(left, A_REVERSE);
              mvwprintw(left, i+16, 5, kopemons.at(i)->getNombre().c_str());
            wattroff(left, A_REVERSE);
          }else{
            if(i==seleccion)
            wattron(left, A_REVERSE);
              mvwprintw(left, i+8, 20, kopemons.at(i)->getNombre().c_str());
            wattroff(left, A_REVERSE);
          }
        }
        choice=wgetch(left);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>kopemons.size()-1) {
              seleccion=kopemons.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      izquierda=kopemons.at(seleccion);

      //seleccion de Stones
    }else{
      mvwprintw(left, 15, 5, "Stones");
      choice = 0;
      seleccion=0;
      while (choice!=10) {
        for (size_t i = 0; i < stones.size(); i++) {
          if (i==seleccion)
            wattron(left, A_REVERSE);
              mvwprintw(left, i+16, 5, stones.at(i)->show().c_str());
            wattroff(left, A_REVERSE);
          }
        choice=wgetch(left);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>stones.size()-1) {
              seleccion=stones.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      izquierda=stones.at(seleccion);
    }
//------------------------------------------------------------------------------

//Elegir Material de la Derecha-----------------------------------------------
    mvwprintw(right, 8, 5, "Which type of material are you going to use?");
    string choicess[4] = {"Element", "Animal", "Kopemon", "Stone"};
    choice=0;
    seleccion=0;

    //Seleccion de Material
    while (choice!=10) {
      for (size_t i = 0; i < 4; i++) {
        if (i==seleccion)
          wattron(right, A_REVERSE);
            mvwprintw(right, i+10, 5, choicess[i].c_str());
          wattroff(right, A_REVERSE);
        }
      choice=wgetch(right);

      switch (choice) {
        case KEY_UP:{
          seleccion--;
          if (seleccion<0) {
            seleccion=0;
          }
        }break;

        case KEY_DOWN:{
          seleccion++;
          if (seleccion>3) {
            seleccion=3;
          }
        }break;

        default:
          break;
      }
    }

    //seleccion de elements
    if (seleccion==0) {
      choice = 0;
      seleccion=0;
      mvwprintw(right, 15, 5, "Elements");
      while (choice!=10) {
        for (size_t i = 0; i < elements.size(); i++) {
          if (i==seleccion)
            wattron(right, A_REVERSE);
              mvwprintw(right, i+16, 5, elements.at(i)->show().c_str());
            wattroff(right, A_REVERSE);
          }
        choice=wgetch(right);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>elements.size()-1) {
              seleccion=elements.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      derecha=elements.at(seleccion);

    //seleccion de animals
    }else if(seleccion==1){
      choice = 0;
      seleccion=0;
      mvwprintw(right, 15, 5, "Animals");
      while (choice!=10) {
        for (size_t i = 0; i < animals.size(); i++) {
          if (i==seleccion)
            wattron(right, A_REVERSE);
              mvwprintw(right, i+16, 5, animals.at(i)->getNombre().c_str());
            wattroff(right, A_REVERSE);
          }
        choice=wgetch(right);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>animals.size()-1) {
              seleccion=animals.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      derecha=animals.at(seleccion);

    //seleccion de Kopemons
    }else if(seleccion==2){
      mvwprintw(right, 15, 5, "Kopemons");
      choice = 0;
      seleccion=0;
      while (choice!=10) {
        for (size_t i = 0; i < kopemons.size(); i++) {
          if (i<8){
            if(i==seleccion)
            wattron(right, A_REVERSE);
              mvwprintw(right, i+16, 5, kopemons.at(i)->getNombre().c_str());
            wattroff(right, A_REVERSE);
          }else{
            if(i==seleccion)
            wattron(right, A_REVERSE);
              mvwprintw(right, i+8, 20, kopemons.at(i)->getNombre().c_str());
            wattroff(right, A_REVERSE);
          }
        }
        choice=wgetch(right);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>kopemons.size()-1) {
              seleccion=kopemons.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      derecha=kopemons.at(seleccion);

      //seleccion de Stones
    }else{
      mvwprintw(right, 15, 5, "Stones");
      choice = 0;
      seleccion=0;
      while (choice!=10) {
        for (size_t i = 0; i < stones.size(); i++) {
          if (i==seleccion)
            wattron(right, A_REVERSE);
              mvwprintw(right, i+16, 5, stones.at(i)->show().c_str());
            wattroff(right, A_REVERSE);
          }
        choice=wgetch(right);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<0) {
              seleccion=0;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>stones.size()-1) {
              seleccion=stones.size()-1;
            }
          }break;

          default:
            break;
        }
      }
      derecha=stones.at(seleccion);
    }
//------------------------------------------------------------------------------
    Object* creacion=*izquierda+derecha;
    string nombre;
    bool repetido=false;

    //Object Fire
    if (typeid(*creacion)==typeid(Fire)) {
      nombre=dynamic_cast<Fire*>(creacion)->getNombre();
      for (int i = 0; i < kopemons.size(); i++) {
        if (nombre==kopemons.at(i)->getNombre()) {
          repetido=true;
        }
      }
      if (!repetido) {
        kopemons.push_back(dynamic_cast<Fire*>(*izquierda+derecha));
      }
    }

    if (typeid(*creacion)==typeid(Water)) {
      nombre=dynamic_cast<Water*>(creacion)->getNombre();
      for (int i = 0; i < kopemons.size(); i++) {
        if (nombre==kopemons.at(i)->getNombre()) {
          repetido=true;
        }
      }
      if (!repetido) {
        kopemons.push_back(dynamic_cast<Water*>(*izquierda+derecha));
      }
    }

    if (typeid(*creacion)==typeid(Electric)) {
      nombre=dynamic_cast<Electric*>(creacion)->getNombre();
      for (int i = 0; i < kopemons.size(); i++) {
        if (nombre==kopemons.at(i)->getNombre()) {
          repetido=true;
        }
      }
      if (!repetido) {
        kopemons.push_back(dynamic_cast<Electric*>(*izquierda+derecha));
      }
    }

    if (typeid(*creacion)==typeid(Grass)) {
      nombre=dynamic_cast<Grass*>(creacion)->getNombre();
      for (int i = 0; i < kopemons.size(); i++) {
        if (nombre==kopemons.at(i)->getNombre()) {
          repetido=true;
        }
      }
      if (!repetido) {
        kopemons.push_back(dynamic_cast<Grass*>(*izquierda+derecha));
      }
    }

    if (typeid(*creacion)==typeid(Stone)) {
      nombre=dynamic_cast<Stone*>(creacion)->show();
      for (int i = 0; i < stones.size(); i++) {
        if (nombre==stones.at(i)->show()) {
          repetido=true;
        }
      }
      if (!repetido) {
        stones.push_back(dynamic_cast<Stone*>(*izquierda+derecha));
      }
    }

    delete creacion;
    refresh();
    wrefresh(left);
//    getch();
    werase(left);
    werase(right);
//    getch();
  }//End of while

  //Pelea

  /*Kopemon** team1=new Kopemon*[3];
  team1[0]=kopemons.at(0);
  team1[1]=kopemons.at(1);
  team1[2]=kopemons.at(2);

  cout<<team1[0]->getNombre()<<endl;
  cout<<team1[1]->getNombre()<<endl;
  cout<<team1[2]->getNombre()<<endl;*/


  getch();
  endwin();
}

vector<Kopemon*> Start::load(){
  vector<Kopemon*> kopemons;
  ifstream load("Log.txt");
  if (load.is_open()) {
    string line;
    while (getline(load, line)) {
      if (line=="Kipachu") {
        kopemons.push_back(new Electric(new Offensive(50, 95, "Thundershock"), "Kipachu", 90));
      }
      if (line=="Riachu") {
        kopemons.push_back(new Electric(new Offensive(70, 70, "Thunder"), "Riachu", 110));
      }
      if (line=="Marchander") {
        kopemons.push_back(new Fire(new Offensive(50, 90, "Ember"), new Offensive(100, 100, "Lava Plume"), "Marchander", 90));
      }
      if (line=="Marcheleon") {
        kopemons.push_back(new Fire(new Offensive(60, 80, "Fire Spin"), new Offensive(110, 100, "Flamethrower"), "Marcheleon", 100));
      }
      if (line=="Marchizard") {
        kopemons.push_back(new Fire(new Offensive(70, 75, "Fireblast"), new Offensive(110, 100, "Blastburn"), "Marchizard", 120));
      }
      if (line=="Escuirtol") {
        kopemons.push_back(new Water(new PowerUp(30, "Bubble"), new Offensive(50, 90, "Water Gun"), "Escuirtol", 90));
      }
      if (line=="Guarturtol") {
        kopemons.push_back(new Water(new PowerUp(35, "Bubblebeam"), new Offensive(60, 85, "Surf"), "Guarturtol", 90));
      }
      if (line=="Vlazztois") {
        kopemons.push_back(new Water(new PowerUp(45, "Brine"), new Offensive(70, 75, "Hydro Pump"), "Vlazztois", 90));
      }
      if (line=="Sulsabaur") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(50, 90, "Absorb"), "Sulsabaur", 90));
      }
      if (line=="Ivybaur") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(60, 85, "Mega Drain"), "Ivybaur", 90));
      }
      if (line=="Nevabaur") {
        kopemons.push_back(new Grass(new PowerUp(45, "Ingrain"), new Offensive(70, 75, "Giga Drain"), "Nevabaur", 90));
      }
      if (line=="Veev") {
        kopemons.push_back(new Kopemon("Veev", 60));
      }
      if (line=="Zapeon") {
        kopemons.push_back(new Electric(new Offensive(65, 80, "Thunderbolt"), "Zapeon", 100));
      }
      if (line=="Blazeon") {
        kopemons.push_back(new Fire(new Offensive(65, 80, "Flame Charge"), new Offensive(110, 100, "Fire Blitz"), "Blazeon", 100));
      }
      if (line=="Aqueon") {
        kopemons.push_back(new Water(new PowerUp(35, "Water Pulse"), new Offensive(65, 80, "Scald"), "Aqueon", 90));
      }
      if (line=="Vineon") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(65, 80, "Magical Leaf"), "Vineon", 90));
      }
    }
    load.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  return kopemons;
}

void Start::explicacion(string stone){
  //Scanners y colores
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  Scanner* veev=new Scanner("./Dibujos/Veev.txt");
  Scanner* tutorial=new Scanner("./Dibujos/Tutorial.txt");
  Scanner* procedure=new Scanner("./Dibujos/Procedure.txt");

  //Print Veev
  attron(COLOR_PAIR(3));
  attron(A_BOLD);
  veev->print(0,0);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(3));

  //Print Tutorial Title
  attron(COLOR_PAIR(2));
  attron(A_BOLD);
  tutorial->print(0, maxX/2+18);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(2));

  //Text Box
  WINDOW* text = newwin(maxY-11, maxX/2+3, 7, maxX/2-3);
  box(text,0,0);
  wattron(text, COLOR_PAIR(2));
  wattron(text, A_BOLD);
  mvwprintw(text,2,2, "Oh I see you have Veev and a %s stone. Now you will learn how to fuse", stone.c_str());
  mvwprintw(text,3,2, "materials to get different Kopemons. Once you are in the Fusion Lab, you");
  mvwprintw(text,4,2, "will first hae to choose a type of material (A Kopemon, an element, a stone");
  mvwprintw(text,5,2, "a stone, etc.), then the material from that type (Kopemon=Veev).");
  wattroff(text, COLOR_PAIR(2));
  wattroff(text, A_BOLD);
  refresh();
  wrefresh(text);
  usleep(5000000);

  //Print Procedure
  wattron(text, COLOR_PAIR(1));
  wattron(text, A_BOLD);
  procedure->wprint(text, 7, 10);
  wattroff(text, A_BOLD);
  wattroff(text, COLOR_PAIR(1));

  //Text Box
  refresh();
  wrefresh(text);
  usleep(5000000);
  wattron(text, COLOR_PAIR(2));
  wattron(text, A_BOLD);
  mvwprintw(text,18,2, "You will repeat this process for the second Material and initiate your");
  mvwprintw(text,19,2, "Fusion. Dont worry if you mess up and pick up wrong material combination,");
  mvwprintw(text,20,2, "it will not affect any future creations. Every now and then you will re-");
  mvwprintw(text,21,2, "ceive new materials for you to work with.");
  wattroff(text, COLOR_PAIR(2));
  wattroff(text, A_BOLD);
  refresh();
  wrefresh(text);
  usleep(5000000);
  wattron(text, COLOR_PAIR(1));
  wattron(text, A_BOLD);
  mvwprintw(text,23,2, "Now go and make some Kopemons!");
  mvwprintw(text,25,2, "[Press Enter]");
  wattroff(text, COLOR_PAIR(1));
  wattroff(text, A_BOLD);
  refresh();
  wrefresh(text);
  int enter;
  do {
    enter=wgetch(text);
  } while(enter!=10);

  //Liberadores de espacio;
  werase(text);
  delwin(text);
  delete veev;
  delete tutorial;
  delete procedure;
  clear();
}

vector<Kopemon*> Start::title(){
  //Variables, Scanners y colores
  vector<Kopemon*> prueba;
  box(stdscr,0,0);
  string line;
  int move=17;
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  Scanner* title=new Scanner("./Dibujos/Kopemon.txt");
  ifstream ball("./Dibujos/pokeball.txt");


  //Imprimir Titulo
  attron(COLOR_PAIR(1));
  attron(A_BOLD);
  title->print(1, 40);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(1));

  //Imprimir pokeball
  if (ball.is_open()) {
    while (getline(ball,line)) {
      attron(A_BOLD);
      if (move<=20) {
        attron(COLOR_PAIR(2));
        mvprintw(move,68, "%s",line.c_str());
        attroff(COLOR_PAIR(2));
      }else{
        mvprintw(move,68, "%s",line.c_str());
      }
      move++;
      attroff(A_BOLD);
    }
    ball.close();
  }else{
    printw("File could not open");
  }

  //Atributos
  attron(COLOR_PAIR(2));
  attron(A_BOLD);
  mvprintw(15, 68, "Crimson  Version");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(2));
  attron(A_BOLD);
  mvprintw(maxY-3, 62, "2017 THE KOPEMON GAME COMPANY");
  attroff(A_BOLD);
  refresh();

  //Choices
  WINDOW* menu=newwin(6, 28, 27, 62);
  keypad(menu, true);
  string choices[3] = {"New File", "Load File", "Exit Game"};
  int choice=0;
  int seleccion=0;
  int a=(int)' ';
  box(menu,a,a);

  while (choice!=10) {
    for (size_t i = 0; i < 3; i++) {
      if (i==seleccion)
        wattron(menu, A_REVERSE);
          mvwprintw(menu, i+1, 1, choices[i].c_str());
        wattroff(menu, A_REVERSE);
      }
    choice=wgetch(menu);

    switch (choice) {
      case KEY_UP:{
        seleccion--;
        if (seleccion<0) {
          seleccion=0;
        }
      }break;

      case KEY_DOWN:{
        seleccion++;
        if (seleccion>2) {
          seleccion=2;
        }
      }break;

      default:
        break;
    }
  }
  if (seleccion==0 ) {
    printw("new Game");
  }

  if (seleccion==1){
    prueba=load();
  }

  if (seleccion==2) {

  }

  delete title;
  werase(menu);
  delwin(menu);
  clear();
  refresh();
  return prueba;
}

string Start::inicio(){
  //Scanners y colores
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  Scanner* maple=new Scanner("./Dibujos/Maple.txt");
  Scanner* kipachu=new Scanner("./Dibujos/Kipachu.txt");

  //Imprime al Professor Maple
  maple->print(0,45);

  //Ventana de texto
  WINDOW* texto=newwin(6, maxX-12, maxY-8,5);
  box(texto,0,0);
  refresh();
  wrefresh(texto);

  //Texto Inicial
  mvwprintw(texto, 1,2, "Welcome to the Kopemon World. My name is Professor Maple. This world is inhabited far and wide by creatures called Kopemons. Here is ");
  mvwprintw(texto, 2,2, "one of them: It is a Kipachu.");
  refresh();
  wrefresh(texto);
  usleep(5000000);

  //Impresion de Kipachu
  attron(COLOR_PAIR(1));
  attron(A_BOLD);
  kipachu->print(14,17);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(1));
  refresh();
  usleep(1000000);
  mvprintw(13,22,"Ki-pa-chu!");
  refresh();

  //Segundo Texto
  mvwprintw(texto, 4,1, "[Press enter]");
  int enter=0;
  do {
    enter=wgetch(texto);
  } while(enter!=10);
  wclear(texto);
  box(texto,0,0);
  mvwprintw(texto, 1,2, "Your mission is to create all possible Kopemons so you can compete. You will need to combine elements with Kopemons to creat new Kope- ");
  mvwprintw(texto, 2,2, "mons. Since I'm a good fellow, I'm going to give you the basic Kopemon 'Veev', and a special stone to help you start your adventure. ");
  mvwprintw(texto, 4,2, "[Press enter]");
  refresh();
  wrefresh(texto);
  enter=0;
  do {
    enter=wgetch(texto);
  } while(enter!=10);

  //Ventana de eleccion
  WINDOW* menu=newwin(8, 28, maxY/4, maxX-maxX/3-10);
  keypad(menu, true);
  string choices[3] = {"Fire", "Water", "Electric"};
  int choice=0;
  int seleccion=0;
  box(menu,0,0);
  mvwprintw(menu, 1,1, "Which stone do you want?" );
  while (choice!=10) {
    for (size_t i = 0; i < 3; i++) {
      if (i==seleccion)
        wattron(menu, A_REVERSE);
          mvwprintw(menu, i+3, 1, choices[i].c_str());
        wattroff(menu, A_REVERSE);
      }
    choice=wgetch(menu);

    switch (choice) {
      case KEY_UP:{
        seleccion--;
        if (seleccion<0) {
          seleccion=0;
        }
      }break;

      case KEY_DOWN:{
        seleccion++;
        if (seleccion>2) {
          seleccion=2;
        }
      }break;

      default:
        break;
    }
  }

  //Vaciar memoria y salir
  werase(texto);
  werase(menu);
  delwin(texto);
  delwin(menu);
  delete maple;
  delete kipachu;
  clear();
  refresh();
  string eleccion=choices[seleccion];
  return eleccion;
}

vector<Animal*> Start::fillAnimals(){
  vector<Animal*> animals;
  animals.push_back(new Animal("Lizard", "Reptile"));
  animals.push_back(new Animal("Frog", "Amphibian"));
  animals.push_back(new Animal("Turtle", "Reptile"));
  animals.push_back(new Animal("Rat", "Rodent"));
  return animals;
}

vector<Element*> Start::fillElements(){
  vector<Element*> elements;
  elements.push_back(new Element("Fire", 400));
  elements.push_back(new Element("Water", 1));
  elements.push_back(new Element("Air", 25));
  elements.push_back(new Element("Earth", 50));
  return elements;
}

Start::~Start(){
}
