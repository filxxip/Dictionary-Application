#include "double_grp_box.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_message_box/custom_message_box.h"
#include "../data/config_file.h"
#include "../text_button/text_button.h"

#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QScrollBar>
#include <QTimer>

#include <map>
#include <utility>

namespace {
constexpr char TITLE[] = "Incorrect Data";
constexpr char INFO_TEXT[] = "Creating empty dict is not allowed";
constexpr char NEW_IMAGE[] = "images/plus.png";
constexpr char BROOM_IMAGE[] = "images/broom.png";
constexpr char GROUPBOX_NAME[] = "smallgroupbox";

std::map<Word::Language, QString> source_languages = {
    {Word::Language::POLISH, "images/poland.jpg"},
    {Word::Language::GERMAN, "images/german.jpg"},
    {Word::Language::ENGLISH, "images/english.png"}};
} // namespace

DoubleGrpBox::DoubleGrpBox(QWidget &widget_)
    : widget(widget_), dictionary1(nullptr), dictionary2(nullptr),
      second(nullptr), second_layout(nullptr) {
  first = create_groupbox();
  first_layout = create_new_dict_layout(Qt::AlignCenter);
  first->setLayout(first_layout.get());
  create_pair();
}

DoubleGrpBox::DoubleGrpBox(QWidget &widget_, Dictionary *dict1,
                           Dictionary *dict2)
    : widget(widget_), dictionary1(dict1), dictionary2(dict2) {
  first = create_groupbox();
  first_layout = create_layout(dict1);
  first->setLayout(first_layout.get());
  second = create_groupbox();
  second_layout = create_layout(dict2);
  second->setLayout(second_layout.get());
  create_pair();
}
DoubleGrpBox::DoubleGrpBox(QWidget &widget_, Dictionary *dict1)
    : widget(widget_), dictionary1(dict1), dictionary2(nullptr) {
  first = create_groupbox();
  first_layout = create_layout(dict1);
  first->setLayout(first_layout.get());
  second = create_groupbox();
  second_layout = create_new_dict_layout(Qt::AlignRight);
  second->setLayout(second_layout.get());
  create_pair();
}
Dictionary *DoubleGrpBox::get_dict(Status status) {
  switch (status) {
  case Status::FIRST: {
    return dictionary1;
  }
  case Status::SECOND: {
    return dictionary2;
  }
  }
  return dictionary1; // never
}

const std::unique_ptr<QGroupBox> &DoubleGrpBox::get_pointer(Status status) {
  switch (status) {
  case Status::FIRST: {
    return first;
  }
  case Status::SECOND: {
    return second;
  }
  }
  return first; // never
}
const std::unique_ptr<QVBoxLayout> &DoubleGrpBox::get_layout(Status status) {
  switch (status) {
  case Status::FIRST: {
    return first_layout;
  }
  case Status::SECOND: {
    return second_layout;
  }
  }
  return first_layout; // never
}

TextLabel *DoubleGrpBox::create_base_label(const QString &text) {
  auto label = new TextLabel(&widget, text);
  label->setAlignment(Qt::AlignRight);
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  return label;
}

std::unique_ptr<QGroupBox> DoubleGrpBox::create_groupbox() {
  auto box = std::make_unique<QGroupBox>();
  box->setEnabled(true);
  box->setObjectName(GROUPBOX_NAME);
  box->setFixedWidth(WidgetData::ELEMENT_WIDTH);
  return box;
}
std::unique_ptr<QVBoxLayout> DoubleGrpBox::create_layout(Dictionary *dict) {

  auto layout = std::make_unique<QVBoxLayout>();
  auto label = new TextLabel(&widget, dict->get_name());
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  layout->addWidget(label);
  for (auto &[language, source] : source_languages) {
    auto lay = new QHBoxLayout;
    auto image =
        new ImageLabel(&widget, source, Displays::DisplayStyle::SCALED_WIDTH,
                       WidgetData::ELEMENT_HEIGHT);

    auto words_number = dict->get_number_of_words(language);
    auto label = create_base_label(QString::number(words_number) + " words");

    lay->addWidget(image);
    lay->addWidget(label);
    layout->addLayout(lay);
  }
  auto set_button = new TextButton(&widget, WidgetData::SET_BUTTON_TEXT);
  set_button->setMaximumWidth(WidgetData::ELEMENT_WIDTH);
  layout->addWidget(set_button);
  return layout;
}

std::unique_ptr<QVBoxLayout>
DoubleGrpBox::create_new_dict_layout(Qt::Alignment align) {

  auto layout = std::make_unique<QVBoxLayout>();

  auto label = new TextLabel(&widget, WidgetData::NEW_DICT_LABEL_TEXT);
  label->setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  layout->addWidget(label);

  auto entry = new EntryLine(&widget, EntryLine::Status::NORMAL);
  entry->setPlaceholderText(Placeholders::NEW_DICT_PLACEHOLDER);
  entry->setAlignment(align);

  auto button =
      new ImageButton(&widget, NEW_IMAGE, Displays::DisplayStyle::SCALED_HEIGHT,
                      WidgetData::NEW_DICT_BUTTON);
  button->setObjectName("plusbutton");
  auto clear = new ImageButton(&widget, BROOM_IMAGE,
                               Displays::DisplayStyle::SCALED_HEIGHT,
                               WidgetData::NEW_DICT_BUTTON);
  clear->setObjectName("plusbutton");
  QObject::connect(clear, &QPushButton::clicked, this,
                   [entry]() { entry->clear(); });
  QObject::connect(button, &QPushButton::clicked, this, [this, entry]() {
    auto text = entry->text();
    if (!text.isEmpty()) {
      emit new_box_signal(entry->text());
    } else {
      auto msg = CustomMessageBox(&widget, TITLE, INFO_TEXT);
      msg.run(CustomMessageBox::Type::Ok);
    }
  });
  layout->setSpacing(WidgetData::NEW_DICT_SPACING);
  layout->setContentsMargins(WidgetData::NEW_GRPBOX_MARGINS);
  layout->addWidget(entry);
  auto hboxlayout = new QHBoxLayout;
  hboxlayout->addWidget(button);
  hboxlayout->addWidget(clear);
  layout->addLayout(hboxlayout);
  return layout;
}

void DoubleGrpBox::create_pair() {
  addWidget(first.get());
  if (second) {
    addWidget(second.get());
  }
}
