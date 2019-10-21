#include <ncursespp/buffer/gap_text_buffer.h>

namespace npp {

GapTextBuffer::GapTextBuffer() {
  NewLine();
}

npp::Cursor GapTextBuffer::Cursor() {
  auto y = text_buffer_.GapBegin();
  // There should always be at least one element
  // before the beginning of the gap
  DCHECK_GE(y, 1);
  y -= 1;
  auto current_line = text_buffer_.At(y);
  auto x = current_line->GapBegin();
  return {x, y};
}

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

void GapTextBuffer::Move(npp::Cursor cursor) {
  // Fix cursor data
  cursor.y = std::max(cursor.y, 1lu);
  DCHECK_GE(text_buffer_.ValueSize(), 1);
  text_buffer_.MoveIndex(cursor.y);
  GapBuffer<char32_t>* line = text_buffer_.At(cursor.y);
  line->MoveIndex(cursor.x);
}

void GapTextBuffer::Insert(std::u32string text) {
  auto cursor = Cursor();
  polluted_ = true;
  text_buffer_.At(cursor.y)->Insert(std::vector<char32_t>(text.begin(), text.end()));
}

void GapTextBuffer::NewLine() {
  text_buffer_.Insert({GapBuffer<char32_t>()});
}

} // namespace npp