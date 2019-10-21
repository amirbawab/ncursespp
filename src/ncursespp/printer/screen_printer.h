#ifndef NPP_SCREEN_PRINTER_H_
#define NPP_SCREEN_PRINTER_H_

#include <ncursespp/printer/printer.h>

namespace npp {

class ScreenPrinter : public Printer {
private:
  npp::ScreenWindow* window_;
protected:
  void NC_AddStr(Point point, const std::vector<char32_t>& text) const override;
  void NC_SetAttribute(npp::Point point, unsigned attribute, bool value) const override;
  void NC_ChangeAttribute(npp::Point point, unsigned attribute) const override;
public:
  explicit ScreenPrinter(npp::ScreenWindow* window) : window_(window) {}
};

} // namespace npp

#endif
