#include <ncursespp/panel/scroll_panel.h>
#include <ncursespp/panel/text.h>
#include <ncursespp/window/buffer_window.h>
#include <ncursespp/layout/sided_layout.h>
#include <ncursespp/layout/fixed_layout.h>
#include <ncursespp/common.h>

namespace npp {

class ScrollerPanel : public Panel {
private:
  Orientation orientation_;
  float value_ = 0.0f;
public:
  explicit ScrollerPanel(Orientation orientation) : orientation_(orientation) {}
  void SetValue(float value) {
    value_ = std::max(value, 0.0f);
    value_ = std::min(value_, 1.0f);
  }
  float Value() const { return value_; }
  void PrintInner(npp::Window* window) override {
    auto inner_view = InnerView();

    int y_begin = inner_view.y;
    int y_end, width;
    if(orientation_ == Horizontal) {
      y_end = y_begin + inner_view.rows;
      width = (int) (inner_view.cols * value_);
    } else {
      assert(orientation_ == Vertical);
      y_end = y_begin + (int)(inner_view.rows * value_);
      width = inner_view.cols;
    }
    for(auto y=y_begin; y < y_end; y++) {
      window->Printer()->DrawChar32Vector({inner_view.x, y}, std::vector<char32_t>(width, 0x2588));
    }
  }
};

ScrollPanel::ScrollPanel(int rows, int cols) : buffer_window_(new BufferWindow({0, 0, rows, cols})) {
  right_scroller_ = new ScrollerPanel(Vertical);
  bottom_scroller_ = new ScrollerPanel(Horizontal);
  SetupPanels();
}

void ScrollPanel::SetupPanels() {

  // Scroll panel layout and children
  sided_layout_ = new SidedLayout();
  AddChild(right_scroller_);
  AddChild(bottom_scroller_);
  AddChild(&center_panel_);
  sided_layout_->SetSide(right_scroller_, SidePanel::Right, 2);
  sided_layout_->SetSide(bottom_scroller_, SidePanel::Bottom, 1);
  sided_layout_->SetSide(&center_panel_, SidePanel::Center, -1);
  SetLayout(sided_layout_);

  // Center panel layout and child
  fixed_layout_ = new FixedLayout();
  center_panel_.AddChild(&window_panel_);
  center_panel_.SetLayout(fixed_layout_);
}

void ScrollPanel::AddChildToMainPanel(npp::Panel *panel) {
  MainPanel()->AddChild(panel);
}

void ScrollPanel::PrintInner(npp::Window *window) {
  right_scroller_->Print(window, window);
  bottom_scroller_->Print(window, window);
  center_panel_.Print(window, buffer_window_);

  // Copy buffer to parent parent window
  window->Copy(buffer_window_, center_panel_.InnerView());
}

void ScrollPanel::FitInner() {
  // TODO (amir) Find a better way to set this (maybe a ScrollLayout extending SidedLayout?)
  // TODO (amir) Need to consider moving the window vertically and horizontally
  {
    // Configure layouts
    auto center_panel_inner_view = center_panel_.InnerView();
    buffer_window_->SetPoint({center_panel_inner_view.x, center_panel_inner_view.y});
    auto window_view = buffer_window_->View();
    fixed_layout_->SetFixedView(&window_panel_, {center_panel_inner_view.x, center_panel_inner_view.y,
                                                 std::min(window_view.rows, center_panel_inner_view.rows),
                                                 std::min(window_view.cols, center_panel_inner_view.cols)});
  }

  // Run Fit() on each of the children
  // in order to fit their children
  for(auto &child : Children()) {
    child->Fit();
  }
}

void ScrollPanel::Clear(npp::Window *window) {
  window->Printer()->DrawEmptyView(this->View());
  buffer_window_->Printer()->DrawEmptyView(this->View());
  auto children = Children();
  for(auto& child : children) {
    child->Clear(buffer_window_);
  }
}

} // namespace npp