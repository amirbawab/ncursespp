#include <ncursespp/panel.h>
#include <ncursespp/layout.h>

namespace npp {

Panel::Panel(std::string id) : id_(id) {
  // FIXME (amir) default to tile layout
  layout_ = new TileLayout();
}

} // namespace npp