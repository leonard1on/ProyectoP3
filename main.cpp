#include <ncurses.h>
#include "Start.h"

int main(int argc, char const *argv[]) {
  Start* game = new Start();
  game->run();
  delete game;
  return 0;
}
