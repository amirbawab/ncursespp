#include <iostream>
#include <ncurses/curses.h>
#include <ncursespp/window.h>

int main() {

  npp::Terminal terminal;
  terminal.init();
  terminal.end();
  printf("%d %d %d %d\n", terminal.Width(), terminal.Height(), terminal.X(), terminal.Y());
  return 0;
}
