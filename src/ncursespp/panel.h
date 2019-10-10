#ifndef NPP_PANEL_H_
#define NPP_PANEL_H_

#include <string>

namespace npp {

class Panel {
private:
  std::string id_;
public:
  explicit Panel() {}
  explicit Panel(std::string id) : id_(id) {}
  std::string Id() const { return id_; }
};

} // namespace nppp

#endif