#ifndef NPP_TEXT_H_
#define NPP_TEXT_H_

#include <ncursespp/panel.h>
#include <ncursespp/gap_buffer/gap_buffer.h>
#include <utility>

namespace npp {

// TODO (amir) Experiment with wchar_t instead of char

class TextBuffer {
public:
  virtual void FromString(std::string) = 0;
  virtual const std::vector<std::vector<char>>& Value() = 0;
};

class CompressedTextBuffer : public TextBuffer {
private:
  std::vector<std::vector<char>> text_vector_;
public:
  void FromString(std::string text) override;
  const std::vector<std::vector<char>>& Value() override;
};

class GapTextBuffer : public TextBuffer {
private:
  GapBuffer<GapBuffer<char>> text_buffer_;
  std::vector<std::vector<char>> cached_text_vector_;
  bool polluted_ = true;
  void CacheValue();
public:
  void FromString(std::string text) override;
  const std::vector<std::vector<char>>& Value() override;
  // TODO Insert(), Remove(), etc ...
};

class Text : public Panel {
private:
  npp::CompressedTextBuffer text_buffer_;
public:
  explicit Text(std::string value = std::string());
  void SetValue(std::string value);
  void PrintInner(npp::Window* window) override;
};

} // namespace npp

#endif