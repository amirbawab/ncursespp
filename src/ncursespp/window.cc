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

} // namespace npp