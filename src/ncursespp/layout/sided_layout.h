#ifndef SIDED_LAYOUT_H_
#define SIDED_LAYOUT_H_

#include <ncursespp/layout/layout.h>

namespace npp {

struct SidePanel {
  enum Side : uint32_t {
    Top     = 1u << 0u,
    Left    = 1u << 1u,
    Bottom  = 1u << 2u,
    Right   = 1u << 3u,
    Hidden  = 1u << 4u,
    Center  = 1u << 5u,
  } side;
  int length;
  SidePanel(Side s, int l) : side(s), length(l) {}
  SidePanel() : SidePanel(Center, 0) {}
};

class SidedLayout : public Layout {
private:
  std::map<Panel*, SidePanel> sides_;
  SidePanel PanelSidePanel(Panel* panel, uint32_t *side_flags);
public:
  void SetSide(Panel* panel, SidePanel::Side side, int length);
  void Fit(Panel* panel) override;
};

} // namespace npp

#endif
