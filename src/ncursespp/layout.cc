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

void TileLayout::SetWeight(std::string panel_id, float weight) {
  weights_[panel_id] = weight;
}

float TileLayout::PanelWeight(npp::Panel* panel) {
  std::string panel_id = panel->Id();
  if(weights_.find(panel_id) != weights_.end()) {
    return weights_[panel_id];
  }
  // Default weight value
  return 1.0f;
}

void TileLayout::Fit(Panel* panel) {
  auto children = panel->Children();
  uint64_t count_tiles = children.size();

  // Compute total children tiles weight
  auto panel_inner_view = panel->Layout()->PaddingView(panel);
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

} // namespace npp