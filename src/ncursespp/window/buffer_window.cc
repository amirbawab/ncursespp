#include <ncursespp/window/buffer_window.h>
#include <ncursespp/printer/buffer_printer.h>
#include <ncursespp/common.h>

namespace npp {

BufferWindow::BufferWindow(npp::View view, npp::WindowOptions options) :
    Window(options, new BufferPrinter(this)), view_(view), window_buffer_(0) {
  SetupWindow();
}

void BufferWindow::SetupWindow() {
  DCHECK_GE(view_.x, 0);
  DCHECK_GE(view_.y, 0);
  DCHECK_GE(view_.rows, 0);
  DCHECK_GE(view_.cols, 0);
  window_buffer_.resize(static_cast<size_t>(view_.rows),
                        std::vector<char32_t>(static_cast<size_t >(view_.cols), ' '));

}

char32_t &BufferWindow::CharAt(npp::Point point) {
  auto row = RowAt(point.y);
  DCHECK_GE(point.x, 0);
  DCHECK_LT(point.x, window_buffer_[point.y].size());
  return row[point.y];
}

std::vector<char32_t> &BufferWindow::RowAt(int y) {
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
