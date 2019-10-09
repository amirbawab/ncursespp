#include <iostream>
#include <ncurses/curses.h>
#include <ncursespp/gap_buffer/gap_buffer.h>

int main() {
  npp::GapBuffer<char> gap_buffer;
  gap_buffer.Insert({'a','b','c'});
  auto val = gap_buffer.Value();
  auto str = std::string(val.begin(), val.end());
  printf("%s\n", str.c_str());
  return 0;
}
