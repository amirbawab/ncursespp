#ifndef NPP_WINDOW_H_
#define NPP_WINDOW_H_

#include <ncurses/curses.h>
#include <ncursespp/panel.h>
#include <ncursespp/printer.h>

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
};

class ScreenWindow : public Window {
private:
  WINDOW* window_ = nullptr;
  npp::Panel panel_;
public:
  explicit ScreenWindow(WindowOptions options = WindowOptions()) : Window(options, new npp::ScreenPrinter(this)) {};
  void Initialize();
  void Destroy();
  int Rows() const { return LINES; }
  int Cols() const { return COLS; }
  npp::View View() const;
  npp::Panel* Panel() { return &panel_; }
  void Fit();
  void Print();
  void Clear();
  WINDOW* CursesWindow() const { return window_; }
};

} // namespace npp

#endif