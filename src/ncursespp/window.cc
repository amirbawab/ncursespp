#include <ncursespp/window.h>

namespace npp {
  void Terminal::init() {
    // Init window
    // TODO (amir) Allow further configuration
    initscr();
    cbreak();
    noecho();
    clear();

    SetX(0);
    SetY(0);
    SetWidth(COLS);
    SetHeight(LINES);
  }

  void Terminal::end() {
    endwin();
  }
}