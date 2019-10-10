#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <map>
#include <ncursespp/view.h>
#include <ncursespp/panel.h>

namespace npp {

struct Direction {
  int top;
  int left;
  int bottom;
  int right;
};

enum Orientation {
  Vertical,
  Horizontal
};

class Layout {
protected:
  Direction margin_;
  Direction padding_;
public:
  virtual void Fit(Panel* panel) = 0;
};

class TileLayout : public Layout {
private:
  Orientation orientation_ = Vertical;
  std::map<std::string, float> weights_;
  float PanelWeight(Panel* panel);
public:
  void SetWeight(std::string panel_id, float weight);
  void SetOrientation(Orientation orientation) { orientation_ = orientation; }
  void Fit(Panel* panel) override;
};

} // namespace npp

#endif