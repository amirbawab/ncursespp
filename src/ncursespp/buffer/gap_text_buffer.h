#ifndef NPP_GAP_TEXT_BUFFER_H_
#define NPP_GAP_TEXT_BUFFER_H_

#include <ncursespp/buffer/text_buffer.h>
#include <ncursespp/common.h>

namespace npp {

struct Cursor {
  uint64_t x;
  uint64_t y;
};

class GapTextBuffer : public TextBuffer {
private:
  GapBuffer <GapBuffer<char32_t>> text_buffer_;
  std::vector <std::vector<char32_t>> cached_text_vector_;
  bool polluted_ = true;
  void CacheValue();
public:
  GapTextBuffer();
  void FromString(std::u32string text) override;
  const std::vector <std::vector<char32_t>> &Value() override;
  void Move(npp::Cursor cursor);
  npp::Cursor Cursor();
  void Insert(std::u32string text);
  void NewLine();
  // TODO Insert(), Remove(), etc ...
};

} // namespace npp

#endif
