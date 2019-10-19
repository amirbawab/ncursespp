#ifndef NPP_FIXED_LAYOUT_H_
#define NPP_FIXED_LAYOUT_H_

#include <ncursespp/layout/layout.h>

namespace npp {

class FixedLayout : public Layout {
private:
  std::map<Panel*, npp::View> fixed_panels_;
  npp::View PanelFixedView(Panel* panel);
public:
  void SetFixedView(Panel* panel, npp::View view);
  void Fit(Panel* panel) override;
};

} // namespace npp

#endif
