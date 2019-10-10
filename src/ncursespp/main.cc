#include <iostream>
#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include "layout.h"

int main() {
  npp::Window main_window;
  main_window.Initialize();

  npp::Panel left("left");
  npp::Panel right("right");

  auto main_panel = main_window.Panel();
  main_panel->AddChild(&left);
  main_panel->AddChild(&right);
  main_window.Fit();

  printf("r=%d\tc=%d\n\r", main_window.Rows(), main_window.Cols());
  printf("x=%d\ty=%d\tr=%d\tc=%d\n\r", left.View().x, left.View().y, left.View().rows, left.View().cols);
  printf("x=%d\ty=%d\tr=%d\tc=%d\n\r", right.View().x, right.View().y, right.View().rows, right.View().cols);

//  getch();
  main_window.Destroy();
  return 0;
}
