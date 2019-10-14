#ifndef NPP_TEXT_H_
#define NPP_TEXT_H_

#include <ncursespp/panel.h>
#include <ncursespp/gap_buffer/gap_buffer.h>
#include <utility>

namespace npp {

class TextBuffer : public GapBuffer<GapBuffer<char>> {
public:
  void FromString(std::string text);
};

class Text : public Panel {
private:
  npp::TextBuffer text_buffer_;
public:
  explicit Text(std::string value = std::string());
  void SetValue(std::string value);
  void Print(npp::Window* window) override;
};

} // namespace npp

#endif