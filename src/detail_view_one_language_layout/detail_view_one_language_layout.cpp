#include "detail_view_one_language_layout.h"
#include "../data/config_file.h"

#include <QStringLiteral>
#include <QStyle>

namespace {
constexpr char DELETE_BUTTON[] = "images/deletev2.png";
constexpr char BASE_UNDEFINED_TEXT[] = "<-translation undefined->";
} // namespace

DetailViewOneLanguageLayout::DetailViewOneLanguageLayout(
    QWidget *widget_, Word &word_, Word::Language language_, Dictionary &dict)
    : QHBoxLayout(), widget(widget_), word(word_), language(language_),
      translation_entry(widget), date_entry(widget),
      language_label(widget, Word::Language_names.at(language)),
      delete_button(widget, DELETE_BUTTON, Displays::DisplayStyle::SCALED_WIDTH,
                    WidgetData::ELEMENT_DETAIL_HEIGHT),
      dictionary(dict) {
  language_label.setFixedWidth(100);
  date_entry.setAlignment(Qt::AlignCenter);
  translation_entry.setAlignment(Qt::AlignCenter);
  addWidget(&language_label);
  addWidget(&translation_entry);
  addWidget(&date_entry);
  addWidget(&delete_button);
  set_entries_read_only(true);
  update_content();
  set_height(WidgetData::ELEMENT_DETAIL_HEIGHT);
  QObject::connect(&delete_button, &QPushButton::clicked, this,
                   &DetailViewOneLanguageLayout::delete_translation);
}

void DetailViewOneLanguageLayout::set_entries_read_only(bool status) {
  translation_entry.setReadOnly(status);
  if (!status && translation_entry.text() == BASE_UNDEFINED_TEXT) {
    translation_entry.setText("");
  }
  set_entries_new_object_names(status ? "entrytitle" : "entryline");
}

void DetailViewOneLanguageLayout::set_entries_new_object_names(
    const QString &new_object_name) {
  translation_entry.set_object_name_stylesheet(new_object_name);
  date_entry.set_object_name_stylesheet(new_object_name);
}

void DetailViewOneLanguageLayout::set_height(int height) {
  language_label.setFixedHeight(height);
  date_entry.setFixedHeight(height);
  translation_entry.setFixedHeight(height);
}

void DetailViewOneLanguageLayout::update_content() {
  auto translation = word.get_translation(language);
  if (word.is_defined(language)) {
    translation_entry.setText(translation);
  } else {
    translation_entry.setText(
        translation_entry.isReadOnly() ? BASE_UNDEFINED_TEXT : "");
  }

  auto translation_date = word.get_date(language);
  date_entry.setText(translation_date.to_string());
}

void DetailViewOneLanguageLayout::delete_translation() {
  if (!word.is_defined(language)) {
    auto text = QStringLiteral("Language is not defined for &1")
                    .arg(word.get_translation(language));
    return;
  }
  word.set_not_defined(language);
  update_content();
  emit update_rest_dictionaries(dictionary);
}

void DetailViewOneLanguageLayout::set_entry_content_to_word() {
  auto text = translation_entry.text();

  if (text != "" && text != BASE_UNDEFINED_TEXT) {
    if (text != word.get_translation(language)) {
      word.change_translation(language, text);
    }
  } else {
    if (word.is_defined(language)) {
      word.set_not_defined(language);
    }
  }

  //  text != "" && text != BASE_UNDEFINED_TEXT
  //      ? word.change_translation(language, text)
  //      : word.set_not_defined(language);
}

Dictionary &DetailViewOneLanguageLayout::get_dictionary() const {
  return dictionary;
}
