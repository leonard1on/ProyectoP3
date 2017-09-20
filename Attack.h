#pragma once
#include <string>
using namespace std;

class Attack {
private:
  string name;
public:
  Attack (string);
  string getName();
  void setName(string);
  ~Attack();
};
