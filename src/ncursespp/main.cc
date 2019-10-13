#include <iostream>
#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include <ncursespp/layout.h>
#include <ncursespp/button.h>

int main() {
  npp::Window main_window;
  main_window.Initialize();

  npp::Button left_button("Left Button");
  npp::Button right_button("Right Button");

  npp::Panel left("left");
  npp::Panel right("right");
  left.AddChild(&left_button);
  right.AddChild(&right_button);

  npp::Borders left_border;
  left_border.left.style = npp::SolidThin;
  left_border.top.style = npp::SolidThin;
  left_border.right.style = npp::SolidThin;
  left_border.bottom.style = npp::SolidThin;
  left.Layout()->SetBorder(left_border);

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
