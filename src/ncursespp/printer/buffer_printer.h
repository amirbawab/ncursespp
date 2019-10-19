#ifndef NPP_BUFFER_PRINTER_H_
#define NPP_BUFFER_PRINTER_H_

#include <ncursespp/printer/printer.h>

namespace npp {

class BufferPrinter : public Printer {
private:
  npp::BufferWindow* window_;
protected:
  void NC_AddStr(Point point, const std::vector<char32_t>& text) const override;
public:
  explicit BufferPrinter(npp::BufferWindow* window) : window_(window) {}
};

} // namespace npp

#endif
