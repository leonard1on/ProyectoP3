#include <ncurses.h>
#include "Start.h"

int main(int argc, char const *argv[]) {
  Start* game = new Start();
  game->run();
  return 0;
}
