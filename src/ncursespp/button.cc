#include <ncursespp/button.h>

namespace npp {

Button::Button(std::string text) : text_(std::move(text)) {
  AddChild(&text_);
}

void Button::SetText(std::string value) {
  text_.SetValue(std::move(value));
}

void Button::Print(npp::Window* window) {
  text_.Print(window);
}

} // namespace npp