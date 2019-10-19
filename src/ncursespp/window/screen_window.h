#ifndef NPP_SCREEN_WINDOW_H_
#define NPP_SCREEN_WINDOW_H_

#include <ncursespp/window/window.h>

namespace npp {

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
  npp::View View() const override;
  npp::Panel* Panel() { return &panel_; }
  void Fit();
  void Print();
  void Clear();
  WINDOW* CursesWindow() const { return window_; }
  void Copy(BufferWindow* buffer_window, npp::View view) override;
};

} // namespace npp

#endif