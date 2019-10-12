#ifndef NPP_PRINTER_H_
#define NPP_PRINTER_H_

#include <string>
#include <ncursespp/view.h>
#include <ncursespp/layout.h>

namespace npp {

struct Point {
  int x;
  int y;
};

class Window;
class Printer {
private:
  npp::Window* window_;
  inline void NC_AddStr(Point point, std::string text) const;
  inline void NC_AddCh(Point point, unsigned int c) const;
public:
  explicit Printer(npp::Window* window) : window_(window) {}
  void DrawString(Point point, std::string text) const;
  void DrawEmptyView(View view) const;
  void DrawVLine(Point point, int length, BorderStyle style = SolidThin) const;
  void DrawHLine(Point point, int length, BorderStyle style = SolidThin) const;
  void DrawTLCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawTRCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBLCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBRCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBorder(Borders borders, View view) const;
};

} // namespace npp

#endif
