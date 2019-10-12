#ifndef NPP_TEXT_H_
#define NPP_TEXT_H_

#include <ncursespp/panel.h>

namespace npp {

class Text : public Panel {
private:
  std::string value_;
public:
  explicit Text(std::string value = std::string()) : value_(std::move(value)) {}
  void SetValue(std::string value) { value_ = value; }
  void Print(npp::Window* window) override;
};

} // namespace npp

#endif