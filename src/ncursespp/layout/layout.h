#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <map>
#include <ncursespp/view.h>
#include <ncursespp/panel/panel.h>
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

} // namespace npp

#endif