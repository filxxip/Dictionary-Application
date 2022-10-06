#include "config_detail_view_panel.h"
#include "../data/config_file.h"

#include <QStyle>

CustomizeImageButton::CustomizeImageButton(QWidget *widget,
                                           const QString &image_source)
    : ImageButton(widget, image_source, Displays::DisplayStyle::SCALED_WIDTH,
                  WidgetData::IMAGE_HEIGHT_OF_DETAIL_PANEL) {
  set_style_sheet("edit_panel_style");
}

ConfigDetailViewPanel::ConfigDetailViewPanel(QWidget *widget, Word &word_)
    : main_widget(widget),
      trash_all_button(main_widget,
                       WidgetData::IMAGE_FILE_LITERAL.arg("trashall.png")),
      add_button(main_widget, WidgetData::IMAGE_FILE_LITERAL.arg("add.png")),
      edit_button(main_widget, WidgetData::IMAGE_FILE_LITERAL.arg("edit3.png")),
      cancel_button(main_widget,
                    WidgetData::IMAGE_FILE_LITERAL.arg("cancel3.png")),
      confirm_button(main_widget,
                     WidgetData::IMAGE_FILE_LITERAL.arg("confirm3.png")),
      word(word_) {
  addWidget(&confirm_button);
  addWidget(&trash_all_button);
  addWidget(&edit_button);
  addWidget(&add_button);
  addWidget(&cancel_button);

  connect_button();
  set_status(Status::NORMAL);
}

void ConfigDetailViewPanel::set_status(Status status) {
  auto condition = status == Status::NORMAL;
  confirm_button.setVisible(!condition);
  cancel_button.setVisible(!condition);
  edit_button.setVisible(condition);
  add_button.setVisible(condition);
  trash_all_button.setVisible(condition);
}

void ConfigDetailViewPanel::connect_button() {
  QObject::connect(&trash_all_button, &QPushButton::clicked, this,
                   &ConfigDetailViewPanel::delete_word_slot);
  QObject::connect(&confirm_button, &QPushButton::clicked, this,
                   &ConfigDetailViewPanel::confirm_changes_slot);
  QObject::connect(&cancel_button, &QPushButton::clicked, this,
                   &ConfigDetailViewPanel::cancel_changes_slot);
  QObject::connect(&edit_button, &QPushButton::clicked, this,
                   &ConfigDetailViewPanel::edit_word_slot);
  QObject::connect(&add_button, &QPushButton::clicked, this,
                   &ConfigDetailViewPanel::add_new_word_slot);
}

void ConfigDetailViewPanel::delete_word_slot() {
  emit delete_word_signal(word);
}

void ConfigDetailViewPanel::add_new_word_slot() {}

void ConfigDetailViewPanel::edit_word_slot() {}

void ConfigDetailViewPanel::confirm_changes_slot() {}

void ConfigDetailViewPanel::cancel_changes_slot() {}
