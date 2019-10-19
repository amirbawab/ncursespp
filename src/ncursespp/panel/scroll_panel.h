#ifndef NPP_SCROLL_PANEL_H_
#define NPP_SCROLL_PANEL_H_

#include <ncursespp/panel/panel.h>

namespace npp {

class SidedLayout;
class FixedLayout;
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

} // namespace npp

#endif
