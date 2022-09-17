#include "text_label.h"
#include "../data/config_file.h"

TextLabel::TextLabel(QWidget *widget_, const QString &text_) : QLabel(widget_) {
  setText(text_);
  setObjectName("textlabel");
  set_font_size(WidgetData::DEFAULT_FONT_SIZE);
  setAlignment(Qt::AlignCenter);
}

void TextLabel::set_font_size(int size) {
  auto font_family = font().family();
  auto new_font = QFont(font_family, size);
  setFont(new_font);
}
void TextLabel::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}
