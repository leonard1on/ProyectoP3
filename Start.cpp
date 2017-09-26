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
#include "Music.h"
#include "SoundFX.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <time.h>
#define maxX 150
#define maxY 38

using namespace std;

void Start::run(){
  vector<Kopemon*> kopemons;
  vector<Element*> elements=fillElements();
  vector<Animal*> animals=fillAnimals();
  vector<Stone*> stones;
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
  }
  SoundFX success("./SoundFX/Success.wav");
  //stones.push_back(new Stone("Fire Stone", "Red"));
  initscr();
  noecho();
  cbreak();
  start_color();
  kopemons=title();
  string piedra="";
  //NEW GAME
  if (kopemons.size()==20) {
  }else{
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
    }else{
      stones.push_back(new Stone("Fire Stone", "Red"));
    }

    int choice=0;
    int seleccion=0;
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);

    //Fusion Lab
    Music music("./Music/Fusion.wav");
    music.play();
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
    int salir=kopemons.size();

    //Empieza las fusiones
    while(salir!=16) {
      Material2.wprint(right,1,4);
      wrefresh(right);
      Material1.wprint(left,1,5);

      Object* izquierda;
      Object* derecha;
      Object* nuevo;

      //Elegir Material de la Izquierda-----------------------------------------------
      mvwprintw(left, 8, 5, "Which type of material are you going to use?");
      string choices[5] = {"Element", "Animal", "Kopemon", "Stone", "Leave"};
      choice=0;
      seleccion=0;

      //Seleccion de Material
      while (choice!=10) {
        for (size_t i = 0; i < 5; i++) {
          if(i<4){
            if (i==seleccion)
            wattron(left, A_REVERSE);
            mvwprintw(left, i+10, 5, choices[i].c_str());
            wattroff(left, A_REVERSE);
          }else{
            if (i==seleccion)
            wattron(left, A_REVERSE);
            mvwprintw(left, i+6, 20, choices[i].c_str());
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
            if (seleccion>4) {
              seleccion=4;
            }
          }break;

          default:
          break;
        }
      }
      if(seleccion!=4){
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

              case KEY_RIGHT:{
                seleccion+=8;
                if (seleccion>kopemons.size()-1) {
                  seleccion-=8;
                }
              }break;

              case KEY_LEFT:{
                seleccion-=8;
                if (seleccion<0) {
                  seleccion+=8;
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

              case KEY_RIGHT:{
                seleccion+=8;
                if (seleccion>kopemons.size()-1) {
                  seleccion-=8;
                }
              }break;

              case KEY_LEFT:{
                seleccion-=8;
                if (seleccion<0) {
                  seleccion+=8;
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
        string nombre="";
        bool repetido=false;
        move(20,0);
        clrtoeol();
        //Object Fire
        if (typeid(*creacion)==typeid(Fire)) {
          nombre=dynamic_cast<Fire*>(creacion)->getNombre();
          for (int i = 0; i < kopemons.size(); i++) {
            if (nombre==kopemons.at(i)->getNombre()) {
              repetido=true;
            }
          }
          if (!repetido) {
            success.play();
            attron(COLOR_PAIR(7));
            mvprintw(20,62, "You created a: '%s'   ", nombre.c_str());
            attroff(COLOR_PAIR(7));
            kopemons.push_back(dynamic_cast<Fire*>(*izquierda+derecha));
          }
        }
        //Object Water
        if (typeid(*creacion)==typeid(Water)) {
          nombre=dynamic_cast<Water*>(creacion)->getNombre();
          for (int i = 0; i < kopemons.size(); i++) {
            if (nombre==kopemons.at(i)->getNombre()) {
              repetido=true;
            }
          }
          if (!repetido) {
            success.play();
            attron(COLOR_PAIR(6));
            mvprintw(20,62, "You created a: '%s'   ", nombre.c_str());
            attroff(COLOR_PAIR(6));
            kopemons.push_back(dynamic_cast<Water*>(*izquierda+derecha));
          }
        }
        //Object Electric
        if (typeid(*creacion)==typeid(Electric)) {
          nombre=dynamic_cast<Electric*>(creacion)->getNombre();
          for (int i = 0; i < kopemons.size(); i++) {
            if (nombre==kopemons.at(i)->getNombre()) {
              repetido=true;
            }
          }
          if (!repetido) {
            success.play();
            attron(COLOR_PAIR(8));
            mvprintw(20,62, "You created a: '%s'   ", nombre.c_str());
            attroff(COLOR_PAIR(8));
            kopemons.push_back(dynamic_cast<Electric*>(*izquierda+derecha));
          }
        }
        //Object Grass
        if (typeid(*creacion)==typeid(Grass)) {
          nombre=dynamic_cast<Grass*>(creacion)->getNombre();
          for (int i = 0; i < kopemons.size(); i++) {
            if (nombre==kopemons.at(i)->getNombre()) {
              repetido=true;
            }
          }
          if (!repetido) {
            success.play();
            attron(COLOR_PAIR(4));
            mvprintw(20,62, "You created a: '%s'   ", nombre.c_str());
            attron(COLOR_PAIR(4));
            kopemons.push_back(dynamic_cast<Grass*>(*izquierda+derecha));
          }
        }
        //Object Stone
        if (typeid(*creacion)==typeid(Stone)) {
          nombre=dynamic_cast<Stone*>(creacion)->show();
          for (int i = 0; i < stones.size(); i++) {
            if (nombre==stones.at(i)->show()) {
              repetido=true;
            }
          }
          if (!repetido) {
            success.play();
            mvprintw(20,62, "You created a: '%s'   ", nombre.c_str());
            stones.push_back(dynamic_cast<Stone*>(*izquierda+derecha));
          }
        }


        delete creacion;
        salir=kopemons.size();
      }else{
        salir=16;
      }

      refresh();
      wrefresh(left);
      werase(left);
      werase(right);
      if (kopemons.size()==16) {
        Material2.wprint(right,1,4);
        wrefresh(right);
        Material1.wprint(left,1,5);
        mvprintw(24, 61, "You've created every Kopemon!");
        mvprintw(25, 67,       "Congratulations!");
        refresh();
        wrefresh(left);
        wrefresh(right);
        usleep(5000000);
      }

      ofstream salida("Log.txt");
      for (size_t i = 0; i < kopemons.size(); i++) {
        salida<<*kopemons.at(i);
      }

    }//End of while
    music.halt();
    delwin(left);
    delwin(right);
    clear();
    refresh();
    int ganar=0;
    //Pelea
    if (kopemons.size()==16) {
      ganar=battle(kopemons);
      if (ganar==2) {
        Music ending("./Music/Ending.wav");
        ending.play();
        mvprintw(maxY/2, maxX/3, "Thank you for playing Kopemon Crimson Version!");
        mvprintw(maxY/2+1, maxX/3, "You are a true Kopemon Trainer");
        refresh();
        usleep(5000000);
        ending.halt();
      }
    }
  }
  //End
  kopemons.clear();
  elements.clear();
  animals.clear();
  stones.clear();
  mvprintw(maxY/2+2, maxX/3, "The End");
  refresh();
  getch();
  endwin();
}

int Start::battle(vector<Kopemon*> kopemons){
  srand (time(NULL));
  vector<Kopemon*> team1;
  vector<Kopemon*> team2=Enemy();
  string location;

  //Music
  Music road("./Music/Road.wav");
  road.play();

  //Choose Kopemons Windows
  WINDOW* list = newwin(maxY-11, 25, 2, 4);
  keypad(list, true);
  refresh();
  wrefresh(list);

  //My Team
  WINDOW* team = newwin(5, maxX/3-6, 2, 31);
  wrefresh(team);

  //Choose your Kopemon Team
  while(team1.size()!=3){
    int choice=0;
    int seleccion=0;

    while (choice!=10) {
      for (size_t i = 0; i < kopemons.size(); i++) {
        if(i==seleccion)
        wattron(list, A_REVERSE);
        mvwprintw(list, i+5, 8, kopemons.at(i)->getNombre().c_str());
        wattroff(list, A_REVERSE);

        //Print All Titles and Kopemons
        location="./Dibujos/"+kopemons.at(seleccion)->getNombre()+".txt";
        Scanner kope(location);
        erase();
        kope.print(1, 78);
        refresh();
        box(list,0,0);
        box(team,0,0);
        mvwprintw(list, 2, 6,   "Create a Team!");
        mvwprintw(list, 3, 4, "Choose 3 Kopemons");
        mvwprintw(team, 1, 2, "My Team:");
        wrefresh(team);
      }
      choice=wgetch(list);

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

    //Kopemons to team
    team1.push_back(kopemons.at(seleccion));
    kopemons.erase(kopemons.begin()+seleccion);
    for (size_t i = 0; i < team1.size(); i++) {
      mvwprintw(team, 3, 2+(i*15), "%s", team1.at(i)->getNombre().c_str());
    }
    wrefresh(team);
    werase(list);
  }

  //Erase everything
  werase(list);
  werase(team);
  erase();
  delwin(list);
  delwin(team);
  refresh();
  road.halt();

  //New stage
  Music batalla("./Music/Battle.wav");
  batalla.play();
  usleep(400000);
  WINDOW* hud=newwin(8,46,maxY-16,0);
  WINDOW* hud2=newwin(8,46,1,88);
  WINDOW* options=newwin(8, maxX/2-16, maxY-16,17);
  keypad(options, true);
  WINDOW* texto=newwin(6, maxX-12, maxY-8,5);
  int a=(int)' ';
  int b=(int)'>';
  int c=(int)'<';
  int enemy=0;
  int resp;
  int salida=0;

  //Fill Screen before battle
  for (size_t i = 0; i < maxY; i+=3) {
    for (size_t j = 0; j < maxX; j+=3) {
      mvprintw(i,j,"#");
      mvprintw(i+1,j+1,"#");
      mvprintw(i+2,j+2,"#");
      usleep(5000);
      refresh();
    }
  }
  erase();
  refresh();
  mvwprintw(texto, 1, 3, "Battle Log:");
  mvwprintw(texto,3,3, "Trainer Red wants to battle you!" );

  //Moving Kopemon HUDS
  for (size_t i = 0; i < 87; i++) {
    werase(hud);
    werase(hud2);
    delwin(hud2);
    delwin(hud);
    erase();
    refresh();
    WINDOW* hud=newwin(8,46,maxY-16,i);
    WINDOW* hud2=newwin(8,46,2,88-i);
    wborder(hud, a, 0, a, 0, a, a, c, 0);
    wborder(hud2, 0, a, a, 0, a, a, 0, b);
    box(texto,0,0);
    wrefresh(hud);
    wrefresh(hud2);
    wrefresh(texto);
    usleep(30000);
  }
  string choices[4] = {"Normal Attack", "Special Attack", "Switch", "Help"};
  //Create HUD2 Information
  wborder(hud2, 0, a, a, 0, a, a, 0, b);
  mvwprintw(hud2, 1,15,"%s", team2.at(0)->getNombre().c_str());
  mvwprintw(hud2, 2,15,"%s", team2.at(0)->getStatus().c_str());
  mvwprintw(hud2, 3,20,":L 100");
  mvwprintw(hud2, 4,15,"HP: %d / %d", team2.at(0)->getHp(), team2.at(0)->getOriginalHp());
  for (size_t i = 1; i < 38; i++) {
    mvwprintw(hud2,5,i,"_");
  }
  for (size_t i = 1; i < 43; i++) {
    wattron(hud2, COLOR_PAIR(6));
    mvwprintw(hud2,6,i,"=");
    wattroff(hud2, COLOR_PAIR(6));
  }
  wrefresh(hud2);

  //Battle Start!!!!
  do {
    //Variables
    int choice=0;
    int seleccion=0;
    wborder(hud, a, 0, a, 0, a, a, c, 0);
    box(texto,0,0);
    mvwprintw(texto, 1, 3, "Battle Log:");
    wrefresh(texto);

    //Create HUD Information
    if(true){
      werase(hud);
      wborder(hud, a, 0, a, 0, a, a, c, 0);
      mvwprintw(hud, 1,15,"%s", team1.at(0)->getNombre().c_str());
      mvwprintw(hud, 2,15,"%s", team1.at(0)->getStatus().c_str());
      mvwprintw(hud, 3,20,":L 100");
      mvwprintw(hud, 4,15,"HP: %d / %d", team1.at(0)->getHp(), team1.at(0)->getOriginalHp());
      for (size_t i = 8; i < 45; i++) {
        mvwprintw(hud,5,i,"_");
      }
      for (size_t i = 2; i < 45; i++) {
        wattron(hud, COLOR_PAIR(6));
        mvwprintw(hud,6,i,"=");
        wattroff(hud, COLOR_PAIR(6));
      }
      box(options,0,0);
      wrefresh(hud);
    }

    //Create HUD2 Information
    if(true){
      werase(hud2);
      wborder(hud2, 0, a, a, 0, a, a, 0, b);
      mvwprintw(hud2, 1,15,"%s", team2.at(0)->getNombre().c_str());
      mvwprintw(hud2, 2,15,"%s", team2.at(0)->getStatus().c_str());
      mvwprintw(hud2, 3,20,":L 100");
      mvwprintw(hud2, 4,15,"HP: %d / %d", team2.at(0)->getHp(), team2.at(0)->getOriginalHp());
      for (size_t i = 1; i < 38; i++) {
        mvwprintw(hud2,5,i,"_");
      }
      for (size_t i = 1; i < 43; i++) {
        wattron(hud2, COLOR_PAIR(6));
        mvwprintw(hud2,6,i,"=");
        wattroff(hud2, COLOR_PAIR(6));
      }
      wrefresh(hud2);
    }

    //Options Player
    mvwprintw(options, 2,4 ,"WHAT ARE YOU GOING TO DO?");
    while (choice!=10) {
      for (size_t i = 0; i < 4; i++) {
        if(i<2){
          if(i==seleccion)
          wattron(options, A_REVERSE);
          mvwprintw(options, i+4, 12, choices[i].c_str());
          wattroff(options, A_REVERSE);
        }else{
          if(i==seleccion)
          wattron(options, A_REVERSE);
          mvwprintw(options, i+2, 38, choices[i].c_str());
          wattroff(options, A_REVERSE);
        }
      }
      choice=wgetch(options);

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

        case KEY_RIGHT:{
          seleccion+=2;
          if (seleccion>3) {
            seleccion-=2;
          }
        }break;

        case KEY_LEFT:{
          seleccion-=2;
          if (seleccion<0) {
            seleccion+=2;
          }
        }break;

        default:
        break;
      }
    }

    //Normal Attack
    if (seleccion==0) {
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 3, "%s", team1.at(0)->Normal(team2.at(0)).c_str());
    }
    //Special Attack
    if (seleccion==1) {
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 3, "%s", team1.at(0)->Special(team2.at(0)).c_str());
    }
    //Switch
    if (seleccion==2) {
      werase(options);
      wrefresh(options);
      choice=0;
      seleccion=1;
      while (choice!=10) {
        mvwprintw(options, 2,4 ,"Which are you going to switch?");
        for (size_t i = 1; i < team1.size(); i++) {
          box(options, 0,0);
          if(i==seleccion)
          wattron(options, A_REVERSE);
          mvwprintw(options, i+3, 12, team1.at(i)->getNombre().c_str());
          wattroff(options, A_REVERSE);
        }
        choice=wgetch(options);

        switch (choice) {
          case KEY_UP:{
            seleccion--;
            if (seleccion<1) {
              seleccion=1;
            }
          }break;

          case KEY_DOWN:{
            seleccion++;
            if (seleccion>team1.size()-1) {
              seleccion=team1.size()-1;
            }
          }break;

          default:
          break;
        }
      }

      Kopemon* nuevo = team1.at(seleccion);
      team1.erase(team1.begin()+seleccion);
      team1.insert(team1.begin(), nuevo);
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 3, "You Switched out your Kopemon. Go %s, you can do it!", team1.at(0)->getNombre().c_str());
    }

    if (seleccion==3) {
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 43, "%s", typeid(team1.at(0)).name());
      mvwprintw(texto, 3, 3, "Fire->Grass->Water->Water Electric->Water / Water revives, Grass heals, Electric Paralyzes, Fire Superattacks");
    }
    mvwprintw(texto, 4, 3, "[Press Enter]");
    wrefresh(texto);
    do {
      resp=wgetch(texto);
    } while(resp!=10);
    werase(texto);
    werase(options);
    box(texto,0,0);
    wrefresh(options);

    //Remove  if fainted
    if(team2.at(0)->getStatus()!="Fainted"){
      //Enemy
      enemy=rand()%2+1;
      //Refresh Enemy HUD
      if(true){
        werase(hud2);
        wborder(hud2, 0, a, a, 0, a, a, 0, b);
        mvwprintw(hud2, 1,15,"%s", team2.at(0)->getNombre().c_str());
        mvwprintw(hud2, 2,15,"%s", team2.at(0)->getStatus().c_str());
        mvwprintw(hud2, 3,20,":L 100");
        mvwprintw(hud2, 4,15,"HP: %d / %d", team2.at(0)->getHp(), team2.at(0)->getOriginalHp());
        for (size_t i = 1; i < 38; i++) {
          mvwprintw(hud2,5,i,"_");
        }
        for (size_t i = 1; i < 43; i++) {
          wattron(hud2, COLOR_PAIR(6));
          mvwprintw(hud2,6,i,"=");
          wattroff(hud2, COLOR_PAIR(6));
        }
        wrefresh(hud2);
      }
      //Normal Attack
      if (enemy==1) {
        werase(texto);
        box(texto,0,0);
        mvwprintw(texto, 1, 3, "Battle Log:");
        mvwprintw(texto, 3, 3, "%s", team2.at(0)->Normal(team1.at(0)).c_str());
      }
      //Special Attack
      if (enemy==2) {
        werase(texto);
        box(texto,0,0);
        mvwprintw(texto, 1, 3, "Battle Log:");
        mvwprintw(texto, 3, 3, "%s", team2.at(0)->Special(team1.at(0)).c_str());
      }
      mvwprintw(texto, 4, 3, "[Press Enter]");
      wrefresh(texto);
      do {
        resp=wgetch(texto);
      } while(resp!=10);
      //Refresh Enemy HUD
      if(true){
        werase(hud2);
        wborder(hud2, 0, a, a, 0, a, a, 0, b);
        mvwprintw(hud2, 1,15,"%s", team2.at(0)->getNombre().c_str());
        mvwprintw(hud2, 2,15,"%s", team2.at(0)->getStatus().c_str());
        mvwprintw(hud2, 3,20,":L 100");
        mvwprintw(hud2, 4,15,"HP: %d / %d", team2.at(0)->getHp(), team2.at(0)->getOriginalHp());
        for (size_t i = 1; i < 38; i++) {
          mvwprintw(hud2,5,i,"_");
        }
        for (size_t i = 1; i < 43; i++) {
          wattron(hud2, COLOR_PAIR(6));
          mvwprintw(hud2,6,i,"=");
          wattroff(hud2, COLOR_PAIR(6));
        }
        wrefresh(hud2);
      }
    }else{
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 3, "%s has fainted. Changing Kopemon", team2.at(0)->getNombre().c_str());

      //Refresh Enemy HUD
      if(true){
        werase(hud2);
        wborder(hud2, 0, a, a, 0, a, a, 0, b);
        mvwprintw(hud2, 1,15,"%s", team2.at(0)->getNombre().c_str());
        mvwprintw(hud2, 2,15,"%s", team2.at(0)->getStatus().c_str());
        mvwprintw(hud2, 3,20,":L 100");
        mvwprintw(hud2, 4,15,"HP: %d / %d", team2.at(0)->getHp(), team2.at(0)->getOriginalHp());
        for (size_t i = 1; i < 38; i++) {
          mvwprintw(hud2,5,i,"_");
        }
        for (size_t i = 1; i < 43; i++) {
          wattron(hud2, COLOR_PAIR(6));
          mvwprintw(hud2,6,i,"=");
          wattroff(hud2, COLOR_PAIR(6));
        }
        wrefresh(hud2);
      }
      team2.erase(team2.begin());
      mvwprintw(texto, 4, 3, "[Press Enter]");
      wrefresh(texto);
      do {
        resp=wgetch(texto);
      } while(resp!=10);
    }

    //Remove Fainted Kopemon
    if (team1.at(0)->getStatus()=="Fainted") {
      werase(texto);
      box(texto,0,0);
      mvwprintw(texto, 1, 3, "Battle Log:");
      mvwprintw(texto, 3, 3, "%s has fainted. Changing Kopemon", team1.at(0)->getNombre().c_str());
      //Create HUD Information
      if(true){
        werase(hud);
        mvwprintw(hud, 1,15,"%s", team1.at(0)->getNombre().c_str());
        mvwprintw(hud, 2,15,"%s", team1.at(0)->getStatus().c_str());
        mvwprintw(hud, 3,20,":L 100");
        mvwprintw(hud, 4,15,"HP: %d / %d", team1.at(0)->getHp(), team1.at(0)->getOriginalHp());
        for (size_t i = 8; i < 45; i++) {
          mvwprintw(hud,5,i,"_");
        }
        for (size_t i = 2; i < 45; i++) {
          wattron(hud, COLOR_PAIR(6));
          mvwprintw(hud,6,i,"=");
          wattroff(hud, COLOR_PAIR(6));
        }
        box(options,0,0);
        wrefresh(hud);
      }
      team1.erase(team1.begin());
      mvwprintw(texto, 4, 3, "[Press Enter]");
      wrefresh(texto);
      do {
        resp=wgetch(texto);
      } while(resp!=10);
    }

    //Exit
    if (team2.size()==0) {
      salida=2;
    }
    if(team1.size()==0){
      salida=1;
    }
    werase(hud);

  } while(salida==0); //Fin de la batalla

  batalla.halt();
  if (salida==1) {
    werase(texto);
    box(texto,0,0);
    mvwprintw(texto, 1, 3, "Battle Log:");
    mvwprintw(texto, 3, 3, "You don't have anymore Kopemon left, you are a loser!");
    mvwprintw(texto, 4, 3, "[Press Enter]");
    wrefresh(texto);
    do {
      resp=wgetch(texto);
    } while(resp!=10);
    team2.clear();
  }

  if (salida==2) {
    Music victory("./Music/Victory.wav");
    victory.play();
    werase(texto);
    box(texto,0,0);
    mvwprintw(texto, 1, 3, "Battle Log:");
    mvwprintw(texto, 2, 3, "Trainer Red: How can this be! You cheated right?");
    mvwprintw(texto, 3, 3, "You are now the Kopemon Champion");
    mvwprintw(texto, 4, 3, "[Press Enter]");
    wrefresh(texto);
    do {
      resp=wgetch(texto);
    } while(resp!=10);
    victory.halt();
    team1.clear();
  }
  erase();
  delwin(hud);
  delwin(hud2);
  delwin(texto);
  delwin(options);
  return salida;
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
        kopemons.push_back(new Electric(new Offensive(75, 70, "Thunder"), "Riachu", 110));
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
        kopemons.push_back(new Water(new PowerUp(35, "Bubblebeam"), new Offensive(60, 85, "Surf"), "Guarturtol", 100));
      }
      if (line=="Vlazztois") {
        kopemons.push_back(new Water(new PowerUp(45, "Brine"), new Offensive(70, 75, "Hydro Pump"), "Vlazztois", 120));
      }
      if (line=="Sulsabaur") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(50, 90, "Absorb"), "Sulsabaur", 90));
      }
      if (line=="Ivybaur") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(60, 85, "Mega Drain"), "Ivybaur", 100));
      }
      if (line=="Nevabaur") {
        kopemons.push_back(new Grass(new PowerUp(45, "Ingrain"), new Offensive(70, 75, "Giga Drain"), "Nevabaur", 120));
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
        kopemons.push_back(new Water(new PowerUp(35, "Water Pulse"), new Offensive(65, 80, "Scald"), "Aqueon", 100));
      }
      if (line=="Vineon") {
        kopemons.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(65, 80, "Magical Leaf"), "Vineon", 100));
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
  Music music("./Music/Guide.wav");
  music.play();
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
  music.halt();
  clear();
}

