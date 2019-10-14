#include <ncursespp/text.h>
#include <ncursespp/window.h>

namespace npp {

void TextBuffer::FromString(std::string text) {
  size_t text_length = text.size();
  size_t text_index = 0;
  while (text_index < text_length) {
    GapBuffer<char> line_buffer;
    size_t new_line_index = text.find('\n', text_index);
    size_t end_line = new_line_index != std::string::npos ? new_line_index : text_length;
    std::string line_text = text.substr(text_index, end_line - text_index);
    std::vector<char> line_chars(line_text.begin(), line_text.end());
    line_buffer.Insert(line_chars);
    Insert({line_buffer});
    text_index = end_line + (new_line_index != std::string::npos ? 1 : 0);
  }
}

Text::Text(std::string value) {
  SetValue(std::move(value));
}

void Text::SetValue(std::string value) {
  text_buffer_.FromString(std::move(value));
}

void Text::Print(npp::Window* window) {
  auto inner_view = InnerView();
  window->Printer()->DrawTextBuffer(text_buffer_, inner_view);
}

} // namespace npp