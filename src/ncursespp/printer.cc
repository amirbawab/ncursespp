#include <ncursespp/printer.h>
#include <ncursespp/window.h>
#include <ncursespp/common.h>
#include <algorithm>

namespace npp {

void ScreenPrinter::NC_AddStr(npp::Point point, std::string text) const {
  mvwaddstr(window_->CursesWindow(), point.y, point.x, text.c_str());
}

void ScreenPrinter::NC_AddCh(npp::Point point, const chtype c) const {
  mvwaddch(window_->CursesWindow(), point.y, point.x, c);
}

void BufferPrinter::NC_AddStr(npp::Point point, std::string text) const {
  auto window_view = window_->View();
  Point relative_point = {point.x - window_view.x, point.y - window_view.y};
  DCHECK_GE(relative_point.x, 0);
  DCHECK_GE(relative_point.y, 0);
  std::vector<char>& row = window_->RowAt(relative_point.y);
  auto string_begin = row.begin() + relative_point.x;
  std::copy(text.begin(), text.end(), string_begin);
}

void BufferPrinter::NC_AddCh(npp::Point point, unsigned int c) const {
  window_->CharAt(point) = static_cast<char>(c);
}

void Printer::DrawTextBuffer(npp::TextBuffer* text_buffer, npp::View view, npp::TextPrinterOptions options) const {
  int x_begin = view.x;
  int y_begin = view.y;
  int y_end = y_begin + view.rows;
  Point text_point = {x_begin, y_begin};
  const auto &text_vector = text_buffer->Value();
  auto lines_count = text_vector.size();
  for(auto i=0; i < lines_count && text_point.y < y_end; i++) {
    auto &line_vector = text_vector[i];
    auto line_length = line_vector.size();
    size_t text_index = 0;
    do {
      size_t end_line = std::min(text_index + view.cols, line_length);
      NC_AddStr(text_point, std::string(line_vector.begin() + text_index, line_vector.begin() + end_line));
      text_index = end_line;
      text_point.y++;
    } while (options.wrap && text_index < line_length);
  }
}

void Printer::DrawEmptyView(npp::View view) const {
  int x_begin = view.x;
  int x_end = x_begin + view.cols;
  int y_begin = view.y;
  int y_end = y_begin + view.rows;

  for(int y = y_begin; y < y_end; y++) {
    for(int x = x_begin; x < x_end; x++) {
      NC_AddCh({x, y}, ' ');
    }
  }
}

#define BORDER_STYLE_VERTICAL_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    for(int y = y_begin; y < y_end; y++) { \
      NC_AddStr({point.x, y}, vside); \
    } \
    break;

void Printer::DrawVLine(npp::Point point, int length, BorderStyle style) const {
  int y_begin = point.y;
  int y_end = y_begin + length;
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_VERTICAL_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_VERTICAL_DRAW

// TODO Check for overflow DCHECK_LT(x_begin, x_end)

#define BORDER_STYLE_HORIZONTAL_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    for(int x = x_begin; x < x_end; x++) { \
      NC_AddStr({x, point.y}, hside); \
    } \
    break;

void Printer::DrawHLine(npp::Point point, int length, npp::BorderStyle style) const {
  int x_begin = point.x;
  int x_end = x_begin + length;
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_HORIZONTAL_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_HORIZONTAL_DRAW

#define BORDER_STYLE_TL_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    NC_AddStr({point.x, point.y}, tl); \
    break;

void Printer::DrawTLCorner(npp::Point point, npp::BorderStyle style) const {
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_TL_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_TL_DRAW

#define BORDER_STYLE_TR_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    NC_AddStr({point.x, point.y}, tr); \
    break;

void Printer::DrawTRCorner(npp::Point point, npp::BorderStyle style) const {
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_TR_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_TR_DRAW

#define BORDER_STYLE_BL_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    NC_AddStr({point.x, point.y}, bl); \
    break;

void Printer::DrawBLCorner(npp::Point point, npp::BorderStyle style) const {
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_BL_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_BL_DRAW

#define BORDER_STYLE_BR_DRAW(name, hside, vside, tl, tr, bl, br) \
  case name: \
    NC_AddStr({point.x, point.y}, br); \
    break;

void Printer::DrawBRCorner(npp::Point point, npp::BorderStyle style) const {
  switch (style) {
    BORDER_STYLE_LIST(BORDER_STYLE_BR_DRAW)
    default:
      DCHECK_EQ(style, BorderStyle::None);
  }
}

#undef BORDER_STYLE_BR_DRAW

void Printer::DrawBorder(npp::Borders borders, npp::View view) const {
  int x_begin = view.x;
  int x_last = x_begin + view.cols-1;
  int y_begin = view.y;
  int y_last = y_begin + view.rows-1;

  // TODO (amir) by default borders are thin,
  // should probably be configurable or automatically adapt
  // Draw top corners
  if(!borders.top.None()) {
    if(!borders.left.None()) {
      DrawTLCorner({x_begin, y_begin});
    }
    if(!borders.right.None()) {
      DrawTRCorner({x_last, y_begin});
    }
  }

  // Draw bottom corners
  if(!borders.bottom.None()) {
    if(!borders.left.None()) {
      DrawBLCorner({x_begin, y_last});
    }
    if(!borders.right.None()) {
      DrawBRCorner({x_last, y_last});
    }
  }

  DrawVLine({x_begin, y_begin+1}, y_last - y_begin - 1, borders.left.style); // left
  DrawVLine({x_last, y_begin+1}, y_last - y_begin - 1, borders.left.style); // right
  DrawHLine({x_begin+1, y_begin}, x_last - x_begin - 1, borders.left.style); // top
  DrawHLine({x_begin+1, y_last}, x_last - x_begin - 1, borders.left.style); // bottom
}

void Printer::DrawString(npp::Point point, std::string text) const {
  NC_AddStr(point, std::move(text));
}

} // namespace npp