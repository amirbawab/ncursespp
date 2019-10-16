#include <ncursespp/view.h>
#include <algorithm>

namespace npp {

npp::View ViewIntersection(const npp::View &v1, const npp::View &v2) {
  npp::View intersection;
  intersection.x = std::max(v1.x, v2.x);
  intersection.y = std::max(v1.y, v2.y);
  intersection.cols = std::min(v1.x + v1.cols, v2.x + v2.cols) - intersection.x;
  intersection.rows = std::min(v1.y + v1.rows, v2.y + v2.rows) - intersection.y;
  if (!VisibleView(intersection)) {
    return INVISIBLE_VIEW;
  }
  return intersection;
}

bool VisibleView(const npp::View& view) {
  return view.rows > 0 && view.cols > 0;
}

} // namespace npp