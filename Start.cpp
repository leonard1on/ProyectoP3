#include "Kopemon.h"
#include "Fire.h"
#include "Grass.h"
#include "Electric.h"
#include "Water.h"
#include "Attack.h"
#include "Offensive.h"
#include "PowerUp.h"
#include <ncurses.h>
#include "Start.h"
#include <string>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <vector>

#define maxX 150
#define maxY 38

using namespace std;
void Start::run(){
  vector<Kopemon*> kopemons;
  initscr();
  noecho();
  cbreak();
  kopemons=title();
  string piedra="Fire";
  if (kopemons.size()==0) {
    piedra=inicio();
    Kopemon* veev=new Kopemon("Veev", 60);
    kopemons.push_back(veev);
    explicacion(piedra);
  }


  getch();
  endwin();
}

void Start::explicacion(string stone){
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  int move=0;
  string line;
  ifstream file("./Dibujos/Veev.txt");
  if (file.is_open()) {
    while (getline(file,line)) {
      attron(COLOR_PAIR(3));
      attron(A_BOLD);
      mvprintw(move,0, "%s",line.c_str());
      attroff(A_BOLD);
      attroff(COLOR_PAIR(3));
      move++;
    }
    file.close();
  }else{
    printw("File could not open");
  }

  move=0;
  ifstream file3("./Dibujos/Tutorial.txt");
  if (file3.is_open()) {
    while (getline(file3,line)) {
      attron(COLOR_PAIR(2));
      attron(A_BOLD);
      mvprintw(move,maxX/2+18, "%s",line.c_str());
      attroff(A_BOLD);
      attroff(COLOR_PAIR(2));
      move++;
    }
    file3.close();
  }else{
    printw("File could not open");
  }

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
  move=7;
  ifstream file2("./Dibujos/Procedure.txt");
  if (file2.is_open()) {
    while (getline(file2,line)) {
      wattron(text, COLOR_PAIR(1));
      wattron(text, A_BOLD);
      mvwprintw(text, move,10, "%s",line.c_str());
      wattroff(text, A_BOLD);
      wattroff(text, COLOR_PAIR(1));
      move++;
    }
    file2.close();
  }else{
    printw("File could not open");
  }

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
  mvwprintw(text,25,2, "Press Enter");
  wattroff(text, COLOR_PAIR(1));
  wattroff(text, A_BOLD);
  refresh();
  wrefresh(text);
  int enter;
  do {
    enter=wgetch(text);
  } while(enter!=10);
  werase(text);
  delwin(text);
  clear();
}

vector<Kopemon*> Start::title(){
  vector<Kopemon*> prueba;
  //-------------------------------
  box(stdscr,0,0);
  string line;
  int move=1;
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  ifstream title("./Dibujos/Kopemon.txt");
  if (title.is_open()) {
    while (getline(title,line)) {
      attron(COLOR_PAIR(1));
      attron(A_BOLD);
      mvprintw(move,40, "%s",line.c_str());
      attroff(A_BOLD);
      attroff(COLOR_PAIR(1));
      move++;
    }
    title.close();
  }else{
    printw("File could not open");
  }

  move=17;
  ifstream ball("./Dibujos/pokeball.txt");
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

  attron(COLOR_PAIR(2));
  attron(A_BOLD);
  mvprintw(15, 68, "Crimson  Version");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(2));

  attron(A_BOLD);
  mvprintw(maxY-3, 62, "2017 THE KOPEMON GAME COMPANY");
  attroff(A_BOLD);
  refresh();

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
    printw("load game");
  }

  if (seleccion==2) {

  }

  refresh();
  //getch();
  clear();
  return prueba;
}
string Start::inicio(){
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  //Imprime al Professor Maple
  int move=0;
  string line;
  ifstream file("./Dibujos/Maple.txt");
  if (file.is_open()) {
    while (getline(file,line)) {
      mvprintw(move,45, "%s",line.c_str());
      move++;
    }
    file.close();
  }else{
    printw("File could not open");
  }

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
  move=14;
  ifstream kipachu("./Dibujos/Kipachu.txt");
  if (kipachu.is_open()) {
    while (getline(kipachu,line)) {
      attron(COLOR_PAIR(1));
      attron(A_BOLD);
      mvprintw(move,17, "%s",line.c_str());
      attroff(A_BOLD);
      attroff(COLOR_PAIR(1));
      move++;
    }
    kipachu.close();
  }else{
    printw("File could not open");
  }
  refresh();
  usleep(1000000);
  mvprintw(13,22,"Ki-pa-chu!");
  refresh();

  //Segundo Texto
  mvwprintw(texto, 4,1, "Press enter");
  int enter=0;
  do {
    enter=wgetch(texto);
  } while(enter!=10);

  wclear(texto);
  box(texto,0,0);
  mvwprintw(texto, 1,2, "Your mission is to create all possible Kopemons so you can compete. You will need to combine elements with Kopemons to creat new Kope- ");
  mvwprintw(texto, 2,2, "mons. Since I'm a good fellow, I'm going to give you the basic Kopemon 'Veev', and a special stone to help you start your adventure. ");
  mvwprintw(texto, 4,2, "Press enter");
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
  werase(texto);
  werase(menu);
  delwin(texto);
  delwin(menu);
  clear();
  refresh();
  string eleccion=choices[seleccion];
  usleep(500000);
  return eleccion;
}
