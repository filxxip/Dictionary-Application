#include "double_index_box.h"
#include "../data/config_file.h"

#include <QObject>
#include <QStyle>

namespace {
constexpr char EDIT_IMAGE[] = "images/editv2.png";
}

DoubleIndexBox::DoubleIndexBox(QWidget *widget_, Word &word_,
                               const QString &index,
                               Word::Language base_language,
                               Word::Language translated_language)
    : IndexBox(widget_, word_, index, base_language),
      to_word_entry(widget_, EntryLine::Status::NORMAL),
      edit_button(widget, EDIT_IMAGE, Displays::DisplayStyle::SCALED_WIDTH,
                  30) {
  set_entry_basic_options(&to_word_entry, translated_language);
  addWidget(&edit_button);
  edit_button.setObjectName("bluecolor");
  QObject::connect(&edit_button, &QPushButton::clicked, this,
                   &DoubleIndexBox::edit_method);
}

void DoubleIndexBox::edit_method() {
  set_edit_style(&to_word_entry);
  set_edit_style(&from_word_entry);
}

void DoubleIndexBox::set_edit_style(EntryLine *entryline) {
  set_status(Status::EDIT);
  entryline->setObjectName("entryline");
  entryline->style()->polish(entryline);
}
