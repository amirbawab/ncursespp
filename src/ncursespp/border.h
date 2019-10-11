#ifndef NPP_BORDER_H_
#define BPP_BORDER_H_

namespace npp {

// (name, vertical_side, horizontal_side, top_left, top_right, bottom_left, bottom_right)
#define BORDER_STYLE_LIST(V)  \
  V(SolidThin, 2500, 2502, 250c, 2510, 2514, 2518)

#define BORDER_STYLE_ENUM(name, vside, hside, tl, tr, bl, br) \
  name,

enum BorderStyle {
  None,
  BORDER_STYLE_LIST(BORDER_STYLE_ENUM)
};

#undef BORDER_STYLE_ENUM

struct Border {
  BorderStyle style = None;
};

} // namespace npp

#endif