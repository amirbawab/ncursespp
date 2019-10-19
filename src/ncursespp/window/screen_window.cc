#include <ncursespp/window/screen_window.h>
#include <ncursespp/window/buffer_window.h>
#include <ncursespp/common.h>

namespace npp {

void ScreenWindow::Initialize() {
  setlocale(LC_ALL, "");
  initscr();
  window_ = stdscr;
  auto options = Options();
  if(options.no_echo) noecho();
  if(options.keypard) keypad(window_, TRUE);
}

void ScreenWindow::Destroy() {
  endwin();
}

npp::View ScreenWindow::View() const {
  npp::View view;
  view.x = 0;
  view.y = 0;
  view.cols = Cols();
  view.rows = Rows();
  return view;
}

void ScreenWindow::Fit() {
  panel_.SetView(View());
  panel_.Fit();
}

void ScreenWindow::Print() {
  panel_.Print(this, this);
}

void ScreenWindow::Clear() {
  panel_.Clear(this);
}

void ScreenWindow::Copy(npp::BufferWindow *buffer_window, npp::View view) {
  auto screen_windwow_view = this->View();
  auto buffer_window_view = buffer_window->View();
  npp::View panel_buffer_view = ViewIntersection(buffer_window_view, view);
  npp::View screen_panel_buffer_view = ViewIntersection(screen_windwow_view, panel_buffer_view);
  auto x_begin = screen_panel_buffer_view.x - buffer_window_view.x;
  auto y_begin = screen_panel_buffer_view.y - buffer_window_view.y;
  auto x_end = x_begin + screen_panel_buffer_view.cols;
  auto y_end = y_begin + screen_panel_buffer_view.rows;

  DCHECK_GE(x_begin, 0);
  DCHECK_GE(y_begin, 0);

  for(auto y=y_begin; y < y_end; y++) {
    const std::vector<char32_t> &row = buffer_window->RowAt(y);
    std::vector<char32_t> sub_row(row.begin() + x_begin, row.begin() + x_end);
    Printer()->DrawChar32Vector({screen_panel_buffer_view.x, screen_panel_buffer_view.y}, sub_row);
    screen_panel_buffer_view.y++;
  }
}

} // namespace npp