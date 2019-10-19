#include <ncursespp/panel/panel.h>
#include <ncursespp/window/window.h>
#include <ncursespp/layout/tile_layout.h>
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

} // namespace npp