#ifndef NPP_BUFFER_WINDOW_H_
#define NPP_BUFFER_WINDOW_H_

#include <ncursespp/window/window.h>

namespace npp {

class BufferWindow : public Window {
private:
  std::vector<std::vector<char32_t>> window_buffer_;
  npp::View view_;
  void SetupWindow();
public:
  explicit BufferWindow(npp::View view, WindowOptions options = WindowOptions());
  npp::View View() const override { return view_; };
  char32_t& CharAt(Point point);
  std::vector<char32_t>& RowAt(int y);
  void SetPoint(Point point);
  void Copy(BufferWindow* buffer_window, npp::View view) override;
};

} // namespace npp

#endif
