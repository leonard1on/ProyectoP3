#include "Scanner.h"
#include <string>
#include <iostream>
#include <iostream>
#include <ncurses.h>
using namespace std;

Scanner::Scanner(string txt){
  text=txt;
  file=new ifstream(txt);
}

void Scanner::print(int move, int x){
  string line;
  if (!file->is_open()) {
    file->clear();
    file->open(text);
  }

  while (getline(*file,line)) {
    mvprintw(move, x, "%s", line.c_str());
    move++;
  }
  file->close();
}

void Scanner::wprint(WINDOW* ventana, int move, int x){
  string line;
  if (!file->is_open()) {
    file->clear();
    file->open(text);
  }

  while (getline(*file,line)) {
    mvwprintw(ventana, move, x, "%s", line.c_str());
    move++;
  }
  file->close();
}

void Scanner::sout(){
  string line;
  if (!file->is_open()) {
    file->clear();
    file->open(text);
  }

  while (getline(*file,line)) {
    cout<<line <<endl;
  }
  file->close();
}


Scanner::~Scanner(){
  delete file;
}
