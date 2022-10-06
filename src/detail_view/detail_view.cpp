#include "detail_view.h"
#include "../data/config_file.h"

#include <QObject>
#include <QPainter>

namespace {
constexpr char EXIT_BUTTON[] = "images/edit2.png";
constexpr char TITLE_IMAGE[] = "images/dict.png";
constexpr char TITLE_DICTIONARY_LABEL_TEXT[] = "Dictionary title: ";
constexpr int BASIC_TEXT_MARGIN = 30;
constexpr int BASIC_TITLE_LABEL_HEIGHT = 120;
constexpr QMargins BASIC_HBOX_MARGIN = {10, 0, 10, 50};
} // namespace

DetailView::DetailView(Word &word_, Dictionary *dictionary_,
                       Word::Language base_language_)
    : QObject(), dictionary(dictionary_),
      exit_button(&main_widget, EXIT_BUTTON,
                  Displays::DisplayStyle::SCALED_WIDTH,
                  WidgetData::EXIT_HEIGHT),
      dictionary_title(&main_widget, dictionary->get_name()),
      title_label(&main_widget, TITLE_IMAGE,
                  Displays::DisplayStyle::CHANGED_WIDTH,
                  BASIC_TITLE_LABEL_HEIGHT),
      edit_panel(&main_widget, word_), word(word_),
      base_language(base_language_) {
  exit_button.set_position(WidgetData::EXIT_POSITION_X,
                           WidgetData::EXIT_POSITION_Y);
  QObject::connect(&exit_button, &QPushButton::clicked, this,
                   [this]() { emit close_window_signal(&main_widget); });
  main_layout.addWidget(&title_label);
  create_dictionary_title();
  main_widget.setLayout(&main_layout);
  main_layout.setContentsMargins(WidgetData::MAIN_LAYOUT_MARGINS);
  for (int i = 0; i <= static_cast<int>(Word::Language::GERMAN); i++) {
    auto item = std::make_unique<DetailViewOneLanguageLayout>(
        &main_widget, word, static_cast<Word::Language>(i), dictionary);
    QObject::connect(
        item.get(), &DetailViewOneLanguageLayout::update_rest_dictionaries,
        this, [this](auto dict) { emit update_rest_dicts_signal(dict); });
    main_layout.addLayout(item.get());
    language_detail_panels.push_back(std::move(item));
  }

  QObject::connect(
      &edit_panel, &ConfigDetailViewPanel::delete_word_signal, this,
      [this](auto &word) { emit delete_window_signal(word, dictionary); });
  main_layout.addLayout(&edit_panel);
}

Word &DetailView::get_word() { return word; }

QWidget *DetailView::get_widget() { return &main_widget; }

void DetailView::update() {
  update_title();
  for (auto &language : language_detail_panels) {
    language->update_content();
  }
}

void DetailView::create_dictionary_title() {

  auto hbox = new QHBoxLayout;
  hbox->setContentsMargins(BASIC_HBOX_MARGIN);

  auto text = TITLE_DICTIONARY_LABEL_TEXT;
  auto name_label = new TextLabel(&main_widget, text);

  name_label->set_adjusted_width(BASIC_TEXT_MARGIN);
  name_label->setFixedHeight(WidgetData::ELEMENT_DETAIL_HEIGHT);

  hbox->addWidget(name_label);
  hbox->addWidget(&dictionary_title);

  dictionary_title.setFixedHeight(WidgetData::ELEMENT_DETAIL_HEIGHT);

  main_layout.addLayout(hbox);
}

Dictionary *DetailView::get_dictionary() const { return dictionary; }

QString DetailView::get_tab_title() const {
  return word.get_translation(base_language) + " - detail";
}

void DetailView::update_title() {
  auto title = dictionary->get_name();
  dictionary_title.setText(title);
}
