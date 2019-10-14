#include <ncursespp/layout.h>
#include <ncursespp/common.h>

namespace npp {

Layout::Layout() {
  SetMargin({0, 0, 0, 0});
  SetPadding({0, 0, 0, 0});
}

npp::View Layout::MarginView(Panel* panel) const {
  auto view = panel->View();
  view.x += margin_.left;
  view.y += margin_.top;
  view.cols -= margin_.left + margin_.right;
  view.rows -= margin_.top + margin_.bottom;
  return view;
}

npp::View Layout::BorderView(npp::Panel *panel) const {
  auto view = MarginView(panel);
  int top = border_.top.None() ? 0 : 1;;
  int left = border_.left.None() ? 0 : 1;;
  int bottom = border_.bottom.None() ? 0 : 1;;
  int right = border_.right.None() ? 0 : 1;;
  view.x += left;
  view.y += top;
  view.cols -= left + right;
  view.rows -= top + bottom;
  return view;
}

npp::View Layout::PaddingView(npp::Panel *panel) const {
  auto view = BorderView(panel);
  view.x += padding_.left;
  view.y += padding_.top;
  view.cols -= padding_.right;
  view.rows -= padding_.bottom;
  return view;
}

void TileLayout::SetWeight(Panel* panel, float weight) {
  weights_[panel] = weight;
}

float TileLayout::PanelWeight(npp::Panel* panel) {
  if(weights_.find(panel) != weights_.end()) {
    return weights_[panel];
  }
  // Default weight value
  return 1.0f;
}

void TileLayout::Fit(Panel* panel) {
  auto children = panel->Children();
  uint64_t count_tiles = children.size();

  // Compute total children tiles weight
  auto panel_inner_view = panel->InnerView();
  float total_weight = 0.0f;
  for(auto i=0; i < count_tiles; i++) {
    total_weight += PanelWeight(children[i]);
  }

  // Update view for each child
  int offset = 0;
  for(auto i=0; i < count_tiles; i++) {
    float normalized_weight = PanelWeight(children[i]) / total_weight;
    View tile_view = panel_inner_view;
    if(orientation_ == Horizontal) {
      tile_view.cols *= normalized_weight;
      tile_view.x += offset;
      offset += tile_view.cols;
    } else if(orientation_ == Vertical) {
      tile_view.rows *= normalized_weight;
      tile_view.y += offset;
      offset += tile_view.rows;
    } else {
      NPP_FATAL("unknown orientation");
    }
    children[i]->SetView(tile_view);
  }
}

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
    }
  }

  // Fit side panels. Order is important!
  auto panel_inner_view = panel->InnerView();
  View hidden_view = View();
  if(top_panel) {
    auto top_panel_length = sides_[top_panel].length;
    if(panel_inner_view.rows >= top_panel_length && panel_inner_view.cols > 0) {
      auto top_panel_view = panel_inner_view;
      top_panel_view.rows = top_panel_length;
      top_panel->SetView(top_panel_view);
      panel_inner_view.y += top_panel_length;
      panel_inner_view.rows -= top_panel_length;
    } else {
      top_panel->SetView(hidden_view);
    }
  }

  if(bottom_panel) {
    auto bottom_panel_length = sides_[bottom_panel].length;
    if(panel_inner_view.rows >= bottom_panel_length && panel_inner_view.cols > 0) {
      auto bottom_panel_view = panel_inner_view;
      bottom_panel_view.rows = bottom_panel_length;
      bottom_panel_view.y += panel_inner_view.rows - bottom_panel_length;
      bottom_panel->SetView(bottom_panel_view);
      panel_inner_view.rows -= bottom_panel_length;
    } else {
      bottom_panel->SetView(hidden_view);
    }
  }

  if(left_panel) {
    auto left_panel_length = sides_[left_panel].length;
    if(panel_inner_view.cols >= left_panel_length && panel_inner_view.rows > 0) {
      auto left_panel_view = panel_inner_view;
      left_panel_view.cols = left_panel_length;
      left_panel->SetView(left_panel_view);
      panel_inner_view.x += left_panel_length;
      panel_inner_view.cols -= left_panel_length;
    } else {
      left_panel->SetView(hidden_view);
    }
  }

  if(right_panel) {
    auto right_panel_length = sides_[right_panel].length;
    if(panel_inner_view.cols >= right_panel_length && panel_inner_view.rows > 0) {
      auto right_panel_view = panel_inner_view;
      right_panel_view.cols = right_panel_length;
      right_panel_view.x += panel_inner_view.cols - right_panel_length;
      right_panel->SetView(right_panel_view);
      panel_inner_view.cols -= right_panel_length;
    } else {
      right_panel->SetView(hidden_view);
    }
  }

  if(center_panel) {
    if(panel_inner_view.rows > 0 && panel_inner_view.cols > 0) {
      center_panel->SetView(panel_inner_view);
    } else {
      center_panel->SetView(hidden_view);
    }
  }
}

} // namespace npp