#include <ncursespp/panel/text.h>
#include <ncursespp/window/window.h>

namespace npp {

Text::Text(std::u32string value) {
  SetValue(std::move(value));
}

void Text::SetValue(std::u32string value) {
  text_buffer_.FromString(std::move(value));
}

void Text::PrintInner(npp::Window* window) {
  auto inner_view = InnerView();
  window->Printer()->DrawTextBuffer(&text_buffer_, inner_view);
}

} // namespace npp