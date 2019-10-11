#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <map>
#include <ncursespp/view.h>
#include <ncursespp/panel.h>
#include <ncursespp/border.h>

namespace npp {

template<class T>
struct Direction {
  T top;
  T left;
  T bottom;
  T right;
};

enum Orientation {
  Vertical,
  Horizontal
};

class Layout {
protected:
  Direction<int> margin_;
  Direction<int> padding_;
  Direction<npp::Border> border_;
public:
  void SetBorder(Direction<Border> border) { border_ = border; }
  void SetMargin(Direction<int> margin) { margin_ = margin; }
  void SetPadding(Direction<int> padding) { padding_ = padding; }
  Direction<int> Margin() const { return margin_; }
  Direction<int> Padding() const { return padding_; }
  Direction<npp::Border> Border() const { return border_; }
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