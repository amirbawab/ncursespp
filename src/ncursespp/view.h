#ifndef NPP_VIEW_H_
#define NPP_VIEW_H_

namespace npp {

#define INVISIBLE_VIEW npp::View{0, 0, 0, 0};

struct View {
  View(int x, int y, int rows, int cols) : x(x), y(y), rows(rows), cols(cols) {}
  View() : View(0, 0, 0, 0) {}
  int x;
  int y;
  int rows;
  int cols;
};

/**
 * Create an intersection view from two view input
 * @param v1
 * @param v2
 * @return view
 */
View ViewIntersection(const npp::View &v1, const npp::View &v2);

/**
 * Check if a view is visible or can be printed
 * @param view
 * @return boolean
 */
bool VisibleView(const npp::View& view);

} // namespace npp

#endif