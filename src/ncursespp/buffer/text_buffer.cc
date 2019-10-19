#include <ncursespp/buffer/text_buffer.h>

namespace npp {

void GapTextBuffer::CacheValue() {
  // Erase old data
  cached_text_vector_.clear();
  // Reconstruct data
  auto gap_buffer_value = text_buffer_.Value();
  auto gap_buffer_lines = gap_buffer_value.size();
  for(auto i=0; i < gap_buffer_lines; i++) {
    cached_text_vector_.push_back(gap_buffer_value[i].Value());
  }
}

void GapTextBuffer::FromString(std::u32string text) {
  size_t text_length = text.size();
  size_t text_index = 0;
  while (text_index < text_length) {
    GapBuffer<char32_t > line_buffer;
    size_t new_line_index = text.find('\n', text_index);
    size_t end_line = new_line_index != std::u32string::npos ? new_line_index : text_length;
    std::u32string line_text = text.substr(text_index, end_line - text_index);
    std::vector<char32_t> line_chars(line_text.begin(), line_text.end());
    line_buffer.Insert(line_chars);
    text_buffer_.Insert({line_buffer});
    text_index = end_line + (new_line_index != std::u32string::npos ? 1 : 0);
  }
}

const std::vector<std::vector<char32_t>>& GapTextBuffer::Value() {
  if(polluted_) {
    CacheValue();
    polluted_ = false;
  }
  return cached_text_vector_;
}

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