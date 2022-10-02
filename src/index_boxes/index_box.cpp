#include "index_box.h"

IndexBox::IndexBox(QWidget *widget_, Word &word_, const QString &index,
                   Word::Language l1)
    : QHBoxLayout(), widget(widget_), word(word_),
      widget_index_entry_layout(std::make_unique<QWidget>()),
      index_entry_layout(std::make_unique<QHBoxLayout>()),
      index_label(widget, index),
      from_word_entry(widget, EntryLine::Status::NORMAL), base_language(l1) {
  index_label.setFixedWidth(50);
  index_entry_layout->addWidget(&index_label);
  set_entry_basic_options(&from_word_entry, l1);
  widget_index_entry_layout->setLayout(index_entry_layout.get());
  addWidget(widget_index_entry_layout.get());

  widget_index_entry_layout->setObjectName("bluecolor");
  widget_index_entry_layout->setFixedWidth(400);
  widget_index_entry_layout->setFixedHeight(30);

  index_entry_layout->setContentsMargins(0, 0, 0, 0);
}

void IndexBox::set_entry_basic_options(EntryLine *entry,
                                       Word::Language language) {
  entry->setObjectName("entrytitle");
  auto content = word.get_translation(language);
  entry->setText(content);
  index_entry_layout->addWidget(entry);
  entry->setFixedHeight(30);
}
