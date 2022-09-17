#include "login_view.h"
#include "../data/config_file.h"
#include "../delay/delay.h"
#include "../image_button/image_button.h"

#include <QDebug>
#include <QObject>
#include <QStyle>
#include <QTime>
#include <QTimer>

LoginView::LoginView(const std::map<QString, QString> &logs_map)
    : QObject(),
      main_image_label(ImageLabel(&main_widget, "images/dict.png",
                                  ImageLabel::DisplayStyle::CHANGED_WIDTH,
                                  WidgetData::IMAGE_HEIGHT)),
      login_label(TextLabel(&main_widget, WidgetData::LOGIN_LABEL_TEXT)),
      password_label(TextLabel(&main_widget, WidgetData::PASSWORD_LABEL_TEXT)),
      login_entry(LoginLineEntry(&main_widget)),
      password_entry(PasswordEntryLine(&main_widget)),
      image_label(&main_widget, "images/dict.png",
                  ImageButton::DisplayStyle::CHANGED_HEIGHT, 50),
      submit_button(&main_widget, WidgetData::SUBMIT_BUTTON_TEXT),
      clear_button(&main_widget, WidgetData::CLEAR_BUTTON_TEXT) {
  login_label.setFixedWidth(WidgetData::LOGIN_LABEL_WIDTH);
  password_label.setFixedWidth(WidgetData::PASSWORD_LABEL_WIDTH);
  main_layout.addWidget(&main_image_label);
  auto login_box = creating_log_layout(EntryLine::Status::NORMAL);
  main_layout.addLayout(login_box);
  auto password_box = creating_log_layout(EntryLine::Status::PASSWORD);
  main_layout.addLayout(password_box);
  auto buttons_layout =
      creating_buttons_layout(logs_map, WidgetData::BUTTONS_MARGINS);
  main_layout.addLayout(buttons_layout);
  main_layout.setContentsMargins(WidgetData::MAIN_LAYOUT_MARGINS);
  main_widget.setLayout(&main_layout);
}

QHBoxLayout *LoginView::creating_log_layout(EntryLine::Status login_status,
                                            const QMargins &margin) {
  QHBoxLayout *layout(new QHBoxLayout);
  switch (login_status) {
  case EntryLine::Status::NORMAL: {
    layout->addWidget(&login_label);
    layout->addWidget(&login_entry);
    break;
  }
  case EntryLine::Status::PASSWORD: {
    layout->addWidget(&password_label);
    layout->addWidget(&password_entry);
    layout->addWidget(&image_label);
    break;
  }
  }
  layout->setSpacing(WidgetData::LOGS_SPACING);
  layout->setContentsMargins(margin);
  return layout;
}

QWidget *LoginView::get_widget() { return &main_widget; }

QHBoxLayout *
LoginView::creating_buttons_layout(const std::map<QString, QString> &logs_map,
                                   const QMargins &margin) {
  auto layout = new QHBoxLayout;
  layout->addWidget(&submit_button);
  layout->addWidget(&clear_button);
  QObject::connect(
      &submit_button, &QPushButton::pressed, this,
      [logs_map, this]() { // dlaczego dziala przez kopie a przez referencje nie
        this->submit_function(logs_map);
      });
  QObject::connect(&clear_button, &QPushButton::pressed, this,
                   &LoginView::clear_function);
  QObject::connect(&password_entry, &QLineEdit::returnPressed, this,
                   [this]() { submit_button.pressed(); });
  layout->setSpacing(WidgetData::BUTTONS_SPACING);
  layout->setContentsMargins(margin);
  return layout;
}

void LoginView::clear_function() {
  password_entry.clear();
  login_entry.clear();
}

void LoginView::submit_function(const std::map<QString, QString> &logs_map) {
  auto email = login_entry.text();
  auto password = password_entry.text();
  auto index = std::find_if(
      logs_map.begin(), logs_map.end(),
      [&email](const auto &pair) { // nie dziala mi structure bindings
        return pair.first == email;
      });
  if (index == logs_map.end()) {
    change_color(LoginView::ENTRIES_SIGNS::BOTH, 1500, Colors::RED);
  } else {
    auto index_pass = std::find_if(
        logs_map.begin(), logs_map.end(),
        [&password](const auto &pair) { // nie dziala mi structure bindings
          return pair.second == password;
        });
    if (index_pass == logs_map.end()) {
      change_color(LoginView::ENTRIES_SIGNS::PASSWORD, 1500, Colors::RED);
    } else {
      change_color(LoginView::ENTRIES_SIGNS::BOTH, 1500, Colors::GREEN);
    }
  }
}

void LoginView::change_color(LoginView::ENTRIES_SIGNS lineedit,
                             int miliseconds_sleep,
                             const QString &change_color) {
  auto style_log = login_entry.styleSheet();
  auto style_pass = password_entry.styleSheet();
  switch (lineedit) {
  case LoginView::ENTRIES_SIGNS::LOGIN: {
    login_entry.setStyleSheet("background-color: " + change_color);
    break;
  }
  case LoginView::ENTRIES_SIGNS::PASSWORD: {
    password_entry.setStyleSheet("background-color: " + change_color);
    break;
  }
  case LoginView::ENTRIES_SIGNS::BOTH: {
    password_entry.setStyleSheet("background-color: " + change_color);
    login_entry.setStyleSheet("background-color: " + change_color);
  }
  }
  delay(miliseconds_sleep);
  switch (lineedit) {
  case LoginView::ENTRIES_SIGNS::LOGIN: {
    login_entry.setStyleSheet(style_log);
    break;
  }
  case LoginView::ENTRIES_SIGNS::PASSWORD: {
    password_entry.setStyleSheet(style_pass);
    break;
  }
  case LoginView::ENTRIES_SIGNS::BOTH: {
    login_entry.setStyleSheet(style_log);
    password_entry.setStyleSheet(style_pass);
  }
  }
  //  lineedit->setStyleSheet(style);
}
