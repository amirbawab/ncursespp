#include <iostream>
#include <ncurses/curses.h>
#include <ncursespp/window.h>

int main() {
  npp::WindowOptions terminal_options;
  terminal_options.show_cursor = false;

  npp::Terminal terminal(terminal_options);
  terminal.init();
  terminal.AddChild(&terminal);
  getch();
  terminal.end();
  return 0;
}
