#ifndef NPP_INPUT_H_
#define NPP_INPUT_H_

#include <ncursespp/panel/panel.h>
#include <ncursespp/buffer/gap_text_buffer.h>

namespace npp {

class Input : public Panel {
private:
  GapTextBuffer text_buffer_;
public:
  void PrintInner(npp::Window* window) override;
  GapTextBuffer& Text() { return text_buffer_; }
};

} // namespace npp

#endif
