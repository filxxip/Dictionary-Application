#include "text_button.h"
#include "../data/config_file.h"

TextButton::TextButton(QWidget *widget_, const QString &text_)
    : QPushButton(widget_) {
  setText(text_);
  setObjectName("textbutton");
  set_font_size(WidgetData::DEFAULT_FONT_SIZE);
  setFixedWidth(WidgetData::DEFAULT_WIDTH);
}

void TextButton::set_font_size(int size) {
  setFont(QFont(font().family(), size));
}

void TextButton::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}
