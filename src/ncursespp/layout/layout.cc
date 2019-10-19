#include <ncursespp/layout/layout.h>
#include <ncursespp/common.h>

namespace npp {

Layout::Layout() {
  SetMargin({0, 0, 0, 0});
  SetPadding({0, 0, 0, 0});
}

npp::View Layout::MarginView(Panel* panel) const {
  auto view = panel->View();
  view.x += margin_.left;
  view.y += margin_.top;
  view.cols -= margin_.left + margin_.right;
  view.rows -= margin_.top + margin_.bottom;
  return view;
}

npp::View Layout::BorderView(npp::Panel *panel) const {
  auto view = MarginView(panel);
  int top = border_.top.None() ? 0 : 1;;
  int left = border_.left.None() ? 0 : 1;;
  int bottom = border_.bottom.None() ? 0 : 1;;
  int right = border_.right.None() ? 0 : 1;;
  view.x += left;
  view.y += top;
  view.cols -= left + right;
  view.rows -= top + bottom;
  return view;
}

npp::View Layout::PaddingView(npp::Panel *panel) const {
  auto view = BorderView(panel);
  view.x += padding_.left;
  view.y += padding_.top;
  view.cols -= padding_.right;
  view.rows -= padding_.bottom;
  return view;
}

} // namespace npp