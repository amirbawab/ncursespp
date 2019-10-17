#ifndef NPP_TEXT_H_
#define NPP_TEXT_H_

#include <ncursespp/panel.h>
#include <ncursespp/gap_buffer/gap_buffer.h>
#include <utility>

namespace npp {

// TODO (amir) Experiment with wchar_t instead of char

class TextBuffer {
public:
  virtual void FromString(std::u32string) = 0;
  virtual const std::vector<std::vector<char32_t>>& Value() = 0;
};

class CompressedTextBuffer : public TextBuffer {
private:
  std::vector<std::vector<char32_t>> text_vector_;
public:
  void FromString(std::u32string text) override;
  const std::vector<std::vector<char32_t>>& Value() override;
};

class GapTextBuffer : public TextBuffer {
private:
  GapBuffer<GapBuffer<char32_t>> text_buffer_;
  std::vector<std::vector<char32_t>> cached_text_vector_;
  bool polluted_ = true;
  void CacheValue();
public:
  void FromString(std::u32string text) override;
  const std::vector<std::vector<char32_t>>& Value() override;
  // TODO Insert(), Remove(), etc ...
};

class Text : public Panel {
private:
  npp::CompressedTextBuffer text_buffer_;
public:
  explicit Text(std::u32string value = std::u32string());
  void SetValue(std::u32string value);
  void PrintInner(npp::Window* window) override;
};

} // namespace npp

#endif