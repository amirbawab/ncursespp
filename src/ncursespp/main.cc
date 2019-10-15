#include <iostream>
#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include <ncursespp/layout.h>
#include <ncursespp/button.h>

int main() {
  npp::ScreenWindow main_window;
  main_window.Initialize();

  // Border template
  npp::Borders border;
  border.left.style = npp::SolidThin;
  border.top.style = npp::SolidThin;
  border.right.style = npp::SolidThin;
  border.bottom.style = npp::SolidThin;

  npp::Panel left;
  left.Layout()->SetBorder(border);
  npp::Button left_button("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbbb\nccc");
  left.AddChild(&left_button);

  npp::ScrollPanel right(100, 100);

  auto main_panel = main_window.Panel();
  main_panel->AddChild(&left);
  main_panel->AddChild(&right);
  main_window.Fit();
  main_window.Print();

//  printf("r=%d\tc=%d\n\r", main_window.Rows(), main_window.Cols());
//  printf("x=%d\ty=%d\tr=%d\tc=%d\n\r", left.View().x, left.View().y, left.View().rows, left.View().cols);
//  printf("x=%d\ty=%d\tr=%d\tc=%d\n\r", right.View().x, right.View().y, right.View().rows, right.View().cols);

  refresh();
  while(getch()) {
    main_window.Clear();
    main_window.Fit();
    main_window.Print();
  }
  main_window.Destroy();
  return 0;
}
