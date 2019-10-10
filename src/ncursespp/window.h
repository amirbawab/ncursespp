#ifndef NPP_WINDOW_H_
#define NPP_WINDOW_H_

#include <ncurses/curses.h>
#include <ncursespp/panel.h>

namespace npp {

struct WindowOptions {
  bool no_echo = false;
  bool keypard = false;
};

class Window {
private:
  WindowOptions options_;
  npp::Panel panel_;
  WINDOW* window_ = nullptr;
public:
  explicit Window(WindowOptions options = WindowOptions());
  void Initialize();
  void Destroy();
  npp::Panel* Panel() { return &panel_;};
};

} // namespace npp

#endif