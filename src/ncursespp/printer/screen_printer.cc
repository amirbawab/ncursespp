#include <ncursespp/printer/screen_printer.h>
#include <ncursespp/window/screen_window.h>
#include <ncursespp/common.h>

namespace npp {

void ScreenPrinter::NC_AddStr(npp::Point point, const std::vector<char32_t>& text) const {
  std::string text_str;
  Char32VectorToString(text, text_str);
  mvwaddstr(window_->CursesWindow(), point.y, point.x, text_str.c_str());
}

void ScreenPrinter::NC_SetAttribute(npp::Point point, unsigned attribute, bool value) const {
  wmove(window_->CursesWindow(), point.y, point.x);
  if(value) {
    wattron(window_->CursesWindow(), attribute);
  } else {
    wattroff(window_->CursesWindow(), attribute);
  }
}

void ScreenPrinter::NC_ChangeAttribute(npp::Point point, unsigned attribute) const {
  mvwchgat(window_->CursesWindow(), point.y, point.x, 1, attribute, 0, NULL);
}

} // namespace npp