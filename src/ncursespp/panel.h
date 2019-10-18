#ifndef NPP_PANEL_H_
#define NPP_PANEL_H_

#include <string>
#include <vector>
#include <ncursespp/view.h>

namespace npp {

class Window;
class BufferWindow;
class Layout;
class SidedLayout;
class FixedLayout;
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
  void Print(npp::Window* window);
  void SetHidden(bool hidden) { hidden_ = hidden; }
  bool IsHidden() const { return hidden_; }
  virtual void Clear(npp::Window* window);
};

class ScrollPanel : public Panel {
private:
  Panel right_scroll_;
  Panel bottom_scroll_;
  // Center panel is simply an intermediate panel
  // It should NOT be used to add children outside
  // this class. This panel can be used to add border
  // or to add panel within the window buffer
  Panel center_panel_;
  Panel window_panel_;
  npp::SidedLayout* sided_layout_ = nullptr;
  npp::FixedLayout* fixed_layout_ = nullptr;
  npp::BufferWindow* buffer_window_;
  void SetupPanels();
protected:
  void PrintInner(npp::Window* window) override;
  void FitInner() override;
public:
  ScrollPanel(int rows, int cols);
  npp::Panel* MainPanel() { return &window_panel_; }
  void AddChildToMainPanel(Panel* panel);
  void Clear(npp::Window* window);
};

} // namespace nppp

#endif