#ifndef NPP_BUTTON_H_
#define NPP_BUTTON_H_

#include <ncursespp/panel.h>
#include <ncursespp/text.h>

namespace npp {

class Button : public Panel {
private:
  npp::Text text_;
public:
  explicit Button(std::u32string text = std::u32string());
  void SetText(std::u32string);
  void PrintInner(npp::Window* window) override;
};

} // namespace npp

#endif