vector<Kopemon*> Start::title(){

  Music music("./Music/1.wav");
  SoundFX continueFX("./SoundFX/A.wav");
  music.play();

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
  string choices[3] = {"New File", "Load File", "Exit"};
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
    prueba.resize(20);
  }
  continueFX.play();

  delete title;
  werase(menu);
  delwin(menu);
  clear();
  refresh();
  music.halt();
  return prueba;
}

string Start::inicio(){
  //Scanners y colores
  Music music("./Music/Maple.wav");
  SoundFX continueFX("./SoundFX/A.wav");
  music.play();
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
  mvwprintw(texto, 4,2, "[Press enter]");
  int enter=0;
  do {
    enter=wgetch(texto);
  } while(enter!=10);
  continueFX.play();
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
  continueFX.play();

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
  music.halt();
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

vector<Kopemon*> Start::Enemy(){
  vector<Kopemon*> enemy;

  //First & Second Kopemon
  int random=3;
  if (random==1) {
    enemy.push_back(new Fire(new Offensive(70, 75, "Fireblast"), new Offensive(110, 100, "Blastburn"), "Marchizard", 120));
    enemy.push_back(new Electric(new Offensive(65, 80, "Thunderbolt"), "Zapeon", 100));
    enemy.push_back(new Grass(new PowerUp(40, "Synthesis"), new Offensive(65, 80, "Magical Leaf"), "Vineon", 100));

  }else if(random==2){
    enemy.push_back(new Water(new PowerUp(45, "Brine"), new Offensive(70, 75, "Hydro Pump"), "Vlazztois", 120));
    enemy.push_back(new Electric(new Offensive(65, 80, "Thunderbolt"), "Zapeon", 100));
    enemy.push_back(new Fire(new Offensive(65, 80, "Flame Charge"), new Offensive(110, 100, "Fire Blitz"), "Blazeon", 100));

  }else{
    enemy.push_back(new Grass(new PowerUp(45, "Ingrain"), new Offensive(70, 75, "Giga Drain"), "Nevabaur", 120));
    enemy.push_back(new Electric(new Offensive(75, 70, "Thunder"), "Riachu", 110));
    enemy.push_back(new Water(new PowerUp(35, "Water Pulse"), new Offensive(65, 80, "Scald"), "Aqueon", 100));
  }
  return enemy;
}

Start::~Start(){
}
