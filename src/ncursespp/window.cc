#include <ncursespp/window.h>

namespace npp {

Window::Window(npp::WindowOptions options) : options_(options) {
  window_ = stdscr;
}

void Window::Initialize() {
  initscr();
  if(options_.no_echo) noecho();
  if(options_.keypard) keypad(window_, TRUE);
}

void Window::Destroy() {
  endwin();
}

npp::View Window::View() const {
  npp::View view;
  view.x = 0;
  view.y = 0;
  view.cols = Cols();
  view.rows = Rows();
  return view;
}

void Window::Fit() {
  panel_.SetView(View());
  panel_.Fit();
}

} // namespace npp