#include <ncursespp/buffer/compressed_text_buffer.h>

namespace npp {

void CompressedTextBuffer::FromString(std::u32string text) {
  text_vector_.clear();
  size_t text_length = text.size();
  size_t text_index = 0;
  while (text_index < text_length) {
    size_t new_line_index = text.find('\n', text_index);
    size_t end_line = new_line_index != std::u32string::npos ? new_line_index : text_length;
    std::u32string line_text = text.substr(text_index, end_line - text_index);
    std::vector<char32_t > line_chars(line_text.begin(), line_text.end());
    text_vector_.push_back(line_chars);
    text_index = end_line + (new_line_index != std::u32string::npos ? 1 : 0);
  }
}

const std::vector<std::vector<char32_t >>& CompressedTextBuffer::Value() {
  return text_vector_;
}

} // namespace npp
