#include "index_box.h"

IndexBox::IndexBox(QWidget *widget_, Word &word_, const QString &index,
                   Word::Language l1)
    : QHBoxLayout(), widget(widget_), word(word_), index_label(widget, index),
      from_word_entry(widget, EntryLine::Status::NORMAL) {
  addWidget(&index_label);
  set_entry_basic_options(&from_word_entry, l1);
  setSpacing(30);
  index_label.setFixedSize(30, 30);
}

void IndexBox::set_status(Status status) {
  switch (status) {
  case IndexBox::Status::EDIT: {
    from_word_entry.setReadOnly(false);
    break;
  }
  case IndexBox::Status::READ_ONLY: {
    from_word_entry.setReadOnly(true);
    break;
  }
  }
}

void IndexBox::set_entry_basic_options(EntryLine *entry,
                                       Word::Language language) {
  entry->setFixedHeight(30);
  set_status(Status::READ_ONLY);
  entry->setObjectName("entrytitle");
  auto content = word.get_translation(language);
  entry->setText(content);
  addWidget(entry);
}
