#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include <ncursespp/layout.h>
#include <ncursespp/common.h>
#include <algorithm>

namespace npp {

Panel::Panel(std::string id) : id_(std::move(id)) {
  layout_ = new TileLayout();
}

void Panel::AddChild(npp::Panel *panel) {
  DCHECK_EQ(panel->parent_, nullptr);
  panel->parent_ = this;
  children_.push_back(panel);
}

bool Panel::RemoveChild(npp::Panel *panel) {
  auto find_panel = std::find(children_.begin(), children_.end(), panel);
  if(find_panel != children_.end()) {
    DCHECK_EQ(panel->parent_, this);
    panel->parent_ = nullptr;
    children_.erase(find_panel);
    return true;
  }
  return false;
}

void Panel::Fit() {
  if(!IsHidden()) {
    layout_->Fit(this);
    for(auto& child : children_) {
      child->Fit();
    }
  }
}

void Panel::Print(npp::Window* window) {
  if(!IsHidden()) {
    PrintOuter(window);
    PrintInner(window);
  }
}

void Panel::PrintOuter(npp::Window *window) {
  // We assume that panel has already been check
  // if it's hidden or not
  window->Printer()->DrawBorder(layout_->Border(), layout_->MarginView(this));
}

npp::View Panel::InnerView() {
  layout_->PaddingView(this);
}

void Panel::PrintInner(npp::Window *window) {
  for(auto& child : children_) {
    child->Print(window);
  }
}

void Panel::Clear(npp::Window *window) {
  window->Printer()->DrawEmptyView(view_);
}

ScrollPanel::ScrollPanel(int rows, int cols) : buffer_window_(new BufferWindow({0, 0, rows, cols})) {
  SetupPanels();
}

void ScrollPanel::SetupPanels() {
  auto sided_layout = new SidedLayout();
  AddChild(&right_scroll_);
  AddChild(&bottom_scroll_);
  AddChild(&center_panel_);
  sided_layout->SetSide(&right_scroll_, SidePanel::Right, 1);
  sided_layout->SetSide(&bottom_scroll_, SidePanel::Bottom, 1);
  sided_layout->SetSide(&center_panel_, SidePanel::Center, -1);
  SetLayout(sided_layout);
}

void ScrollPanel::AddChildToMainPanel(npp::Panel *panel) {
  center_panel_.AddChild(panel);
}

void ScrollPanel::PrintInner(npp::Window *window) {
  Panel::PrintInner(buffer_window_);

  // FIXME (amir) Temporary indicator of scroll panel
  CompressedTextBuffer vertical_text_buffer;
  vertical_text_buffer.FromString("Vertical Scroll");
  window->Printer()->DrawTextBuffer(&vertical_text_buffer, right_scroll_.InnerView());
  CompressedTextBuffer horizontal_text_buffer;
  horizontal_text_buffer.FromString("Horizontal Scroll");
  window->Printer()->DrawTextBuffer(&horizontal_text_buffer, bottom_scroll_.InnerView());

  // Use buffer on all descendant
  center_panel_.Print(buffer_window_);
  // Copy buffer to parent parent window
  window->Copy(buffer_window_, center_panel_.View());
}

} // namespace npp