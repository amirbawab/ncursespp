#ifndef NPP_VIEW_H_
#define NPP_VIEW_H_

#include <cinttypes>

namespace npp {

struct View {
  uint64_t x;
  uint64_t y;
  uint64_t rows;
  uint64_t cols;
};

} // namespace npp

#endif