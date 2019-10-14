#include <ncursespp/window.h>
#include "layout.h"

namespace npp {

void ScreenWindow::Initialize() {
  setlocale(LC_ALL, "");
  initscr();
  window_ = stdscr;
  auto options = Options();
  if(options.no_echo) noecho();
  if(options.keypard) keypad(window_, TRUE);
}

void ScreenWindow::Destroy() {
  endwin();
}

npp::View ScreenWindow::View() const {
  npp::View view;
  view.x = 0;
  view.y = 0;
  view.cols = Cols();
  view.rows = Rows();
  return view;
}

void ScreenWindow::Fit() {
  panel_.SetView(View());
  panel_.Fit();
}

void ScreenWindow::Print() {
  panel_.Print(this);
}

void ScreenWindow::Clear() {
  panel_.Clear(this);
}

} // namespace npp