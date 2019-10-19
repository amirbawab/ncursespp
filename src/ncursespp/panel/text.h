#ifndef NPP_TEXT_H_
#define NPP_TEXT_H_

#include <ncursespp/panel/panel.h>
#include <ncursespp/buffer/compressed_text_buffer.h>

namespace npp {

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