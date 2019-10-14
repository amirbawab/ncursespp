#ifndef NPP_VIEW_H_
#define NPP_VIEW_H_

namespace npp {

struct View {
  View(int x, int y, int rows, int cols) : x(x), y(y), rows(rows), cols(cols) {}
  View() : View(0, 0, 0, 0) {}
  int x;
  int y;
  int rows;
  int cols;
};

} // namespace npp

#endif