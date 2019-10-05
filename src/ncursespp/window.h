#ifndef NPP_WINDOW_H_
#define NPP_WINDOW_H_

#include <ncurses/ncurses.h>
#include <ncursespp/layout.h>

namespace npp {

struct WindowOptions {
  bool show_cursor = false;
};

class Window {
public:
  Window(WindowOptions options);
  Window(WindowOptions options, int x, int y, int width, int height);
  int X() const { return x_; }
  int Y() const { return y_; }
  int Width() const { return width_; }
  int Height() const { return height_; }
  int SetWidth(int width) { width_ = width; }
  int SetHeight(int height) { height_ = height; }
  int SetX(int x) { x_ = x; }
  int SetY(int y) { y_ = y; }
  int SetLayout(Layout* layout) { layout_ = layout; }
  Layout* GetLayout() { return layout_; }
  void AddChild(Window* window);
  WindowOptions Options() const { return options_; }
private:
  WindowOptions options_;
  int x_;
  int y_;
  int width_;
  int height_;
  Layout* layout_;
};

class Terminal : public Window {
public:
  explicit Terminal(WindowOptions options) : Window(options) {};
  void init();
  void end();
};

} // npp

#endif