#ifndef NPP_WINDOW_H_
#define NPP_WINDOW_H_

#include <ncurses/curses.h>
#include <ncursespp/panel/panel.h>
#include <ncursespp/printer/screen_printer.h>

namespace npp {

struct WindowOptions {
  bool no_echo = false;
  bool keypard = false;
};

class Window {
private:
  WindowOptions options_;
  npp::Printer* printer_;
public:
  explicit Window(WindowOptions options, npp::Printer* printer) : options_(options), printer_(printer) {}
  const npp::Printer* Printer() const { return printer_; }
  const WindowOptions& Options() const { return options_; }
  virtual npp::View View() const = 0;
  virtual void Copy(BufferWindow* buffer_window, npp::View view) = 0;
};

} // namespace npp

#endif