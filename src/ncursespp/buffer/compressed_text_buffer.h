#ifndef NPP_COMPRESSED_TEXT_BUFFER_H_
#define NPP_COMPRESSED_TEXT_BUFFER_H_

#include <ncursespp/buffer/text_buffer.h>

namespace npp {

class CompressedTextBuffer : public TextBuffer {
private:
  std::vector <std::vector<char32_t>> text_vector_;
public:
  void FromString(std::u32string text) override;
  const std::vector <std::vector<char32_t>> &Value() override;
};

} // namespace npp

#endif
