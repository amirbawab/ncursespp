#ifndef NPP_GAP_BUFFER_H_
#define NPP_GAP_BUFFER_H_

#include <vector>
#include <cinttypes>
#include <cassert>

namespace npp {

template <class T>
class GapBuffer {
private:
  std::vector<T> buffer_;
  uint64_t gap_begin_;
  uint64_t gap_end_;
  uint64_t additional_gap_;

  /**
   * Resize buffer
   * @param new_size
   */
  void Resize(uint64_t new_size) {
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
public:
  explicit GapBuffer(uint64_t initial_size = 100, uint64_t additional_gap = 50) : buffer_(initial_size) {
    gap_begin_ = 0;
    gap_end_ = buffer_.size();
    additional_gap_ = additional_gap;
  }

  /**
   * Move gap to previous position {count} times
   * @param count
   * @return Number of position moved
   */
  uint64_t MovePrevious(uint64_t count) {
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

  /**
   * Move gap to next position {count} times
   * @param count
   * @return Number of position moved
   */
  uint64_t MoveNext(uint64_t count) {
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

  /**
   * Move to {index} position
   * @param index
   * @return Gap begin
   */
  uint64_t MoveIndex(uint64_t index) {
    if(index <= gap_begin_) {
      MovePrevious(gap_begin_ - index);
    } else {
      MoveNext(index - gap_begin_);
    }
    return gap_begin_;
  }

  /**
   * Move to first position
   * @return Gap begin
   */
  uint64_t MoveBegin() {
    return MoveIndex(0);
  }

  /**
   * Move to last position
   * @return Gap begin
   */
  uint64_t MoveEnd() {
    return MoveIndex(0xffffffffffffffff);
  }

  /**
   * Insert a vector of {T}
   * @param val Vector of {T}
   */
  void Insert(std::vector<T> val) {
    auto val_len = val.size();
    if(val_len == 0) return;
    // Resize if necessary
    auto future_gap_begin = gap_begin_ + val_len;
    if(future_gap_begin > gap_end_) {
      Resize(buffer_.size() + additional_gap_);
    }
    // Copy argument value into buffer
    std::copy(val.begin(), val.end(), buffer_.begin() + gap_begin_);
    gap_begin_ = future_gap_begin;
  }

  /**
   * Delete {count} elements
   * @param count
   */
  void Delete(uint64_t count) {
    if(count > gap_begin_) {
      count = gap_begin_;
    }
    gap_begin_ -= count;
  }

  /**
   * Value vector excluding gap
   * @return vector
   */
  std::vector<T> Value() {
    std::vector<T> result;
    result.insert(result.end(), buffer_.begin(), buffer_.begin() + gap_begin_);
    result.insert(result.end(), buffer_.begin() + gap_end_, buffer_.end());
    return result;
  }

  /**
   * Buffer with gap
   * @return vector
   */
  std::vector<T> Buffer() {
    return buffer_;
  }
};

}; // namespace npp

#endif