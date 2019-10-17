#include <ncursespp/window.h>
#include <ncursespp/layout.h>
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
  panel_.Print(this);
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

BufferWindow::BufferWindow(npp::View view, npp::WindowOptions options) :
    Window(options, new BufferPrinter(this)), view_(view), window_buffer_(0) {
  SetupWindow();
}

void BufferWindow::SetupWindow() {
  DCHECK_GE(view_.x, 0);
  DCHECK_GE(view_.y, 0);
  DCHECK_GE(view_.rows, 0);
  DCHECK_GE(view_.cols, 0);
  window_buffer_.resize(static_cast<size_t>(view_.rows), std::vector<char32_t>(static_cast<size_t >(view_.cols), ' '));

}

char32_t& BufferWindow::CharAt(npp::Point point) {
  auto row = RowAt(point.y);
  DCHECK_GE(point.x, 0);
  DCHECK_LT(point.x, window_buffer_[point.y].size());
  return row[point.y];
}

std::vector<char32_t>& BufferWindow::RowAt(int y) {
  DCHECK_GE(y, 0);
  DCHECK_LT(y, window_buffer_.size());
  return window_buffer_[y];
}

void BufferWindow::SetPoint(npp::Point point) {
  view_.x = point.x;
  view_.y = point.y;
}

void BufferWindow::Copy(npp::BufferWindow *buffer_window, npp::View view) {
  // TODO (amir) to implement
}

} // namespace npp