#ifndef NPP_GAP_TEXT_BUFFER_H_
#define NPP_GAP_TEXT_BUFFER_H_

#include <ncursespp/buffer/text_buffer.h>

namespace npp {

class GapTextBuffer : public TextBuffer {
private:
  GapBuffer <GapBuffer<char32_t>> text_buffer_;
  std::vector <std::vector<char32_t>> cached_text_vector_;
  bool polluted_ = true;
  void CacheValue();
public:
  void FromString(std::u32string text) override;
  const std::vector <std::vector<char32_t>> &Value() override;
  // TODO Insert(), Remove(), etc ...
};

} // namespace npp

#endif
