#include "add_new_word.h"

#include <QStringLiteral>

namespace {
auto text = QStringLiteral("images/%1");
} // namespace

AddNewWord::AddNewWord(Word::Language main_language_, Dictionary &dictionary)
    : QObject(), dict(dictionary),
      title_image(&main_window, text.arg("dict.png"),
                  Displays::DisplayStyle::CHANGED_WIDTH,
                  WidgetData::WORDLIST_VIEW_IMG_HEIGHT),
      confirm_button(&main_window, text.arg("confirm3.png")),
      cancel_button(&main_window, text.arg("cancel3.png")),
      clear_button(&main_window, text.arg("trashall.png")),
      main_language(main_language_) {
  main_layout.addWidget(&title_image);
  create_entryboxes();
  create_config_panel_layout();

  main_layout.setContentsMargins(WidgetData::WORDLIST_VIEW_IMG_MARGINS);
  main_window.setLayout(&main_layout);
}

QWidget *AddNewWord::get_widget() { return &main_window; }

Dictionary &AddNewWord::get_dictionary() { return dict; }

void AddNewWord::create_config_panel_layout() {
  auto hboxlayout = new QHBoxLayout();
  main_layout.addLayout(hboxlayout);
  hboxlayout->addWidget(&confirm_button);
  hboxlayout->addWidget(&cancel_button);
  hboxlayout->addWidget(&clear_button);
  QObject::connect(&confirm_button, &QPushButton::clicked, this,
                   &AddNewWord::add_new_word);
  QObject::connect(&clear_button, &QPushButton::clicked, this,
                   &AddNewWord::clear);
  QObject::connect(&cancel_button, &QPushButton::clicked, this,
                   [this]() { emit exit_signal(&main_window); });
}

void AddNewWord::create_single_entrybox(int height, Word::Language language) {
  auto box = std::make_unique<LabelEntryBox>(
      &main_window, Word::Language_names.at(language), "type translation",
      EntryLine::Status::NORMAL);
  box->set_label_width(150);
  auto lay = box->create_layout(height);

  language_panels.insert({language, std::move(box)});
  main_layout.addLayout(lay);
}

void AddNewWord::create_entryboxes() {
  if (main_language != Word::Language::UNDEFINED) {
    create_single_entrybox(50, main_language);
    language_panels.at(main_language)
        ->change_entry_line_object_name("entryline_important");
  }
  for (auto &[language, name] : Word::Language_names) {
    if (language != Word::Language::UNDEFINED && language != main_language) {
      create_single_entrybox(40, language);
    }
  }
}

std::map<Word::Language, QString> AddNewWord::get_defined_translations() const {
  std::map<Word::Language, QString> mapa;
  for (auto &[language, name] : Word::Language_names) {
    if (language != Word::Language::UNDEFINED) {
      auto translation = language_panels.at(language)->get_text();
      qDebug() << translation;
      mapa.insert({language, translation});
    }
  }
  return mapa;
}

void AddNewWord::add_new_word() {
  if (main_language != Word::Language::UNDEFINED) {
    auto entryline = language_panels.at(main_language)->get_entryline();
    if (entryline->isEmpty()) {
      change_color({entryline}, "red", 500);
      return;
    }
  }
  qDebug("aaa");
  Word word(get_defined_translations());
  qDebug() << dict.get_number_of_words();
  dict.add_word(word);
  qDebug() << dict.get_number_of_words();
  emit add_new_word_signal(dict);
  //  emit exit_signal(&main_window);
}

void AddNewWord::clear() {
  for (auto &[language, entrybox] : language_panels) {
    entrybox->get_entryline()->clear();
  }
}
