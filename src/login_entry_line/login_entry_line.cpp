#include "login_entry_line.h"
#include "../data/config_file.h"
#include "../regex_check/regex_check.h"

#include <QObject>

LoginLineEntry::LoginLineEntry(QWidget *widget_) : EntryLine(widget_) {
  setPlaceholderText(Placeholders::LOGIN_PLACEHOLDER);
}

EntryLine::Status LoginLineEntry::get_status() const {
  return EntryLine::Status::NORMAL;
}
