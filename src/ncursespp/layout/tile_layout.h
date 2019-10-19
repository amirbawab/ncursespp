#ifndef NPP_TILE_LAYOUT_H_
#define NPP_TILE_LAYOUT_H_

#include <ncursespp/layout/layout.h>
#include <ncursespp/common.h>

namespace npp {

class TileLayout : public Layout {
private:
  Orientation orientation_ = Horizontal;
  std::map<Panel*, float> weights_;
  float PanelWeight(Panel* panel);
public:
  void SetWeight(Panel* panel, float weight);
  void SetOrientation(Orientation orientation) { orientation_ = orientation; }
  void Fit(Panel* panel) override;
};

} // namespace nnp

#endif
