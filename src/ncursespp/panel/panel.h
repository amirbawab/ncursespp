#ifndef NPP_PANEL_H_
#define NPP_PANEL_H_

#include <string>
#include <vector>
#include <ncursespp/view.h>

namespace npp {

class Window;
class BufferWindow;
class Layout;
class Panel {
private:
  std::string id_;
  npp::View view_;
  npp::Layout* layout_ = nullptr;
  Panel* parent_ = nullptr;
  std::vector<Panel*> children_;
  bool hidden_ = false;
  void PrintOuter(npp::Window* window);
  void FitOuter();
protected:
  virtual void PrintInner(npp::Window* window);
  virtual void FitInner();
public:
  explicit Panel(std::string id = std::string());
  std::string Id() const { return id_; }
  void SetId(std::string id) { id_ = std::move(id); }
  npp::Layout* Layout() const { return layout_; }
  void SetLayout(npp::Layout* layout) { layout_ = layout; }
  void AddChild(Panel* panel);
  bool RemoveChild(Panel* panel);
  std::vector<npp::Panel*> Children() const { return children_; }
  void Fit();
  npp::View View() const { return view_; }
  npp::View InnerView();
  void SetView(npp::View view) { view_ = view; }
  void Print(npp::Window* window_outer, npp::Window* window_inner);
  void SetHidden(bool hidden) { hidden_ = hidden; }
  bool IsHidden() const { return hidden_; }
  virtual void Clear(npp::Window* window);
};

} // namespace nppp

#endif