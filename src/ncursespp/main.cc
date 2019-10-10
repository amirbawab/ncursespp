#include <iostream>
#include <ncurses/curses.h>
#include <ncursespp/gap_buffer/gap_buffer.h>
#include <ncursespp/border.h>

int main() {
  printf("%d\n", npp::BorderStyle::SolidThin);
  return 0;
}
