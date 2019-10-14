#ifndef NPP_PANEL_H_
#define NPP_PANEL_H_

#include <string>
#include <vector>
#include <ncursespp/view.h>

namespace npp {

class Window;
class Layout;
class Panel {
private:
  std::string id_;
  npp::View view_;
  npp::Layout* layout_ = nullptr;
  Panel* parent_ = nullptr;
  std::vector<Panel*> children_;
protected:
  void PrintOuter(npp::Window* window);
public:
  explicit Panel(std::string id = std::string());
  std::string Id() const { return id_; }
  std::string SetId(std::string id) { id_ = std::move(id); }
  virtual npp::Layout* Layout() const { return layout_; }
  void SetLayout(npp::Layout* layout) { layout_ = layout; }
  void AddChild(Panel* panel);
  bool RemoveChild(Panel* panel);
  std::vector<npp::Panel*> Children() const { return children_; }
  void Fit();
  npp::View View() const { return view_; }
  npp::View InnerView();
  void SetView(npp::View view) { view_ = view; }
  virtual void Print(npp::Window* window); // TODO (amir) maybe promote to PrintWriter class?
  void Clear(npp::Window* window);
};

class ScrollPanel : public Panel {
private:
  Panel right_scroll_;
  Panel bottom_scroll_;
  Panel center_panel_;
  void SetupPanels();
public:
  ScrollPanel();
  npp::Panel* MainPanel() { return &center_panel_; }
  void Print(npp::Window* window);
};

} // namespace nppp

#endif