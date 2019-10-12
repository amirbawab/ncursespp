#include <ncursespp/window.h>
#include <ncursespp/panel.h>
#include <ncursespp/layout.h>
#include <ncursespp/common.h>
#include <algorithm>

namespace npp {

Panel::Panel(std::string id) : id_(id) {
  // FIXME (amir) default to tile layout
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
  layout_->Fit(this);
  for(auto& child : children_) {
    child->Fit();
  }
}

void Panel::PrintOuter(npp::Window *window) {
  window->Printer().DrawBorder(layout_->Border(), layout_->MarginView(this));
}

npp::View Panel::InnerView() {
  layout_->PaddingView(this);
}

void Panel::Print(npp::Window* window) {
  PrintOuter(window);
  for(auto& child : children_) {
    child->Print(window);
  }
}

void Panel::Clear(npp::Window *window) {
  window->Printer().DrawEmptyView(view_);
}

} // namespace npp