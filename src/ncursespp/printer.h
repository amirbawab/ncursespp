#ifndef NPP_PRINTER_H_
#define NPP_PRINTER_H_

#include <string>
#include <ncursespp/view.h>
#include <ncursespp/layout.h>
#include <ncursespp/text.h>

namespace npp {

struct Point {
  int x;
  int y;
};

struct TextPrinterOptions {
  bool wrap = true;
};

class ScreenWindow;
class BufferWindow;
class Printer {
protected:
  virtual void NC_AddStr(Point point, const std::vector<char32_t>& text) const = 0;
public:
  void DrawTextBuffer(npp::TextBuffer* text_buffer, View view, TextPrinterOptions options = TextPrinterOptions()) const;
  void DrawEmptyView(View view) const;
  void DrawVLine(Point point, int length, BorderStyle style = SolidThin) const;
  void DrawHLine(Point point, int length, BorderStyle style = SolidThin) const;
  void DrawTLCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawTRCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBLCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBRCorner(Point point, BorderStyle style = SolidThin) const;
  void DrawBorder(Borders borders, View view) const;
  void DrawChar32Vector(Point point, const std::vector<char32_t>& text) const;
};

class ScreenPrinter : public Printer {
private:
  npp::ScreenWindow* window_;
protected:
  void NC_AddStr(Point point, const std::vector<char32_t>& text) const override;
public:
  explicit ScreenPrinter(npp::ScreenWindow* window) : window_(window) {}
};

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
