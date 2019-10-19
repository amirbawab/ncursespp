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

} // namespace npp

#endif
