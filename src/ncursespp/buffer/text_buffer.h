#ifndef NPP_TEXT_BUFFER_H_
#define NPP_TEXT_BUFFER_H_

#include <ncursespp/buffer/gap_buffer.h>
#include <string>

namespace npp {

class TextBuffer {
public:
  virtual void FromString(std::u32string) = 0;
  virtual const std::vector <std::vector<char32_t>> &Value() = 0;
};

class CompressedTextBuffer : public TextBuffer {
private:
  std::vector <std::vector<char32_t>> text_vector_;
public:
  void FromString(std::u32string text) override;
  const std::vector <std::vector<char32_t>> &Value() override;
};

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
