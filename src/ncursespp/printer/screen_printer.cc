#include <ncursespp/printer/screen_printer.h>
#include <ncursespp/window/screen_window.h>
#include <ncursespp/common.h>

namespace npp {

void ScreenPrinter::NC_AddStr(npp::Point point, const std::vector<char32_t>& text) const {
  std::string text_str;
  Char32VectorToString(text, text_str);
  mvwaddstr(window_->CursesWindow(), point.y, point.x, text_str.c_str());
}

} // namespace npp