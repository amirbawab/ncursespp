#ifndef NPP_WINDOW_H_
#define NPP_WINDOW_H_

#include <ncurses/ncurses.h>

namespace npp {
class Window {
public:
  Window() {}
  Window(int x, int y, int width, int height) :
      x_(x), y_(y), width_(width), height_(height) {};
  int X() const { return x_; }
  int Y() const { return y_; }
  int Width() const { return width_; }
  int Height() const { return height_; }
  int SetWidth(int width) { width_ = width; }
  int SetHeight(int height) { height_ = height; }
  int SetX(int x) { x_ = x; }
  int SetY(int y) { y_ = y; }
private:
  int x_;
  int y_;
  int width_;
  int height_;
};

class Terminal : public Window {
public:
  void init();
  void end();
};

} // npp

#endif