#include "double_grp_box.h"
#include "../content_layout/content_layout.h"
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

DoubleGrpBox::DoubleGrpBox(QWidget &widget_)
    : widget(widget_), right_layout(nullptr) {
  left_layout = std::make_unique<NewDictLayout>(widget_, Qt::AlignCenter);
  create_pair();
}

DoubleGrpBox::DoubleGrpBox(QWidget &widget_, Dictionary *dict1,
                           Dictionary *dict2)
    : widget(widget_) {
  left_layout = std::make_unique<ContentLayout>(widget_, dict1);
  right_layout = std::make_unique<ContentLayout>(widget_, dict2);
  create_pair();
}
DoubleGrpBox::DoubleGrpBox(QWidget &widget_, Dictionary *dict1)
    : widget(widget_) {
  left_layout = std::make_unique<ContentLayout>(widget_, dict1);
  right_layout = std::make_unique<NewDictLayout>(widget_, Qt::AlignRight);
  create_pair();
}

void DoubleGrpBox::create_pair() {
  auto left_ptr = get_left_groupbox().get();
  addWidget(std::move(left_ptr));
  if (right_layout) {
    auto right_ptr = get_right_groupbox().get();
    addWidget(std::move(right_ptr));
  }
}

const std::unique_ptr<QGroupBox> &DoubleGrpBox::get_left_groupbox() {
  return left_layout->get_groupbox();
}

const std::unique_ptr<QGroupBox> &DoubleGrpBox::get_right_groupbox() {
  return right_layout->get_groupbox();
}

const std::unique_ptr<QVBoxLayout> &DoubleGrpBox::get_left_layout() {
  return left_layout->get_layout();
}

const std::unique_ptr<QVBoxLayout> &DoubleGrpBox::get_right_layout() {
  return right_layout->get_layout();
}

Dictionary *DoubleGrpBox::get_left_dictionary() {
  return left_layout->get_dictionary();
}

Dictionary *DoubleGrpBox::get_right_dictionary() {
  return right_layout->get_dictionary();
}

NewDictLayout *DoubleGrpBox::get_dict_layout() {
  if (dynamic_cast<NewDictLayout *>(left_layout.get())) {
    return static_cast<NewDictLayout *>(left_layout.get());
  }
  if (dynamic_cast<NewDictLayout *>(right_layout.get())) {
    return static_cast<NewDictLayout *>(right_layout.get());
  }
  return nullptr;
}

const std::unique_ptr<CustomVBoxLayout> &DoubleGrpBox::get_left_item() {
  return left_layout;
}
const std::unique_ptr<CustomVBoxLayout> &DoubleGrpBox::get_right_item() {
  return right_layout;
}

bool DoubleGrpBox::has_dictionary(Dictionary *dict) {
  if (left_layout->get_dictionary() == dict) {
    return true;
  }
  if (right_layout->get_dictionary() == dict) {
    return true;
  }
  return false;
}

void DoubleGrpBox::update_dictionary(Dictionary *dict) {
  if (left_layout->get_dictionary() == dict) {
    left_layout->update();
  }
  if (right_layout->get_dictionary() == dict) {
    right_layout->update();
  }
}
