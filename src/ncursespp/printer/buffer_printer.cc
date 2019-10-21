#include <ncursespp/printer/buffer_printer.h>
#include <ncursespp/window/buffer_window.h>
#include <ncursespp/common.h>

namespace npp {

Point BufferPrinter::RelativePoint(const npp::Point& point) const {
  auto window_view = window_->View();
  Point relative_point = {point.x - window_view.x, point.y - window_view.y};
  DCHECK_GE(relative_point.x, 0);
  DCHECK_GE(relative_point.y, 0);
  return relative_point;
}

void BufferPrinter::NC_AddStr(npp::Point point, const std::vector<char32_t>& text) const {
  auto relative_point = RelativePoint(point);
  std::vector<char32_t>& row = window_->RowAt(relative_point.y);
  auto string_begin = row.begin() + relative_point.x;
  std::copy(text.begin(), text.end(), string_begin);
}

void BufferPrinter::NC_SetAttribute(npp::Point point, unsigned attribute, bool value) const {
  if(value) {
    window_->AttributeAt(RelativePoint(point)) |= attribute;
  } else {
    window_->AttributeAt(RelativePoint(point)) &= ~attribute;
  }
}

void BufferPrinter::NC_ChangeAttribute(npp::Point point, unsigned attribute) const {
  window_->AttributeAt(RelativePoint(point)) = attribute;
}

} // namespace npp