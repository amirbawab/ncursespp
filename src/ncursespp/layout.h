#ifndef NPP_LAYOUT_H_
#define NPP_LAYOUT_H_

#include <ncursespp/view.h>

namespace npp {

struct Direction {
  int top;
  int left;
  int bottom;
  int right;
};

class Layout {
private:
  View view_; // TODO (amir) might not use
  Direction margin_;
  Direction padding_;
public:
  virtual void Fit() = 0;
};
}

#endif