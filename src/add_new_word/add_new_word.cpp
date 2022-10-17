#include "add_new_word.h"
#include "../custom_message_box/custom_message_box.h"

#include <QStringLiteral>

namespace {
auto text = QStringLiteral("images/%1");

constexpr char EMPTY_MAIN_LANGUAGE_TITLE[] = "INCORRECT DATA";

constexpr char EMPTY_MAIN_LANGUAGE_TEXT[] =
    "Creating empty main language is banned, pass something to it!";

constexpr char CORRECT_DATA_TITLE[] = "CORRECT DATA";

const QString CORRECT_DATA_TEXT = QStringLiteral(
    "Are you sure to create '%1' in %2 language new word with given "
    "translations?");

const QString WORD_CONTAIN_OTHER_WORD_TEXT = QStringLiteral(
    "Are you sure to create '%1' in %2 language new word with given "
    "translations? Other word is part of this word and will be removed!");

const QString OTHER_WORD_CONTAIN_WORD_TEXT = QStringLiteral(
    "Are you sure to create '%1' in %2 language new word with given "
    "translations? Content of this word will be added to other word");
} // namespace

const Word::Language AddNewWord::MAIN_BASE_LANGUAGE = Word::Language::ENGLISH;

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
      mapa.insert({language, translation});
    }
  }
  return mapa;
}
void AddNewWord::adding_undefined_main_language(
    Word::Language information_language) {
  auto text = language_panels.at(information_language)->get_entryline()->text();
  auto content = text.isEmpty() ? "undefined" : text;
  auto language_name = Word::Language_names.at(information_language);
  Word word(get_defined_translations());

  CustomMessageBox *msg =
      nullptr; // jesli chodzi o te operatory new to sa one tutaj mam nadzieje
               // chwilowo, po prostu jest to poki co jedyna dzialajaca opcja
               // ktora odkrylem, problem jest w tym, ze w trakcie emitacji
               // sygnalu usuwany jest obiekt tej klasy i powoduje to tak jakby
               // podwojna probe usuniecia tych messageboxow podwuje, gdy
               // korzystam z new no to to usuniecie nie nastepuje ani razu,
               // wiec wiem, ze musi to koniecznie byc skorygowane
  if (dict.any_word_contain(word)) {
    msg = new CustomMessageBox(
        &main_window, CORRECT_DATA_TITLE,
        OTHER_WORD_CONTAIN_WORD_TEXT.arg(content, language_name));
  } else if (dict.contain_any_word(word)) {
    msg = new CustomMessageBox(
        &main_window, CORRECT_DATA_TITLE,
        WORD_CONTAIN_OTHER_WORD_TEXT.arg(content, language_name));
  }
  if (!msg) {
    msg = new CustomMessageBox(&main_window, CORRECT_DATA_TITLE,
                               CORRECT_DATA_TEXT.arg(content, language_name));
  }
  if (msg->run(CustomMessageBox::Type::No, {CustomMessageBox::Type::Yes}) ==
      CustomMessageBox::Type::Yes) {
    delete msg;
    dict.add_word(word);
    emit add_new_word_signal(dict);
  }
}

void AddNewWord::adding_defined_main_language() {
  auto entryline = language_panels.at(main_language)->get_entryline();
  if (entryline->isEmpty()) {
    change_color({entryline}, "red", 500);
    auto *msg = new CustomMessageBox(&main_window, EMPTY_MAIN_LANGUAGE_TITLE,
                                     EMPTY_MAIN_LANGUAGE_TEXT);
    msg->run(CustomMessageBox::Type::Ok);
  } else {
    adding_undefined_main_language(main_language);
  }
}

void AddNewWord::add_new_word() {
  main_language == Word::Language::UNDEFINED
      ? adding_undefined_main_language(Word::Language::ENGLISH)
      : adding_defined_main_language();
}

void AddNewWord::clear() {
  for (auto &[language, entrybox] : language_panels) {
    entrybox->get_entryline()->clear();
  }
}
