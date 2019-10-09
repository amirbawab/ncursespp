#ifndef NPP_GAP_BUFFER_H_
#define NPP_GAP_BUFFER_H_

#include <vector>
#include <string>

namespace npp {

class GapBuffer {
private:
  std::vector<char> buffer_;
  uint64_t gap_begin_;
  uint64_t gap_end_;
  void Resize(uint64_t new_size);
public:
  GapBuffer();
  uint64_t MoveLeft(uint64_t count);
  uint64_t MoveRight(uint64_t count);
  uint64_t MoveIndex(uint64_t index);
  uint64_t MoveBegin();
  uint64_t MoveEnd();
  void Insert(std::string val);
  void Delete(uint64_t count);
  std::string Value();
  std::string DebugValue();
};

} // namespace npp

#endif