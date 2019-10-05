#include <ncursespp/layout.h>

namespace npp {
void Layout::Include(npp::Window *window) {
  windows_.push_back(window);
}

WindowVector TileLayout::Windows() {
  WindowVector windows = Layout::Windows();
  return windows;
}

} // npp