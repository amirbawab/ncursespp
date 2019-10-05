#include <ncursespp/window.h>
#include <ncursespp/common.h>

namespace npp {
  Window::Window(npp::WindowOptions options) : Window(options, 0, 0, 0, 0) {}

  Window::Window(WindowOptions options, int x, int y, int width, int height)
      : options_(options), x_(x), y_(y), width_(width), height_(height) {
    // Tile layout by default
    layout_ = new TileLayout();

    // TODO (amir) Read options
  }

  void Window::AddChild(npp::Window *window) {
    DCHECK_NE(window, nullptr);
    DCHECK_NE(layout_, nullptr);
    layout_->Include(window);
  }

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