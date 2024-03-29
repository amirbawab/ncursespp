#include <ncursespp/common.h>

namespace npp {

void Char32ToString(char32_t codepoint, std::string& out) {
  if (codepoint <= 0x7f) {
    out.append(1, static_cast<char>(codepoint));
  } else if (codepoint <= 0x7ff) {
    out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  } else if (codepoint <= 0xffff) {
    out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
    out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  } else {
    out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
    out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  }
}

void Char32VectorToString(const std::vector<char32_t>& codepoints, std::string& out) {
  for (char32_t codepoint : codepoints) {
    Char32ToString(codepoint, out);
  }
}

}