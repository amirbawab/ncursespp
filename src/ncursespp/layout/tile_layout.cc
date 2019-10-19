#include <ncursespp/layout/tile_layout.h>
#include <ncursespp/common.h>

namespace npp {

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

} // namespace npp