#include <iostream>
#include <ncursespp/window.h>

int main() {
  npp::Window main_window;
  main_window.Initialize();
  getch();
  main_window.Destroy();
  return 0;
}
