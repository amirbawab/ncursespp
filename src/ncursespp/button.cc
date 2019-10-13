#include <ncursespp/button.h>
#include <ncursespp/layout.h>

namespace npp {

Button::Button(std::string text) : text_(std::move(text)) {
  AddChild(&text_);

  // Add thin button border
  Borders borders;
  borders.top.style = SolidThin;
  borders.left.style = SolidThin;
  borders.bottom.style = SolidThin;
  borders.right.style = SolidThin;
  Layout()->SetBorder(borders);
}

void Button::SetText(std::string value) {
  text_.SetValue(std::move(value));
}

void Button::Print(npp::Window* window) {
  PrintOuter(window);
  text_.Print(window);
}

} // namespace npp