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

typedef Direction<int> Margins;
typedef Direction<int> Paddings;
typedef Direction<npp::Border> Borders;

enum Orientation {
  Vertical,
  Horizontal
};

class Layout {
protected:
  Margins margin_;
  Paddings padding_;
  Borders border_;
public:
  explicit Layout();
  void SetBorder(Borders border) { border_ = border; }
  void SetMargin(Margins margin) { margin_ = margin; }
  void SetPadding(Paddings padding) { padding_ = padding; }
  Margins Margin() const { return margin_; }
  Paddings Padding() const { return padding_; }
  Borders Border() const { return border_; }
  npp::View MarginView(Panel* panel) const;
  npp::View BorderView(Panel* panel) const;
  npp::View PaddingView(Panel* panel) const;
  virtual void Fit(Panel* panel) = 0;
};

class TileLayout : public Layout {
private:
  Orientation orientation_ = Horizontal;
  std::map<std::string, float> weights_;
  float PanelWeight(Panel* panel);
public:
  void SetWeight(std::string panel_id, float weight);
  void SetOrientation(Orientation orientation) { orientation_ = orientation; }
  void Fit(Panel* panel) override;
};

} // namespace npp

#endif