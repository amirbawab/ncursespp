#include <ncursespp/panel/input.h>
#include <ncursespp/window/window.h>

namespace npp {

void Input::PrintInner(npp::Window *window) {
  window->Printer()->DrawTextBuffer(&text_buffer_, InnerView());
}

} // namespace npp