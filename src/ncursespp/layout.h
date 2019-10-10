#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <vector>
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
  Panel* panel_;
  Direction margin_;
  Direction padding_;
public:
  virtual void Fit() = 0;
};

struct TileContainer {
  Panel* panel;
  float weight;
};

class TileLayout : public Layout {
private:
  Orientation orientation_ = Vertical;
  std::map<Panel*, TileContainer> containers_;
public:
  void Fit() override;
};

} // namespace npp

#endif