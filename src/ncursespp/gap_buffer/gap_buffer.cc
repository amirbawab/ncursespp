#include <ncursespp/gap_buffer/gap_buffer.h>
#include <ncursespp/common.h>
#include <cassert>

namespace npp {

#define INITIAL_BUFFER_SIZE 100
#define ADDITIONAL_GAP_SIZE 50

GapBuffer::GapBuffer() : buffer_(INITIAL_BUFFER_SIZE) {
  gap_begin_ = 0;
  gap_end_ = buffer_.size();
}

void GapBuffer::Resize(uint64_t new_size) {
  uint64_t old_size = buffer_.size();
  assert(new_size > old_size);
  buffer_.resize(new_size);
  uint64_t after_gap = old_size - gap_end_;
  uint64_t new_gap_end = new_size - after_gap;
  for(auto i=0; i < after_gap; i++) {
    buffer_[new_gap_end+i] = buffer_[gap_end_+i];
  }
  gap_end_ = new_gap_end;
}

void GapBuffer::Insert(std::string val) {
  auto val_len = val.size();
  if(val_len == 0) return;
  // Resize if necessary
  auto future_gap_begin = gap_begin_ + val_len;
  if(future_gap_begin > gap_end_) {
    Resize(buffer_.size() + ADDITIONAL_GAP_SIZE);
  }
  // Copy argument value into buffer
  std::copy(val.begin(), val.end(), buffer_.begin() + gap_begin_);
  gap_begin_ = future_gap_begin;
}

void GapBuffer::Delete(uint64_t count) {
  if(count > gap_begin_) {
    count = gap_begin_;
  }
  gap_begin_ -= count;
}

std::string GapBuffer::Value() {
  std::string left = std::string(buffer_.begin(), buffer_.begin() + gap_begin_);
  std::string right = std::string(buffer_.begin() + gap_end_, buffer_.end());
  return left + right;
}

uint64_t GapBuffer::MoveLeft(uint64_t count) {
  uint64_t future_gap_begin = gap_begin_ - count;
  // Detect overflow
  if(future_gap_begin > gap_begin_) {
    count = gap_begin_;
  }
  // Start copying
  for(int i=0; i < count; i++) {
    buffer_[gap_end_-1-i] = buffer_[gap_begin_-1-i];
  }
  gap_begin_ -= count;
  gap_end_ -= count;
  return count;
}

uint64_t GapBuffer::MoveRight(uint64_t count) {
  uint64_t future_gap_end = gap_end_ + count;
  // Detect overflow
  if(future_gap_end < gap_end_ || future_gap_end > buffer_.size()) {
    count = buffer_.size() - gap_end_;
  }
  // Start copying
  for(int i=0; i < count; i++) {
    buffer_[gap_begin_+i] = buffer_[gap_end_+i];
  }
  gap_begin_ += count;
  gap_end_ += count;
  return count;
}

uint64_t GapBuffer::MoveIndex(uint64_t index) {
  if(index <= gap_begin_) {
    MoveLeft(gap_begin_ - index);
  } else {
    MoveRight(index - gap_begin_);
  }
  return gap_begin_;
}

uint64_t GapBuffer::MoveBegin() {
  return MoveIndex(0);
}

uint64_t GapBuffer::MoveEnd() {
  return MoveIndex(0xffffffffffffffff);
}

std::string GapBuffer::DebugValue() {
  std::string left = std::string(buffer_.begin(), buffer_.begin() + gap_begin_);
  std::string gap = std::string(gap_end_ - gap_begin_, ' ');
  if(gap.size() == 1) {
    gap[0] = '#';
  } else if(!gap.empty()) {
    gap[0] = '[';
    gap[gap.size()-1] = ']';
  }
  std::string right = std::string(buffer_.begin() + gap_end_, buffer_.end());
  return left + gap + right;
}

} // namespace npp