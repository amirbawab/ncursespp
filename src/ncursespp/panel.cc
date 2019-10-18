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
    FitOuter();
    FitInner();
  }
}

void Panel::FitOuter() {
  layout_->Fit(this);
}

void Panel::FitInner() {
  for(auto& child : children_) {
    child->Fit();
  }
}

void Panel::Print(npp::Window *window_outer, npp::Window *window_inner) {
  if(!IsHidden()) {
    PrintOuter(window_outer);
    PrintInner(window_inner);
  }
}

void Panel::PrintOuter(npp::Window *window) {
  window->Printer()->DrawBorder(layout_->Border(), layout_->MarginView(this));
}

void Panel::PrintInner(npp::Window *window) {
  for(auto& child : children_) {
    child->Print(window, window);
  }
}

npp::View Panel::InnerView() {
  layout_->PaddingView(this);
}

void Panel::Clear(npp::Window *window) {
  window->Printer()->DrawEmptyView(view_);
  for(auto& child : children_) {
    child->Clear(window);
  }
}

ScrollPanel::ScrollPanel(int rows, int cols) : buffer_window_(new BufferWindow({0, 0, rows, cols})) {
  SetupPanels();
}

void ScrollPanel::SetupPanels() {

  // Scroll panel layout and children
  sided_layout_ = new SidedLayout();
  AddChild(&right_scroll_);
  AddChild(&bottom_scroll_);
  AddChild(&center_panel_);
  sided_layout_->SetSide(&right_scroll_, SidePanel::Right, 1);
  sided_layout_->SetSide(&bottom_scroll_, SidePanel::Bottom, 1);
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
  right_scroll_.Print(window, window);
  bottom_scroll_.Print(window, window);
  center_panel_.Print(window, buffer_window_);

  // FIXME (amir) Temporary indicator of scroll panel
  {
    CompressedTextBuffer vertical_text_buffer;
    vertical_text_buffer.FromString(U"Vertical Scroll");
    window->Printer()->DrawTextBuffer(&vertical_text_buffer, right_scroll_.InnerView());
    CompressedTextBuffer horizontal_text_buffer;
    horizontal_text_buffer.FromString(U"Horizontal Scroll");
    window->Printer()->DrawTextBuffer(&horizontal_text_buffer, bottom_scroll_.InnerView());
  }

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