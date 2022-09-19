#include "entry_line.h"
#include "../data/config_file.h"

EntryLine::EntryLine(QWidget *widget_, Status entry_type) : QLineEdit(widget_) {
  set_text_status(entry_type);
  setObjectName("entryline");
  setTextMargins(WidgetData::DEFAULT_TEXT_MARGINS);
}

void EntryLine::append_text(const QString &append_text) {
  setText(text() + append_text);
}

void EntryLine::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}

EntryLine::Status EntryLine::get_status() const { return status; }

void EntryLine::set_text_status(EntryLine::Status new_status) {

  status = new_status;
  switch (new_status) {
  case EntryLine::Status::NORMAL: {
    setEchoMode(EchoMode::Normal);
    break;
  }
  case EntryLine::Status::PASSWORD: {
    setEchoMode(EchoMode::Password);
    break;
  }
  }
}
