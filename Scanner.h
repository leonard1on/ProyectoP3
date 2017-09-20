#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ncurses.h>
using namespace std;

class Scanner {
private:
  string text;
  ifstream* file;

public:
  Scanner (string);
  void print(int, int);
  void wprint(WINDOW*, int, int);
  void sout();
  ~Scanner();
};
