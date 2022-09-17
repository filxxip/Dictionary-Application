#include "entry_line.h"
#include "../data/config_file.h"

EntryLine::EntryLine(QWidget *widget_) : QLineEdit(widget_) {
  setObjectName("entryline");
  setTextMargins(WidgetData::DEFAULT_TEXT_MARGINS);
}

void EntryLine::append_text(const QString &append_text) {
  setText(text() + append_text);
}

void EntryLine::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}
