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
  auto rows = static_cast<size_t>(view_.rows);
  auto cols = static_cast<size_t >(view_.cols);
  window_buffer_.resize(rows, std::vector<char32_t>(cols, ' '));
  window_attributes_.resize(rows, std::vector<unsigned>(cols, 0));

}

char32_t &BufferWindow::CharAt(npp::Point point) {
  auto row = RowAt(point.y);
  DCHECK_GE(point.x, 0);
  DCHECK_LT(point.x, window_buffer_[point.y].size());
  return row[point.x];
}

std::vector<char32_t> &BufferWindow::RowAt(int y) {
  DCHECK_GE(y, 0);
  DCHECK_LT(y, window_buffer_.size());
  return window_buffer_[y];
}

unsigned& BufferWindow::AttributeAt(npp::Point point) {
  auto row = AttributesAt(point.y);
  DCHECK_GE(point.x, 0);
  DCHECK_LT(point.x, window_buffer_[point.y].size());
  return row[point.x];
}

std::vector<unsigned>& BufferWindow::AttributesAt(int y) {
  DCHECK_GE(y, 0);
  DCHECK_LT(y, window_attributes_.size());
  return window_attributes_[y];
}

void BufferWindow::SetPoint(npp::Point point) {
  view_.x = point.x;
  view_.y = point.y;
}

void BufferWindow::Copy(npp::BufferWindow *buffer_window, npp::View view) {
  // TODO (amir) to implement
}

} // namespace npp
