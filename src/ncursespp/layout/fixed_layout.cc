#include <ncursespp/layout/fixed_layout.h>
#include <ncursespp/common.h>

namespace npp {

void FixedLayout::SetFixedView(npp::Panel *panel, npp::View view) {
  fixed_panels_[panel] = view;
}

npp::View FixedLayout::PanelFixedView(npp::Panel *panel) {
  if(fixed_panels_.find(panel) != fixed_panels_.end()) {
    return fixed_panels_[panel];
  }
  // Default, view is non-existent
  // TODO Replace with INVISIBLE_VIEW
  return {0, 0, 0, 0};
}

void FixedLayout::Fit(npp::Panel *panel) {
  auto children = panel->Children();
  uint64_t count_panels = children.size();
  for(auto i=0; i < count_panels; i++) {
    auto child_panel = children[i];
    auto child_panel_view = PanelFixedView(child_panel);
    DCHECK_GE(child_panel_view.x, 0);
    DCHECK_GE(child_panel_view.y, 0);
    if(child_panel_view.rows > 0 && child_panel_view.cols > 0) {
      child_panel->SetHidden(false);
      child_panel->SetView(child_panel_view);
    } else {
      child_panel->SetHidden(true);
    }
  }
}

} // namespace npp