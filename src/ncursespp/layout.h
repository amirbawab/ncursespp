#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <ncursespp/common.h>

namespace npp {
enum LayoutKind {
  Tile
};

class Window;
typedef std::vector<Window*> WindowVector;

class Layout {
public:
  explicit Layout(std::string name) : name_(std::move(name)) {}
  virtual WindowVector Windows() { return windows_; }
  void Include(Window* window);
private:
  std::string name_;
  WindowVector windows_;
};

class TileLayout : public Layout {
public:
  TileLayout() : Layout("tile") {}
  WindowVector Windows();
};
}

#endif