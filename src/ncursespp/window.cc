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

BufferWindow::BufferWindow(npp::View view, npp::WindowOptions options) :
    Window(options, new BufferPrinter(this)), view_(view), window_buffer_(0) {
  SetupWindow();
}

void BufferWindow::SetupWindow() {
  DCHECK_GE(view_.x, 0);
  DCHECK_GE(view_.y, 0);
  DCHECK_GE(view_.rows, 0);
  DCHECK_GE(view_.cols, 0);
  window_buffer_.resize(static_cast<size_t>(view_.rows), std::vector<char>(static_cast<size_t >(view_.cols), ' '));

}

char& BufferWindow::CharAt(npp::Point point) {
  auto row = RowAt(point.y);
  DCHECK_GE(point.x, 0);
  DCHECK_LT(point.x, window_buffer_[point.y].size());
  return row[point.y];
}

std::vector<char>& BufferWindow::RowAt(int y) {
  DCHECK_GE(y, 0);
  DCHECK_LT(y, window_buffer_.size());
  return window_buffer_[y];
}

} // namespace npp