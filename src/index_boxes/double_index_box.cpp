#include "double_index_box.h"
#include "../data/config_file.h"

#include <QObject>
#include <QPushButton>
#include <QStyle>

namespace {
constexpr char EDIT_IMAGE[] = "images/editv2.png";
constexpr char CONFIRM_CHANGES[] = "images/confirm2.png";
constexpr char CANCEL_CHANGES[] = "images/cancel2.png";
constexpr char DELETE_TRANSLATION[] = "images/delete.png";
} // namespace

DoubleIndexBox::DoubleIndexBox(QWidget *widget_, Word &word_,
                               const QString &index,
                               Word::Language base_language_,
                               Word::Language translated_language_)
    : IndexBox(widget_, word_, index, base_language_),
      to_word_entry(widget_, EntryLine::Status::NORMAL),
      widget_change_bar_layout(std::make_unique<QWidget>()),
      change_bar_layout(std::make_unique<QHBoxLayout>()),
      edit_button(widget, EDIT_IMAGE, Displays::DisplayStyle::SCALED_WIDTH, 30),
      confirm_button(widget, CONFIRM_CHANGES,
                     Displays::DisplayStyle::SCALED_WIDTH, 30),
      cancel_button(widget, CANCEL_CHANGES,
                    Displays::DisplayStyle::SCALED_WIDTH, 30),
      delete_button(widget, DELETE_TRANSLATION,
                    Displays::DisplayStyle::SCALED_WIDTH, 30),
      translated_language(translated_language_) {

  set_status(Status::READ_ONLY);
  set_entry_basic_options(&to_word_entry, translated_language);
  widget_change_bar_layout->setLayout(change_bar_layout.get());
  addWidget(widget_change_bar_layout.get());
  widget_change_bar_layout->setObjectName("bluecolor");

  apply_button_configuration(&edit_button);
  apply_button_configuration(&confirm_button);
  apply_button_configuration(&cancel_button);
  apply_button_configuration(&delete_button);

  set_status(Status::READ_ONLY);
  QObject::connect(&edit_button, &QPushButton::clicked, this,
                   &DoubleIndexBox::edit_method);
  QObject::connect(&cancel_button, &QPushButton::clicked, this,
                   &DoubleIndexBox::cancel_changes);
  QObject::connect(&confirm_button, &QPushButton::clicked, this,
                   &DoubleIndexBox::confirm_changes);
  QObject::connect(&delete_button, &QPushButton::clicked, this,
                   &DoubleIndexBox::delete_translation);
}

void DoubleIndexBox::apply_button_configuration(QPushButton *button) {
  change_bar_layout->addWidget(button);
  button->setObjectName("bluecolor");
}

void DoubleIndexBox::edit_method() {
  set_status(Status::EDIT);
  set_edit_style(&to_word_entry);
  set_edit_style(&from_word_entry);
}

void DoubleIndexBox::set_edit_style(EntryLine *entryline) {
  entryline->set_object_name_stylesheet("entryline");
}

void DoubleIndexBox::set_read_style(EntryLine *entryline) {
  entryline->set_object_name_stylesheet("entrytitle");
}

void DoubleIndexBox::set_status(Status status) {
  auto condition = status == IndexBox::Status::READ_ONLY;
  from_word_entry.setReadOnly(condition);
  to_word_entry.setReadOnly(condition);
  change_status_images(status);
}

void DoubleIndexBox::change_status_images(Status status) {
  auto condition = status == IndexBox::Status::READ_ONLY;
  cancel_button.setVisible(!condition);
  confirm_button.setVisible(!condition);
  edit_button.setVisible(condition);
  delete_button.setVisible(condition);
  //  switch (status) {
  //  case IndexBox::Status::EDIT: {
  //    cancel_button.setVisible(true);
  //    confirm_button.setVisible(true);
  //    edit_button.setVisible(false);
  //    delete_button.setVisible(false);
  //    break;
  //  }
  //  case IndexBox::Status::READ_ONLY: {
  //    cancel_button.setVisible(false);
  //    confirm_button.setVisible(false);
  //    edit_button.setVisible(true);
  //    delete_button.setVisible(true);
  //    break;
  //  }
  //  }
}

void DoubleIndexBox::set_visible(bool status) {
  index_label.setVisible(status);
  from_word_entry.setVisible(status);
  this->edit_button.setVisible(status);
  confirm_button.setVisible(status);
  this->cancel_button.setVisible(status);
  delete_button.setVisible(status);
  to_word_entry.setVisible(status);
}

void DoubleIndexBox::cancel_changes() {
  auto previous_translation = word.get_translation(translated_language);
  auto base = word.get_translation(base_language);
  from_word_entry.setText(base);
  to_word_entry.setText(previous_translation);
  set_status(IndexBox::Status::READ_ONLY);
  set_read_style(&to_word_entry);
  set_read_style(&from_word_entry);
}

void DoubleIndexBox::confirm_changes() {
  auto base = from_word_entry.text();
  auto translation = to_word_entry.text();
  word.change_translation(translated_language, translation);
  word.change_translation(base_language, base);
  set_status(IndexBox::Status::READ_ONLY);
  set_read_style(&to_word_entry);
  set_read_style(&from_word_entry);
  emit update_window();
}

void DoubleIndexBox::delete_translation() {
  word.set_not_defined(translated_language);
  emit update_window();
}
