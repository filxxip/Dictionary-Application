#include "newdict_layout.h"
#include "../content_layout/content_layout.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_message_box/custom_message_box.h"
#include "../data/config_file.h"
#include "../text_button/text_button.h"

#include <QLabel>
#include <QObject>

namespace {
constexpr char TITLE[] = "Incorrect Data";
constexpr char INFO_TEXT[] = "Creating empty dict is not allowed";
constexpr char NEW_IMAGE[] = "images/plus.png";
constexpr char BROOM_IMAGE[] = "images/broom.png";

} // namespace

NewDictLayout::NewDictLayout(QWidget &widget_, Qt::Alignment align)
    : CustomVBoxLayout(widget_), entry(&widget_, EntryLine::Status::NORMAL),
      label(&widget, WidgetData::NEW_DICT_LABEL_TEXT),
      clear_button(&widget, BROOM_IMAGE, Displays::DisplayStyle::SCALED_HEIGHT,
                   WidgetData::NEW_DICT_BUTTON),
      create_button(&widget, NEW_IMAGE, Displays::DisplayStyle::SCALED_HEIGHT,
                    WidgetData::NEW_DICT_BUTTON) {
  create_layout(align);
}

void NewDictLayout::create_base_label(Qt::Alignment align) {
  label.setAlignment(align);
  label.setFixedHeight(WidgetData::ELEMENT_HEIGHT);
  label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void NewDictLayout::create_layout(Qt::Alignment align) {
  layout->setSpacing(WidgetData::NEW_DICT_SPACING);
  layout->setContentsMargins(WidgetData::NEW_GRPBOX_MARGINS);
  layout->addWidget(&label);
  create_entry(align);
  layout->addWidget(&entry);
  clear_button.setObjectName("plusbutton");

  QObject::connect(&clear_button, &QPushButton::clicked, this,
                   [this]() { entry.clear(); });
  QObject::connect(&create_button, &QPushButton::clicked, this,
                   [this]() { new_button_function(); });

  auto hboxlayout = new QHBoxLayout;

  hboxlayout->addWidget(&create_button);
  hboxlayout->addWidget(&clear_button);
  layout->addLayout(hboxlayout);
}

// Dictionary &NewDictLayout::get_dictionary() { return nullptr; } // todo

void NewDictLayout::new_button_function() {
  auto text = entry.text();
  if (!text.isEmpty()) {
    emit new_box_signal(entry.text());
  } else {
    auto msg = CustomMessageBox(&widget, TITLE, INFO_TEXT);
    msg.run(CustomMessageBox::Type::Ok);
  }
}

void NewDictLayout::create_entry(Qt::Alignment align) {
  entry.setPlaceholderText(Placeholders::NEW_DICT_PLACEHOLDER);
  entry.setAlignment(align);
}

bool NewDictLayout::has_dictionary() const { return false; }
