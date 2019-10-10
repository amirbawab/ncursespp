#ifndef NPP_PANEL_H_
#define NPP_PANEL_H_

#include <string>
#include <vector>
#include <ncursespp/view.h>

namespace npp {

class Layout;
class Panel {
private:
  std::string id_;
  npp::View view_;
  npp::Layout* layout_ = nullptr;
  Panel* parent_ = nullptr;
  std::vector<Panel*> children_;
public:
  explicit Panel(std::string id = std::string());
  std::string Id() const { return id_; }
  npp::Layout* Layout() const { return layout_; }
  void SetLayout(npp::Layout* layout) { layout_ = layout; }
  void AddChild(Panel* panel);
  bool RemoveChild(Panel* panel);
  std::vector<npp::Panel*> Children() const { return children_; }
  void Fit();
  npp::View View() const { return view_; }
  void SetView(npp::View view) { view_ = view; }
};

} // namespace nppp

#endif