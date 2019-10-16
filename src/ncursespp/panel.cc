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
    FitInner();
  }
}

void Panel::FitInner() {
  layout_->Fit(this);
  for(auto& child : children_) {
    child->Fit();
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

  // FIXME (amir) temporary panel indicator
  {
    Borders solid_borders;
    solid_borders.top.style = SolidThin;
    solid_borders.left.style = SolidThin;
    solid_borders.bottom.style = SolidThin;
    solid_borders.right.style = SolidThin;
    center_panel_.Layout()->SetBorder(solid_borders);
    window_panel_.Layout()->SetBorder(solid_borders);
  }
}

void ScrollPanel::AddChildToMainPanel(npp::Panel *panel) {
  center_panel_.AddChild(panel);
}

void ScrollPanel::PrintInner(npp::Window *window) {
  right_scroll_.Print(window);
  bottom_scroll_.Print(window);

  // TODO (amir) Find a better way to call FitInner(window) and FitOuter(buffer_window) (Maybe modify Fit(win1, wind2)?)
  {
    // Center panel content is printed on the buffer
    // and the outer border on the parent's window
    window->Printer()->DrawBorder(center_panel_.Layout()->Border(), center_panel_.Layout()->MarginView(&center_panel_));
    for(auto &child : center_panel_.Children()) {
      child->Print(buffer_window_);
    }
  }

  // FIXME (amir) Temporary indicator of scroll panel
  {
    CompressedTextBuffer vertical_text_buffer;
    vertical_text_buffer.FromString("Vertical Scroll");
    window->Printer()->DrawTextBuffer(&vertical_text_buffer, right_scroll_.InnerView());
    CompressedTextBuffer horizontal_text_buffer;
    horizontal_text_buffer.FromString("Horizontal Scroll");
    window->Printer()->DrawTextBuffer(&horizontal_text_buffer, bottom_scroll_.InnerView());
  }

  // Copy buffer to parent parent window
  window->Copy(buffer_window_, center_panel_.View());
}

void ScrollPanel::FitInner() {
  // TODO (amir) Find a better way to set this (maybe a ScrollLayout extending SidedLayout?)
  // TODO (amir) Need to consider moving the window vertically and horizontally
  {
    // Configure layouts
    auto panel_inner_view = center_panel_.InnerView();
    auto window_view = buffer_window_->View();
    buffer_window_->SetPoint({panel_inner_view.x, panel_inner_view.y});
    fixed_layout_->SetFixedView(&window_panel_, {panel_inner_view.x, panel_inner_view.y,
                                                 std::min(window_view.rows, panel_inner_view.rows),
                                                 std::min(window_view.cols, panel_inner_view.cols)});
  }
  Panel::FitInner();
}

} // namespace npp