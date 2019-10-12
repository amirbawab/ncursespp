#include <ncursespp/text.h>
#include <ncursespp/window.h>

namespace npp {

void Text::Print(npp::Window* window) {
  auto inner_view = InnerView();
  window->Printer().DrawString({inner_view.x, inner_view.y}, value_);
}

} // namespace npp