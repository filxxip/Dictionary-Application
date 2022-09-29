#include "content_layout.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_message_box/custom_message_box.h"
#include "../data/config_file.h"
#include "../text_button/text_button.h"

#include <QObject>
#include <QStyle>

namespace {
constexpr char TRASH_IMAGE[] = "images/trash.png";
constexpr char EDIT_IMAGE[] = "images/edit.png";
constexpr char CONFIRM_IMAGE[] = "images/confirm.png";
constexpr char CANCEL_IMAGE[] = "images/cancel.png";

constexpr char INFORMATION_WARNING[] = "New title cannot be empty!";
constexpr char TITLE[] = "INCORRECT TITLE";

std::map<Word::Language, QString> source_languages = {
    {Word::Language::POLISH, "images/poland.jpg"},
    {Word::Language::GERMAN, "images/german.jpg"},
    {Word::Language::ENGLISH, "images/english.png"}};
} // namespace

void ContentLayout::create_base_entryline() {
  auto dict_name = dictionary->get_name();
  entry_title.setText(std::move(dict_name));
  layout->addWidget(&entry_title);
  entry_title.setReadOnly(true);
}

ContentLayout::ContentLayout(QWidget &widget_, Dictionary *dict)
    : CustomVBoxLayout(widget_),
      entry_title(&widget_, EntryLine::Status::NORMAL),
      trash_button(&widget, TRASH_IMAGE, Displays::DisplayStyle::SCALED_HEIGHT,
                   WidgetData::TRASH_EDIT_BUTTON),
      edit_button(&widget, EDIT_IMAGE, Displays::DisplayStyle::SCALED_HEIGHT,
                  WidgetData::TRASH_EDIT_BUTTON),
      confirm_button(&widget, CONFIRM_IMAGE,
                     Displays::DisplayStyle::SCALED_HEIGHT,
                     WidgetData::TRASH_EDIT_BUTTON),
      cancel_button(&widget, CANCEL_IMAGE,
                    Displays::DisplayStyle::SCALED_HEIGHT,
                    WidgetData::TRASH_EDIT_BUTTON),
      set_button(&widget, WidgetData::SET_BUTTON_TEXT), dictionary(dict) {
  create_layout();
  entry_configuration();
  confirm_button.setVisible(false);
  cancel_button.setVisible(false);
}

void ContentLayout::entry_configuration() {
  entry_title.setAlignment(Qt::AlignCenter);
  entry_title.setObjectName("entrytitle");
}

TextLabel *ContentLayout::create_base_label(const QString &text) {
  auto label = new TextLabel(&widget, text);
  label->setAlignment(Qt::AlignRight);
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  return label;
}

QHBoxLayout *ContentLayout::create_language_hbox(Word::Language language,
                                                 const QString &source) {
  Word::is_language_valid(language);
  auto lay = new QHBoxLayout;
  auto image =
      new ImageLabel(&widget, source, Displays::DisplayStyle::SCALED_WIDTH,
                     WidgetData::ELEMENT_HEIGHT);

  auto words_number = dictionary->get_number_of_words(language);
  auto label = create_base_label(QString::number(words_number) + " words");

  lay->addWidget(image);
  lay->addWidget(label);
  return lay;
}

void ContentLayout::set_box() { emit set_signal(dictionary); }

QHBoxLayout *ContentLayout::create_operation_layout() {
  auto lay = new QHBoxLayout;

  QObject::connect(&trash_button, &QPushButton::clicked, this,
                   [this]() { trash_element(); });
  QObject::connect(&edit_button, &QPushButton::clicked, this,
                   &ContentLayout::change_title);
  QObject::connect(&cancel_button, &QPushButton::clicked, this,
                   &ContentLayout::cancel_title);
  QObject::connect(&confirm_button, &QPushButton::clicked, this,
                   &ContentLayout::confirm_title);
  QObject::connect(&set_button, &QPushButton::clicked, this,
                   &ContentLayout::set_box);

  trash_button.setObjectName("plusbutton");
  edit_button.setObjectName("plusbutton");
  confirm_button.setObjectName("plusbutton");
  cancel_button.setObjectName("plusbutton");
  lay->addWidget(&trash_button);
  lay->addWidget(&edit_button);
  lay->addWidget(&confirm_button);
  lay->addWidget(&cancel_button);
  return lay;
}

ImageButton *ContentLayout::get_trash_button() { return &trash_button; }

void ContentLayout::create_layout() {
  create_base_entryline();
  for (auto &[language, source] : source_languages) {
    auto lay = create_language_hbox(language, source);
    layout->addLayout(std::move(lay));
  }
  set_button.setMaximumWidth(WidgetData::ELEMENT_WIDTH);
  layout->addWidget(&set_button);
  auto edit_trash_panel = create_operation_layout();
  layout->addLayout(std::move(edit_trash_panel));
}

Dictionary *ContentLayout::get_dictionary() { return dictionary; }

void ContentLayout::change_title() {
  entry_title.setReadOnly(false);
  entry_title.setObjectName("entryline");
  entry_title.style()->polish(&entry_title);
  set_confirm_cancel_panel();
}

void ContentLayout::confirm_title() {
  if (entry_title.text() != "") {
    entry_title.setReadOnly(true);
    entry_title.setObjectName("entrytitle");
    entry_title.style()->polish(&entry_title);
    dictionary->set_name(entry_title.text());
    set_edit_panel();
  } else {
    auto msg = CustomMessageBox(&widget, TITLE, INFORMATION_WARNING);
    msg.run(CustomMessageBox::Type::Ok);
  }
}

void ContentLayout::cancel_title() {
  entry_title.setReadOnly(true);
  entry_title.setObjectName("entrytitle");
  entry_title.style()->polish(&entry_title);
  entry_title.setText(dictionary->get_name());
  set_edit_panel();
}

void ContentLayout::set_confirm_cancel_panel() {
  confirm_button.setVisible(true);
  cancel_button.setVisible(true);
  edit_button.setVisible(false);
}
void ContentLayout::set_edit_panel() {
  confirm_button.setVisible(false);
  cancel_button.setVisible(false);
  edit_button.setVisible(true);
}

void ContentLayout::trash_element() { emit trash_dict(dictionary); }
