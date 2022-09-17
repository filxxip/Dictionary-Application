#include "password_entry_line.h"
#include "../data/config_file.h"

PasswordEntryLine::PasswordEntryLine(QWidget *widget_) : EntryLine(widget_) {
  set_text_status(Mode::Password);
  setPlaceholderText(Placeholders::PASSWORD_PLAHOLDER);
}

EntryLine::Status PasswordEntryLine::get_status() const {
  return EntryLine::Status::PASSWORD;
}

void PasswordEntryLine::set_text_status(Mode mode) { setEchoMode(mode); }
