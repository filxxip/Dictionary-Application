#include "wordlist_widget.h"
#include "../custom_entry_line/entry_line.h"
#include "../data/config_file.h"
#include "../text_button/text_button.h"

#include <QDebug>
#include <QLabel>
#include <QObject>

#include <map>
#include <utility>

namespace {
constexpr char EXIT_IMAGE[] = "images/exit.png";
constexpr char TITLE_IMAGE[] = "images/dict.png";
constexpr char NEW_IMAGE[] = "images/plus.png";
constexpr char GROUPBOX_NAME[] = "smallgroupbox";

std::map<Word::Language, QString> source_languages = {
    {Word::Language::POLISH, "images/poland.jpg"},
    {Word::Language::GERMAN, "images/german.jpg"},
    {Word::Language::ENGLISH, "images/english.png"}};
} // namespace

void WordlistWindow::setting_scroll_options() {
  scrollarea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scrollarea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollarea.setWidgetResizable(true);
  groupbox->setEnabled(true);
}

WordlistWindow::WordlistWindow()
    : QObject(), exit_button(&main_widget, EXIT_IMAGE,
                             Displays::DisplayStyle::SCALED_WIDTH,
                             WidgetData::EXIT_HEIGHT),
      main_label(&main_widget, TITLE_IMAGE,
                 Displays::DisplayStyle::CHANGED_WIDTH,
                 WidgetData::WORDLIST_VIEW_IMG_HEIGHT),
      groupbox(std::make_unique<QGroupBox>()),
      baselayout(std::make_unique<QVBoxLayout>()) {
  mainlayout.addWidget(&main_label);
  exit_button.set_position(WidgetData::EXIT_POSITION_X,
                           WidgetData::EXIT_POSITION_Y);

  setting_scroll_options();

  scrollarea.setWidget(groupbox.get());
  mainlayout.addWidget(&scrollarea);

  main_widget.setLayout(&mainlayout);
  mainlayout.setContentsMargins(WidgetData::WORDLIST_VIEW_IMG_MARGINS);
}

QWidget *WordlistWindow::get_widget() { return &main_widget; };

ImageButton &WordlistWindow::get_exit_button() { return exit_button; }

void WordlistWindow::set_dict(std::vector<Dictionary *> dictionary) {
  dict = dictionary;
  baselayout = std::make_unique<QVBoxLayout>();
  groupbox = std::make_unique<QGroupBox>();

  scrollarea.setWidget(groupbox.get());
  QHBoxLayout *hboxlay;
  auto dict_size = dict.size();
  for (unsigned long i = 0; i <= dict_size; i++) {
    if (i < dict_size - 1) {
      auto first = create_groupbox(dict.at(i));
      i++;
      auto second = create_groupbox(dict.at(i));
      hboxlay = create_pair(first, second);
      baselayout->addLayout(hboxlay);
      continue;
    }
    if (i == dict_size - 1) {
      auto first = create_groupbox(dict.at(i));
      auto second = create_new_dict_groupbox();
      hboxlay = create_pair(first, second);
      baselayout->addLayout(hboxlay);
      break;
    }
    if (i == dict_size) {
      auto first = create_new_dict_groupbox();
      hboxlay = create_pair(first);
      baselayout->addLayout(hboxlay);
      break;
    }
  }
  groupbox->setLayout(baselayout.get());
}

QGroupBox *WordlistWindow::create_groupbox(Dictionary *dict) {
  auto *box = create_base_groupbox();

  auto *layout = new QVBoxLayout;
  box->setLayout(layout);

  auto label = new TextLabel(&main_widget, dict->get_name());
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  layout->addWidget(label);

  for (auto &[language, source] : source_languages) {
    auto lay = new QHBoxLayout;
    auto image = new ImageLabel(&main_widget, source,
                                Displays::DisplayStyle::SCALED_WIDTH,
                                WidgetData::ELEMENT_HEIGHT);

    auto words_number = dict->get_number_of_words(language);
    auto label = create_base_label(QString::number(words_number) + " words");

    lay->addWidget(image);
    lay->addWidget(label);
    layout->addLayout(lay);
  }
  auto set_button = new TextButton(&main_widget, WidgetData::SET_BUTTON_TEXT);
  set_button->setMaximumWidth(WidgetData::ELEMENT_WIDTH);
  layout->addWidget(set_button);
  return box;
}

QHBoxLayout *WordlistWindow::create_pair(QGroupBox *first, QGroupBox *second) {
  auto *lay = new QHBoxLayout;
  lay->addWidget(first);
  if (second) {
    lay->addWidget(second);
  }
  return lay;
}

QGroupBox *WordlistWindow::create_new_dict_groupbox() {

  auto *box = create_base_groupbox();
  auto *layout = new QVBoxLayout;
  box->setLayout(layout);

  auto label = new TextLabel(&main_widget, WidgetData::NEW_DICT_LABEL_TEXT);
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  layout->addWidget(label);

  auto entry = new EntryLine(&main_widget, EntryLine::Status::NORMAL);
  entry->setPlaceholderText(Placeholders::NEW_DICT_PLACEHOLDER);
  entry->setAlignment(Qt::AlignRight);

  auto button = new ImageButton(&main_widget, NEW_IMAGE,
                                Displays::DisplayStyle::SCALED_WIDTH,
                                WidgetData::NEW_DICT_BUTTON);
  layout->setSpacing(WidgetData::NEW_DICT_SPACING);
  layout->addWidget(entry);
  layout->addWidget(button);
  return box;
}

TextLabel *WordlistWindow::create_base_label(const QString &text) {
  auto label = new TextLabel(&main_widget, text);
  label->setAlignment(Qt::AlignRight);
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  return label;
}

QGroupBox *WordlistWindow::create_base_groupbox() {
  auto *box = new QGroupBox;
  box->setEnabled(true);
  box->setObjectName(GROUPBOX_NAME);
  box->setFixedWidth(WidgetData::ELEMENT_WIDTH);
  return box;
}
