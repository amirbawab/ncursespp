#include <ncursespp/layout/sided_layout.h>
#include <ncursespp/common.h>

namespace npp {

SidePanel SidedLayout::PanelSidePanel(npp::Panel *panel, uint32_t *side_flags) {
  if(sides_.find(panel) != sides_.end() && ((static_cast<uint32_t >(sides_[panel].side) & *side_flags) == 0)) {
    *side_flags |= static_cast<uint32_t >(sides_[panel].side);
    return sides_[panel];
  }
  // Default hidden
  return {SidePanel::Side::Hidden, 0};
}

void SidedLayout::SetSide(Panel* panel, npp::SidePanel::Side side, int length) {
  sides_[panel] = {side, length};
}

void SidedLayout::Fit(npp::Panel *panel) {
  auto children = panel->Children();
  uint64_t count_sides = children.size();

  // Fetch the various panels
  uint32_t side_flags = 0;
  Panel* left_panel = nullptr;
  Panel* center_panel = nullptr;
  Panel* right_panel = nullptr;
  Panel* top_panel = nullptr;
  Panel* bottom_panel = nullptr;
  for(auto i=0; i < count_sides; i++) {
    auto child_side_panel = PanelSidePanel(children[i], &side_flags);
    switch (child_side_panel.side) {
      case SidePanel::Side::Top:
        top_panel = children[i];
        break;
      case SidePanel::Side::Left:
        left_panel = children[i];
        break;
      case SidePanel::Side::Bottom:
        bottom_panel = children[i];
        break;
      case SidePanel::Side::Right:
        right_panel = children[i];
        break;
      case SidePanel::Side::Center: {
        center_panel = children[i];
        break;
      }
      default:
        DCHECK_EQ(child_side_panel.side, SidePanel::Side::Hidden);
        children[i]->SetHidden(true);
        break;
    }
  }

  // Fit side panels. Order is important!
  auto panel_inner_view = panel->InnerView();
  if(top_panel) {
    auto top_panel_length = sides_[top_panel].length;
    if(panel_inner_view.rows >= top_panel_length && panel_inner_view.cols > 0) {
      auto top_panel_view = panel_inner_view;
      top_panel_view.rows = top_panel_length;
      top_panel->SetView(top_panel_view);
      top_panel->SetHidden(false);
      panel_inner_view.y += top_panel_length;
      panel_inner_view.rows -= top_panel_length;
    } else {
      top_panel->SetHidden(true);
    }
  }

  if(bottom_panel) {
    auto bottom_panel_length = sides_[bottom_panel].length;
    if(panel_inner_view.rows >= bottom_panel_length && panel_inner_view.cols > 0) {
      auto bottom_panel_view = panel_inner_view;
      bottom_panel_view.rows = bottom_panel_length;
      bottom_panel_view.y += panel_inner_view.rows - bottom_panel_length;
      bottom_panel->SetView(bottom_panel_view);
      bottom_panel->SetHidden(false);
      panel_inner_view.rows -= bottom_panel_length;
    } else {
      bottom_panel->SetHidden(true);
    }
  }

  if(left_panel) {
    auto left_panel_length = sides_[left_panel].length;
    if(panel_inner_view.cols >= left_panel_length && panel_inner_view.rows > 0) {
      auto left_panel_view = panel_inner_view;
      left_panel_view.cols = left_panel_length;
      left_panel->SetView(left_panel_view);
      left_panel->SetHidden(false);
      panel_inner_view.x += left_panel_length;
      panel_inner_view.cols -= left_panel_length;
    } else {
      left_panel->SetHidden(true);
    }
  }

  if(right_panel) {
    auto right_panel_length = sides_[right_panel].length;
    if(panel_inner_view.cols >= right_panel_length && panel_inner_view.rows > 0) {
      auto right_panel_view = panel_inner_view;
      right_panel_view.cols = right_panel_length;
      right_panel_view.x += panel_inner_view.cols - right_panel_length;
      right_panel->SetView(right_panel_view);
      right_panel->SetHidden(false);
      panel_inner_view.cols -= right_panel_length;
    } else {
      right_panel->SetHidden(true);
    }
  }

  if(center_panel) {
    if(panel_inner_view.rows > 0 && panel_inner_view.cols > 0) {
      center_panel->SetView(panel_inner_view);
      center_panel->SetHidden(false);
    } else {
      center_panel->SetHidden(true);
    }
  }
}

} // namespace npp