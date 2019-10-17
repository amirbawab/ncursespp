#ifndef NPP_BORDER_H_
#define BPP_BORDER_H_

namespace npp {

// (name, horizontal_side, vertical_side, top_left, top_right, bottom_left, bottom_right)
#define BORDER_STYLE_LIST(V)  \
  V(SolidThin, U"\u2500", U"\u2502", U"\u250c", U"\u2510", U"\u2514", U"\u2518")

#define BORDER_STYLE_ENUM(name, hside, vside, tl, tr, bl, br) \
  name,

enum BorderStyle {
  None,
  BORDER_STYLE_LIST(BORDER_STYLE_ENUM)
};

#undef BORDER_STYLE_ENUM

struct Border {
  BorderStyle style = BorderStyle::None;
  bool None() const { return style == BorderStyle::None; }
};

} // namespace npp

#endif