#include <ncursespp/layout.h>
#include <ncursespp/common.h>

namespace npp {

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
  auto panel_view = panel->View();
  uint64_t count_tiles = children.size();

  // Compute total children tiles weight
  float total_weight = 0.0f;
  for(auto i=0; i < count_tiles; i++) {
    total_weight += PanelWeight(children[i]);
  }

  // Update view for each child
  int offset = 0;
  for(auto i=0; i < count_tiles; i++) {
    float normalized_weight = PanelWeight(children[i]) / total_weight;
    View tile_view = panel_view;
    if(orientation_ == Horizontal) {
      tile_view.cols *= normalized_weight;
      tile_view.x = offset;
      offset += tile_view.cols;
    } else if(orientation_ == Vertical) {
      tile_view.rows *= normalized_weight;
      tile_view.y = offset;
      offset += tile_view.rows;
    } else {
      NPP_FATAL("unknown orientation");
    }
    children[i]->SetView(tile_view);
  }
}

} // namespace npp