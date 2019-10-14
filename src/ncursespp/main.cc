#include <iostream>
#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include <ncursespp/layout.h>
#include <ncursespp/button.h>

int main() {
  npp::Window main_window;
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

  npp::Panel right;
  npp::SidedLayout sided_layout;
  right.SetLayout(&sided_layout);
  npp::Panel right_top, right_left, right_bottom, right_right, right_center;
  right_top.Layout()->SetBorder(border);
  right_left.Layout()->SetBorder(border);
  right_bottom.Layout()->SetBorder(border);
  right_right.Layout()->SetBorder(border);
  right_center.Layout()->SetBorder(border);
  right.AddChild(&right_top);
  right.AddChild(&right_left);
  right.AddChild(&right_bottom);
  right.AddChild(&right_right);
  right.AddChild(&right_center);
  sided_layout.SetSide(&right_center, npp::SidePanel::Center, -1);
  sided_layout.SetSide(&right_top, npp::SidePanel::Top, 10);
  sided_layout.SetSide(&right_left, npp::SidePanel::Left, 10);
  sided_layout.SetSide(&right_bottom, npp::SidePanel::Bottom, 10);
  sided_layout.SetSide(&right_right, npp::SidePanel::Right, 10);

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
