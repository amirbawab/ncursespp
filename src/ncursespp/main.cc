#include <iostream>
#include <ncursespp/window/screen_window.h>
#include <ncursespp/panel/scroll_panel.h>
#include <ncursespp/layout/layout.h>
#include <ncursespp/panel/button.h>
#include <ncursespp/panel/input.h>

int main() {
  npp::ScreenWindow main_window;
  main_window.Initialize();

  // Border template
  npp::Borders border;
  border.left.style = npp::SolidThin;
  border.top.style = npp::SolidThin;
  border.right.style = npp::SolidThin;
  border.bottom.style = npp::SolidThin;

  // Input field
  npp::Input input;
  input.Text().Insert(U"Hello world");

  auto main_panel = main_window.Panel();
  main_panel->AddChild(&input);
  main_window.Fit();
  main_window.Print();

  refresh();
  while(getch()) {
    main_window.Clear();
    main_window.Fit();
    main_window.Print();
  }
  main_window.Destroy();
  return 0;
}
