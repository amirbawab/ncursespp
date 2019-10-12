#ifndef NPP_BUTTON_H_
#define NPP_BUTTON_H_

#include <ncursespp/panel.h>
#include <ncursespp/text.h>

namespace npp {

class Button : public Panel {
private:
  npp::Text text_;
public:
  explicit Button(std::string text = std::string());
  void SetText(std::string);
  void Print(npp::Window* window) override;
};

} // namespace npp

#endif